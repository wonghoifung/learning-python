//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#include "tcpconn_handler.h"
#include "shared/utils/logger.h"

tcpconn_handler::tcpconn_handler()
{

}

tcpconn_handler::~tcpconn_handler()
{

}

void tcpconn_handler::on_highwatermark(tcpconn_ptr conn, size_t size, size_t count)
{

}

void tcpconn_handler::set_default_sockbuf(tcpconn_ptr& conn)
{
	int ret = conn->set_sndbuf_size(1024 * 64);
	if (0 != ret)
	{
		logstr("peer(%s), set_sndbuf_size failure, err:%d", conn->remoteaddr().c_str(), ret); 
	}
	ret = conn->set_rcvbuf_size(1024 * 32);
	if (0 != ret)
	{
		logstr("peer(%s), set_rcvbuf_size failure, err:%d", conn->remoteaddr().c_str(), ret);
	}
}


