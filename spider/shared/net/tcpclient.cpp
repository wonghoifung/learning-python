//
//  tcpclient.cpp
//  console
//
//  Created by huanghaifeng on 14-10-2.
//  Copyright (c) 2014 wonghoifung. All rights reserved.
//

#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/make_shared.hpp>
#include "tcpclient.h"

using boost::asio::ip::tcp;
  
tcpclient::tcpclient(boost::asio::io_service& iosrv, tcpconn_handler* h) :
	iosrv_(iosrv), reconntimer_(NULL), 
	conn_(boost::make_shared<tcpconn>(iosrv_)), 
	successorhandler_(h),
	autoreconn_(true)
{
	assert(successorhandler_);
	conn_->set_handler(this);
}

tcpclient::~tcpclient()
{
	if (reconntimer_)
	{
		boost::system::error_code e;
		reconntimer_->cancel(e);
		delete reconntimer_;
		reconntimer_ = NULL;
	}
}

void tcpclient::connect(const char* ip, const char* port, bool autoreconn)
{           
	ip_ = ip;
	port_ = port;
	conn_->connect(ip_, port_);
	autoreconn_ = autoreconn;
}
        
void tcpclient::close()
{
	autoreconn_ = false;
	conn_->stop();
}
    
void tcpclient::on_connect(tcpconn_ptr conn)
{
	{boost::format fmt("%1%:%2%");
	fmt % conn->socket().remote_endpoint().address().to_string();
	fmt % conn->socket().remote_endpoint().port();
	conn->set_remoteaddr(fmt.str()); }

	{boost::format fmt("%1%:%2%");
	fmt % conn->socket().local_endpoint().address().to_string();
	fmt % conn->socket().local_endpoint().port();
	conn->set_localaddr(fmt.str()); }

	successorhandler_->on_connect(conn);
}

void tcpclient::on_close(tcpconn_ptr conn, const int ec, const std::string& msg)
{
	successorhandler_->on_close(conn, ec, msg);

	if (autoreconn_)
	{
		if (reconntimer_ == NULL)
		{
			reconntimer_ = new boost::asio::deadline_timer(iosrv_);
		}
		reconntimer_->expires_from_now(boost::posix_time::seconds(30));
		reconntimer_->async_wait(boost::bind(&tcpclient::on_reconntimeout, this, boost::asio::placeholders::error));
	}
}

int tcpclient::on_message(tcpconn_ptr conn, decoder* pack)
{
	return successorhandler_->on_message(conn, pack);
}

void tcpclient::on_reconntimeout(const boost::system::error_code & error)
{
	if (error.value() == 0)
	{
		connect(ip_.c_str(), port_.c_str());
	}
}

