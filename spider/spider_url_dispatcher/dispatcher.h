//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef dispatcher_header
#define dispatcher_header

#include <string>
#include <boost/asio.hpp>
#include "shared/net/tcpserver.h"

class dispatcher : private boost::noncopyable
{
public:
	explicit dispatcher(boost::asio::io_service& ios, const std::string& address, const std::string& port);
	~dispatcher();

private:
	void handle_stop();
	void handle_usr1();

	void set_stop_signal();
	void set_usr1_signal();

	boost::asio::io_service& io_service_;
	boost::asio::signal_set signals_;
	boost::asio::signal_set reloadsignals_;

	tcpconn_handler* svrhandler_;
	tcpserver server_;
};

#endif

