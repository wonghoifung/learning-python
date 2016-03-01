//
//  tcpclient.h
//  console
//
//  Created by huanghaifeng on 14-10-2.
//  Copyright (c) 2014 wonghoifung. All rights reserved.
//

#ifndef tcpclient_header
#define tcpclient_header

#include <boost/asio.hpp>
#include "tcpconn_handler.h"

class tcpclient : public tcpconn_handler
{
public:
	tcpclient(boost::asio::io_service& iosrv, tcpconn_handler* h);
	virtual ~tcpclient();

    void connect(const char* ip, const char* port, bool autoreconn = true);
	void close();

	virtual void on_connect(tcpconn_ptr conn);
	virtual void on_close(tcpconn_ptr conn, const int ec, const std::string& msg);
	virtual int on_message(tcpconn_ptr conn, decoder* pack);
	void on_reconntimeout(const boost::system::error_code & error);

private:
    boost::asio::io_service& iosrv_;
	boost::asio::deadline_timer* reconntimer_;
	tcpconn_ptr conn_;
	tcpconn_handler* successorhandler_;
	std::string ip_;
	std::string port_;
	bool autoreconn_;
};
      
#endif
