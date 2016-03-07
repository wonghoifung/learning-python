//
//  Created by huanghaifeng on 16-3-3.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "job_scheduler.h"
#include "conn_manager.h"
#include "redisdao.h"
#include "command.h"
#include "config.h"
#include "consume_url_req.pb.h"
#include "shared/utils/common_globals.h"
#include <boost/bind.hpp>

using namespace spider;

job_scheduler::job_scheduler() :schtimer(global_io_service::ref().get())
{
	consume_req_count = 0;
	consume_resp_count = 0;
}

job_scheduler::~job_scheduler()
{
	stop_schedule_timer();
}

void job_scheduler::start_schedule_timer()
{
	boost::system::error_code e;
	schtimer.expires_from_now(boost::posix_time::seconds(config::ref().schedule_timeout()), e);
	schtimer.async_wait(boost::bind(&job_scheduler::on_schedule_timeout, this, boost::asio::placeholders::error));
}

void job_scheduler::stop_schedule_timer()
{
	boost::system::error_code e;
	schtimer.cancel(e);
}

job_scheduler& job_scheduler::ref()
{
	static job_scheduler js;
	return js;
}

void job_scheduler::init()
{
	start_schedule_timer();
}

void job_scheduler::on_schedule_timeout(const boost::system::error_code& error)
{
	if (error)
	{
		return;
	}
	schedule();
	start_schedule_timer();
}

void job_scheduler::schedule()
{
	std::map<int, int>& ccm = conn_manager::ref().consumer_cap_map();
	logdebug("consumer count: %d, pending count: %d, failed count: %d", 
		ccm.size(), redisdao::ref().url_queue_count(), redisdao::ref().failed_url_queue_count());
	if (ccm.size()) // there are some consumers
	{
		std::map<int, int>::iterator it = ccm.begin();
		for (; it != ccm.end(); ++it)
		{
			int cap = it->second;
			
			if (cap == 0)
			{
				logdebug("consume, req_cnt:%d, resp_cnt:%d", consume_req_count, consume_resp_count);
				continue; // this consumer is busy
			}

			int id = it->first;
			conn_info* ci = conn_manager::ref().consumer_info(id);
			if (ci)
			{
				consume_url_req req;
				for (int i = 0; i < cap; i++)
				{
					std::string url = redisdao::ref().url_dequeue();
					if (url == "")
					{
						url = redisdao::ref().failed_url_dequeue();
						if (url == "") break;
					}
					req.add_urls(url);
				}
				consume_req_count += 1;
				ci->conn->put(cmd_consume_url, req); // dispatch job
				conn_manager::ref().sub_consumer_cap(id, req.urls_size()); // modify the capacity of the consumer
				if (req.urls_size() < cap) return; // no more url need to be consumed
			}
		}
	}
}
