//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#include "tcpserver.h"
#include "tcpconn_handler.h"
#include "shared/utils/logger.h"
#include <boost/bind.hpp>
#include <boost/format.hpp>

tcpserver::tcpserver(boost::asio::io_service& ios, const std::string& address, const std::string& port, tcpconn_handler* h)
	: io_service_(ios),
	acceptor_(io_service_),
	new_connection_(),
	handler_(h)
{
	assert(handler_);

	boost::asio::ip::tcp::resolver resolver(acceptor_.get_io_service());
	boost::asio::ip::tcp::resolver::query query(address, port);
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor_.bind(endpoint);
	acceptor_.listen();
	start_accept();
}

tcpserver::~tcpserver()
{

}

void tcpserver::run()
{
	io_service_.run();
}

void tcpserver::start_accept()
{
	new_connection_.reset(new tcpconn(io_service_));
	new_connection_->set_handler(handler_);
	acceptor_.async_accept(new_connection_->socket(),
		boost::bind(&tcpserver::handle_accept, this,
		boost::asio::placeholders::error));
}

void tcpserver::handle_accept(const boost::system::error_code& e)
{
	if (!e)
	{
		try {
			{boost::format fmt("%1%:%2%");
			fmt % new_connection_->socket().remote_endpoint().address().to_string();
			fmt % new_connection_->socket().remote_endpoint().port();
			new_connection_->set_remoteaddr(fmt.str()); }

			{boost::format fmt("%1%:%2%");
			fmt % new_connection_->socket().local_endpoint().address().to_string();
			fmt % new_connection_->socket().local_endpoint().port();
			new_connection_->set_localaddr(fmt.str()); }

			handler_->on_connect(new_connection_);
			new_connection_->start();
		}
		catch (std::exception& e)
		{
			logcritical("[handle_accept] exception: %s", e.what());
		}
	}

	start_accept();
}

