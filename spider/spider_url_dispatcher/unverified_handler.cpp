//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "unverified_handler.h"
#include "producer_handler.h"
#include "consumer_handler.h"
#include "command.h"
#include "redisdao.h"
#include "conn_manager.h"
#include "handler_factory.h"
#include "shared/net/tcpclient.h"
#include "shared/utils/logger.h"
#include <json/json.h>
#include <boost/shared_array.hpp>
#include <boost/bind.hpp>

unverified_handler::unverified_handler() :producerh_(NULL), consumerh_(NULL)
{
	producerh_ = handler_factory::ref().create_handler(CONN_TYPE_PRODUCER);
	assert(producerh_);
	consumerh_ = handler_factory::ref().create_handler(CONN_TYPE_CONSUMER);
	assert(consumerh_);
}

unverified_handler::~unverified_handler()
{
	if (producerh_) {
		handler_factory::ref().destroy_handler(&producerh_);
	}

	if (consumerh_) {
		handler_factory::ref().destroy_handler(&consumerh_);
	}
}

void unverified_handler::on_connect(tcpconn_ptr conn)
{
	set_default_sockbuf(conn);
	logdebug("[unverified_handler] %s -> %s connected", conn->localaddr().c_str(), conn->remoteaddr().c_str());
}

void unverified_handler::on_close(tcpconn_ptr conn, const int ec, const std::string& msg)
{
	logdebug("[unverified_handler] %s -> %s closed", conn->localaddr().c_str(), conn->remoteaddr().c_str());
}

int unverified_handler::on_message(tcpconn_ptr conn, decoder* pack)
{
	int cmd = pack->command();
	switch (cmd)
	{
	case cmd_producer_register:
		conn->set_handler(producerh_);
		return dynamic_cast<producer_handler*>(producerh_)->handle_producer_register(conn, pack);

	case cmd_consumer_register:
		conn->set_handler(consumerh_);
		return dynamic_cast<consumer_handler*>(consumerh_)->handle_consumer_register(conn, pack);

	default:
		logstr("[unverified_handler] unverified_handler::on_message should not get cmd: %d", cmd);
		break;
	}
	return cmd;
}

