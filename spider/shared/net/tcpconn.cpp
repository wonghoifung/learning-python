//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#include "tcpconn.h"
#include "tcpconn_handler.h"
#include "shared/utils/logger.h"
#include <boost/bind.hpp>

tcpconn::tcpconn(const boost::asio::io_service& io_service) : 
	tcpconn_base(io_service),
	handler_(NULL)
{
	parser_.reset(new packparser(boost::bind(&tcpconn::pack_parse_complete, this, _1)));
	assert(parser_ != NULL);
}

tcpconn::~tcpconn()
{

}

int tcpconn::send(encoder* pack)
{
	return tcpconn_base::send(pack->cbuffer(), pack->size());
}

void tcpconn::on_connect(tcpconn_base_ptr conn)
{
	if (handler_)
	{
		handler_->on_connect(boost::dynamic_pointer_cast<tcpconn>(conn));
	}
}

void tcpconn::on_close(tcpconn_base_ptr conn, const int ec, const std::string& msg)
{
	if (handler_)
	{
		handler_->on_close(boost::dynamic_pointer_cast<tcpconn>(conn), ec, msg);
	}
}
//static unsigned int idx = 0;
void tcpconn::on_data(tcpconn_base_ptr conn, char* buf, size_t len)
{
	if (handler_)
	{
		//logstr("-------> idx:%u %s recv len: %d", idx, conn->remoteaddr().c_str(), len);
		parser_->parse(buf, len);
		//logstr("-------> idx:%u %s parse done", idx, conn->remoteaddr().c_str());
		//idx += 1;
	}
}

void tcpconn::on_highwatermark(tcpconn_base_ptr conn, size_t size, size_t count)
{
	if (handler_)
	{
		handler_->on_highwatermark(boost::dynamic_pointer_cast<tcpconn>(conn), size, count);
	}
}

int tcpconn::pack_parse_complete(decoder* pack)
{
	if (handler_)
	{
		return handler_->on_message(boost::dynamic_pointer_cast<tcpconn>(shared_from_this()), pack);
	}
	return -1;
}


