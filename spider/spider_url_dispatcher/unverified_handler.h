//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef unverified_handler_header
#define unverified_handler_header

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "shared/net/tcpconn_handler.h"

class unverified_handler : public tcpconn_handler
{
public:
	explicit unverified_handler();
	virtual ~unverified_handler();

	virtual void on_connect(tcpconn_ptr conn);
	virtual void on_close(tcpconn_ptr conn, const int ec, const std::string& msg);
	virtual int on_message(tcpconn_ptr conn, decoder* pack);

private:
	tcpconn_handler* producerh_;
	tcpconn_handler* consumerh_;
};

#endif

