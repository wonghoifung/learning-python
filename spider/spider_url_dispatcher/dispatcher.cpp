//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "dispatcher.h"
#include "handler_factory.h"
#include "conn_manager.h"
#include "shared/utils/logger.h"
#include "config.h"
#include <boost/bind.hpp>

dispatcher::dispatcher(boost::asio::io_service& ios, const std::string& address, const std::string& port)
	: io_service_(ios), signals_(io_service_), reloadsignals_(io_service_),
	svrhandler_(handler_factory::ref().create_handler(CONN_TYPE_UNVERIFIED)),
	server_(io_service_, address, port, svrhandler_)
{
	set_stop_signal();
	set_usr1_signal(); // for reload config
}

dispatcher::~dispatcher()
{
	if (svrhandler_)
	{
		handler_factory::ref().destroy_handler(&svrhandler_);
	}
}

void dispatcher::handle_stop()
{
	io_service_.stop();
}

void dispatcher::handle_usr1()
{
	// reload
	logstr("recv signal sigusr1, reload config...");

	if (!config::ref().reload("../config/config.xml"))
	{
		logcritical("reload config error");
	}
	else
	{
		set_logger_level((logger_level)config::ref().logger_level());
	}

	logstr("config reload done!");

	set_usr1_signal();
}

void dispatcher::set_stop_signal()
{
	boost::system::error_code ec;
	signals_.clear(ec);

	signals_.add(SIGINT);
	signals_.add(SIGTERM);
#if defined(SIGQUIT)
	signals_.add(SIGQUIT);
#endif 
	signals_.async_wait(boost::bind(&dispatcher::handle_stop, this));
}

void dispatcher::set_usr1_signal()
{
	boost::system::error_code ec;
	reloadsignals_.clear(ec);

#if defined(SIGUSR1)
	reloadsignals_.add(SIGUSR1);
	reloadsignals_.async_wait(boost::bind(&dispatcher::handle_usr1, this));
#endif
}
