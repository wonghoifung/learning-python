//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef TCPSERVER_HEADER
#define TCPSERVER_HEADER

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "tcpconn.h"

class tcpconn_handler;

class tcpserver : private boost::noncopyable
{
public:
	explicit tcpserver(boost::asio::io_service& ios, const std::string& address, const std::string& port, tcpconn_handler* h);
	~tcpserver();
	void run();

private:
	void start_accept();
	void handle_accept(const boost::system::error_code& e);

	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;

	tcpconn_ptr new_connection_;
	tcpconn_handler* handler_;
};

#endif

