//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef TCPCONN_HANDLER_HEADER
#define TCPCONN_HANDLER_HEADER

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "tcpconn.h"

class tcpconn_handler : private boost::noncopyable
{
public:
	explicit tcpconn_handler();
	virtual ~tcpconn_handler();

	virtual void on_connect(tcpconn_ptr conn) = 0;
	virtual void on_close(tcpconn_ptr conn, const int ec, const std::string& msg) = 0;
	virtual int on_message(tcpconn_ptr conn, decoder* pack) = 0;
	virtual void on_highwatermark(tcpconn_ptr conn, size_t size, size_t count);

protected:
	void set_default_sockbuf(tcpconn_ptr& conn);
};

#endif

