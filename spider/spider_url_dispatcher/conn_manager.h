//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef conn_manager_header
#define conn_manager_header

#include <map>
#include <string>
#include "shared/net/tcpconn.h"
#include "command.h"

class conn_info : private boost::noncopyable
{
public:
	conn_info();
	~conn_info();

	tcpconn_ptr conn;
	CONN_TYPE type;
	int id;

	boost::asio::deadline_timer* idle_timer;
	uint64_t last_op_count;
	uint64_t current_op_count;
	void start_idle_timer();
	void stop_idle_timer();
	void update_current_op_count();
	void on_idle_timeout(const boost::system::error_code& error);
};

typedef std::map<int, conn_info*> connmap_t;

class conn_manager : private boost::noncopyable
{
public:
	static conn_manager& ref();

	// return value: 0 success
	int insert_producer(int id, tcpconn_ptr conn);
	int delete_producer(int id);
	tcpconn_ptr producer_conn(int id);
	conn_info* producer_info(int id);

	int insert_consumer(int id, tcpconn_ptr conn);
	int delete_consumer(int id);
	tcpconn_ptr consumer_conn(int id);
	conn_info* consumer_info(int id);

	bool add_consumer_cap(int id, int addcap);
	bool sub_consumer_cap(int id, int subcap);
	int consumer_cap(int id);
	std::map<int, int>& consumer_cap_map() { return consumer_cap_; }

private:
	conn_manager() {}
	~conn_manager() {}

private:
	connmap_t producers_;
	connmap_t consumers_;

	std::map<int, int> consumer_cap_;
};

#endif

