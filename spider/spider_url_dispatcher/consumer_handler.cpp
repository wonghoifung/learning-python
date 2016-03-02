//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "consumer_handler.h"
#include "command.h"
#include "redisdao.h"
#include "globals.h"
#include "shared/net/tcpclient.h"
#include "shared/utils/common_globals.h"
#include "shared/utils/logger.h"
#include "shared/protocol/pbcodec.h"
#include "config.h"
#include "pingpong_req.pb.h"
#include "pingpong_resp.pb.h"
#include "consume_url_req.pb.h"
#include "consume_url_resp.pb.h"
#include "consumer_register_req.pb.h"
#include "consumer_register_resp.pb.h"
#include <json/json.h>
#include <boost/shared_array.hpp>
#include <boost/bind.hpp>

using namespace spider;

consumer_handler::consumer_handler()
{

}

consumer_handler::~consumer_handler()
{

}

void consumer_handler::on_connect(tcpconn_ptr conn)
{

}

void consumer_handler::on_close(tcpconn_ptr conn, const int ec, const std::string& msg)
{
	conn_info* ci = extract_conn_info(conn);
	if (ci) {
		conn_manager::ref().delete_consumer(ci->id);
		logdebug("[consumer_handler] %s -> %s closed", conn->localaddr().c_str(), conn->remoteaddr().c_str());
	}
}

int consumer_handler::on_message(tcpconn_ptr conn, decoder* pack)
{
	int cmd = pack->command();
	switch (cmd)
	{
	case cmd_consume_url:
		return handle_consume_url(conn, pack);

	case cmd_pingpong:
		return handle_pingpong(conn, pack);

	default:
		assert(0);
		break;
	}
	return cmd;
}

void consumer_handler::on_highwatermark(tcpconn_ptr conn, size_t size, size_t count)
{
	conn_info* ci = extract_conn_info(conn);
	if (ci == NULL) {
		logcritical("conn is dying");
		return;
	}

	logstr("[consumer_handler] %s -> %s reach highwatermark, closed[id:%d]", conn->localaddr().c_str(), conn->remoteaddr().c_str(), ci->id);
	conn->stop();
	conn_manager::ref().delete_consumer(ci->id); // remove as early as possible
}

int consumer_handler::handle_consume_url(tcpconn_ptr conn, decoder* pack)
{
	conn_info* ci = extract_conn_info(conn);
	if (ci == NULL) {
		logcritical("conn is dying");
		return -1;
	}
	
	ci->update_current_op_count();

	consume_url_resp resp;
	if (!unseri_message(*pack, resp)) {
		logcritical("cannot unseri consume url resp, id:%d", ci->id);
		return -1;
	}

	int res = resp.res();
	if (res != 0) {
		for (int i = 0; i < resp.failed_urls_size(); ++i)
		{
			logcritical("[id:%d] failed url: %s", ci->id, resp.failed_urls(i).c_str());
			redisdao::ref().url_enqueue(resp.failed_urls(i));
		}
	}

	for (int i = 0; i < resp.success_urls_size(); ++i)
	{
		redisdao::ref().url_hset(resp.success_urls(i), 1);
	}

	return 0;
}

int consumer_handler::handle_pingpong(tcpconn_ptr conn, decoder* pack)
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

int consumer_handler::handle_consumer_register(tcpconn_ptr conn, decoder* pack)
{
	consumer_register_req req;
	if (!unseri_message(*pack, req)) {
		logcritical("cannot unseri consumer register");
		return -1;
	}

	int id = req.id();

	conn_info* ci = conn_manager::ref().consumer_info(id);
	if (ci) {
		// re-login
		logdebug("id:%d re-login", id);
		ci->conn->stop();
		conn_manager::ref().delete_consumer(id);
	}

	conn_manager::ref().insert_consumer(id, conn);

	consumer_register_resp resp;
	resp.set_id(id);
	resp.set_res(0);
	conn->put(cmd_consumer_register, resp);

	return 0;
}

