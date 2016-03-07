//
//  Created by huanghaifeng on 16-3-3.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef job_scheduler_header
#define job_scheduler_header

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

class job_scheduler : private boost::noncopyable
{
private:
	job_scheduler();
	~job_scheduler();
	void start_schedule_timer();
	void stop_schedule_timer();

public:
	int consume_req_count;
	int consume_resp_count;

public:
	static job_scheduler& ref();
	void init();
	void on_schedule_timeout(const boost::system::error_code& error);
	void schedule();

private:
	boost::asio::deadline_timer schtimer;
};

#endif
