//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "conn_manager.h"
#include "config.h"
#include "shared/utils/common_globals.h"
#include "shared/utils/logger.h"
#include <boost/bind.hpp>

conn_info::conn_info() :type(CONN_TYPE_UNVERIFIED), id(-1), idle_timer(NULL), last_op_count(0), current_op_count(0)
{
	start_idle_timer();
}

conn_info::~conn_info()
{
	stop_idle_timer();
}

void conn_info::start_idle_timer()
{
	if (!idle_timer)
	{
		idle_timer = new boost::asio::deadline_timer(global_io_service::ref().get());
	}
	boost::system::error_code e;
	idle_timer->expires_from_now(boost::posix_time::seconds(config::ref().pingpong_timeout()), e);
	idle_timer->async_wait(boost::bind(&conn_info::on_idle_timeout, this, boost::asio::placeholders::error));
}

void conn_info::stop_idle_timer()
{
	if (idle_timer)
	{
		boost::system::error_code e;
		idle_timer->cancel(e);
		delete idle_timer;
		idle_timer = NULL;
	}
}

void conn_info::update_current_op_count()
{
	current_op_count += 1;
}

void conn_info::on_idle_timeout(const boost::system::error_code& error)
{
	if (error)
	{
		return;
	}

	if (current_op_count == last_op_count)
	{
		logstr("%s %d timeout, close %s", conn_type_str(type), id, conn->remoteaddr().c_str());
		conn->stop();
	}
	else
	{
		last_op_count = current_op_count;
		start_idle_timer();
	}
}

conn_manager& conn_manager::ref()
{
	static conn_manager bm;
	return bm;
}

int conn_manager::insert_producer(int id, tcpconn_ptr conn)
{
	//delete_producer(id);
	conn_info* info = new conn_info();
	info->conn = conn;
	info->type = CONN_TYPE_PRODUCER;
	info->id = id;
	conn->set_id(id);
	conn->set_ud(info);
	return producers_.insert(std::make_pair(id, info)).second ? 0 : 1;
}

int conn_manager::delete_producer(int id)
{
	connmap_t::iterator it = producers_.find(id);
	if (it != producers_.end())
	{
		it->second->conn->set_id(0);
		it->second->conn->set_ud(NULL);
		it->second->stop_idle_timer();
		delete it->second;
		producers_.erase(it);
	}
	return 0;
}

tcpconn_ptr conn_manager::producer_conn(int id)
{
	conn_info* info = producer_info(id);
	if (info) {
		return info->conn;
	}
	else {
		return tcpconn_ptr(); // null
	}
}

conn_info* conn_manager::producer_info(int id)
{
	connmap_t::iterator it = producers_.find(id);
	if (it == producers_.end())
	{
		return NULL;
	}
	return it->second;
}

int conn_manager::insert_consumer(int id, tcpconn_ptr conn)
{
	//delete_consumer(id);
	conn_info* info = new conn_info();
	info->conn = conn;
	info->type = CONN_TYPE_CONSUMER;
	info->id = id;
	conn->set_id(id);
	conn->set_ud(info);
	add_consumer_cap(id, config::ref().consumer_cap());
	return consumers_.insert(std::make_pair(id, info)).second ? 0 : 1;
}

int conn_manager::delete_consumer(int id)
{
	connmap_t::iterator it = consumers_.find(id);
	if (it != consumers_.end())
	{
		it->second->conn->set_id(0);
		it->second->conn->set_ud(NULL);
		it->second->stop_idle_timer();
		delete it->second;
		consumer_cap_.erase(id);
		consumers_.erase(it);
	}
	return 0;
}

tcpconn_ptr conn_manager::consumer_conn(int id)
{
	conn_info* info = consumer_info(id);
	if (info) {
		return info->conn;
	}
	else {
		return tcpconn_ptr(); // null
	}
}

conn_info* conn_manager::consumer_info(int id)
{
	connmap_t::iterator it = consumers_.find(id);
	if (it == consumers_.end())
	{
		return NULL;
	}
	return it->second;
}

bool conn_manager::add_consumer_cap(int id, int addcap)
{
	int& cap = consumer_cap_[id];
	if (cap + addcap > config::ref().consumer_cap()) return false;
	cap += addcap;
	return true;
}

bool conn_manager::sub_consumer_cap(int id, int subcap)
{
	int& cap = consumer_cap_[id];
	if (cap < subcap) return false;
	cap -= subcap;
	return true;
}

int conn_manager::consumer_cap(int id)
{
	return consumer_cap_[id];
}
