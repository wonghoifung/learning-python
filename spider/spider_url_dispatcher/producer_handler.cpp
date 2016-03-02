//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "producer_handler.h"
#include "shared/net/tcpconn.h"
#include "command.h"
#include "redisdao.h"
#include "conn_manager.h"
#include "shared/net/tcpclient.h"
#include "shared/utils/logger.h"
#include "config.h"
#include "globals.h"
#include "pingpong_req.pb.h"
#include "pingpong_resp.pb.h"
#include "produce_url_req.pb.h"
#include "produce_url_resp.pb.h"
#include "producer_register_req.pb.h"
#include "producer_register_resp.pb.h"
#include "shared/protocol/pbcodec.h"
#include <json/json.h>
#include <boost/shared_array.hpp>
#include <boost/bind.hpp>

using namespace spider;

producer_handler::producer_handler()
{

}

producer_handler::~producer_handler()
{

}

void producer_handler::on_connect(tcpconn_ptr conn)
{
	
}

void producer_handler::on_close(tcpconn_ptr conn, const int ec, const std::string& msg)
{
	conn_info* ci = extract_conn_info(conn);
	if (ci) {
		conn_manager::ref().delete_producer(ci->id);
		logdebug("[producer_handler] %s -> %s closed", conn->localaddr().c_str(), conn->remoteaddr().c_str());
	}
}

int producer_handler::on_message(tcpconn_ptr conn, decoder* pack)
{
	int cmd = pack->command();
	switch (cmd)
	{
	case cmd_produce_url:
		return handle_produce_url(conn, pack);

	case cmd_pingpong:
		return handle_pingpong(conn, pack);

	default:
		assert(0);
		break;
	}
	return cmd;
}

void producer_handler::on_highwatermark(tcpconn_ptr conn, size_t size, size_t count)
{
	conn_info* ci = extract_conn_info(conn);
	if (ci == NULL) {
		logcritical("conn is dying");
		return;
	}

	logstr("[producer_handler] %s -> %s reach highwatermark, closed[id:%d]", conn->localaddr().c_str(), conn->remoteaddr().c_str(), ci->id);
	conn->stop();
	conn_manager::ref().delete_producer(ci->id); // remove as early as possible
}

int producer_handler::handle_produce_url(tcpconn_ptr conn, decoder* pack)
{
	conn_info* ci = extract_conn_info(conn);
	if (ci == NULL) {
		logcritical("conn is dying");
		return -1;
	}

	ci->update_current_op_count();

	produce_url_req req;
	if (!unseri_message(*pack, req)) {
		logcritical("cannot unseri produce url req, id:%d", ci->id);
		return -1;
	}

	for (int i = 0; i < req.urls_size(); ++i)
	{
		const ::std::string& url = req.urls(i);
		// TODO dispatch to consumers
		logdebug("produce %s", url.c_str());
	}

	return 0;
}

int producer_handler::handle_pingpong(tcpconn_ptr conn, decoder* pack)
{
	conn_info* ci = extract_conn_info(conn);
	if (ci == NULL) {
		logcritical("conn is dying");
		return -1;
	}

	ci->update_current_op_count();

	pingpong_req req;
	if (!unseri_message(*pack, req)) {
		logcritical("cannot unseri pingpong req, id:%d", ci->id);
		return -1;
	}

	pingpong_resp resp;
	resp.set_num(req.num());
	conn->put(cmd_pingpong, resp);

	return 0;
}

int producer_handler::handle_producer_register(tcpconn_ptr conn, decoder* pack)
{
	producer_register_req req;
	if (!unseri_message(*pack, req)) {
		logcritical("cannot unseri producer register");
		return -1;
	}

	int id = req.id();

	conn_info* ci = conn_manager::ref().producer_info(id);
	if (ci) {
		// re-login
		logdebug("id:%d re-login", id);
		ci->conn->stop();
		conn_manager::ref().delete_producer(id);
	}

	conn_manager::ref().insert_producer(id, conn);
	
	logdebug("send procuder %d register resp", id);
	producer_register_resp resp;
	resp.set_id(id);
	resp.set_res(0);
	conn->put(cmd_producer_register, resp);

	return 0;
}




