//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef producer_handler_header
#define producer_handler_header

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "shared/net/tcpconn_handler.h"

class producer_handler : public tcpconn_handler
{
public:
	explicit producer_handler();
	virtual ~producer_handler();

	virtual void on_connect(tcpconn_ptr conn);
	virtual void on_close(tcpconn_ptr conn, const int ec, const std::string& msg);
	virtual int on_message(tcpconn_ptr conn, decoder* pack);
	virtual void on_highwatermark(tcpconn_ptr conn, size_t size, size_t count);

protected:
	int handle_produce_url(tcpconn_ptr conn, decoder* pack);
	int handle_pingpong(tcpconn_ptr conn, decoder* pack);

public:
	int handle_producer_register(tcpconn_ptr conn, decoder* pack);
};

#endif

