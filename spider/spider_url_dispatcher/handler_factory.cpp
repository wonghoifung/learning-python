//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "handler_factory.h"
#include "unverified_handler.h"
#include "consumer_handler.h"
#include "producer_handler.h"

handler_factory& handler_factory::ref()
{
	static handler_factory hf;
	return hf;
}

tcpconn_handler* handler_factory::create_handler(CONN_TYPE type)
{
	switch (type)
	{
	case CONN_TYPE_UNVERIFIED:
		return new unverified_handler();
	case CONN_TYPE_CONSUMER:
		return new consumer_handler();
	case CONN_TYPE_PRODUCER:
		return new producer_handler();
	default:
		assert(0);
		break;
	}
	return NULL;
}

void handler_factory::destroy_handler(tcpconn_handler** h)
{
	if (h && *h)
	{
		delete *h;
		*h = NULL;
	}
}

