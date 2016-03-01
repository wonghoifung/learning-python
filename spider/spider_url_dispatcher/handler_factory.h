//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef handler_factory_header
#define handler_factory_header

#include <boost/noncopyable.hpp>
#include "shared/net/tcpconn_handler.h"
#include "command.h"

class handler_factory : private boost::noncopyable
{
private:
	handler_factory() {}
	~handler_factory() {}

public:
	static handler_factory& ref();
	tcpconn_handler* create_handler(CONN_TYPE type);
	void destroy_handler(tcpconn_handler** h);
};

#endif

