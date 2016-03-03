//
//  Created by huanghaifeng on 16-3-3.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "job_scheduler.h"
#include "conn_manager.h"
#include "redisdao.h"
#include "command.h"
#include "consume_url_req.pb.h"

using namespace spider;

void job_scheduler::schedule()
{
	std::map<int, int>& ccm = conn_manager::ref().consumer_cap_map();
	if (ccm.size()) // there are some consumers
	{
		std::map<int, int>::iterator it = ccm.begin();
		for (; it != ccm.end(); ++it)
		{
			int cap = it->second;
			if (cap == 0) continue; // this consumer is busy
			int id = it->first;
			conn_info* ci = conn_manager::ref().consumer_info(id);
			if (ci)
			{
				consume_url_req req;
				for (int i = 0; i < cap; i++)
				{
					std::string url = redisdao::ref().url_dequeue();
					if (url == "") break; 
					req.add_urls(url);
				}
				ci->conn->put(cmd_consume_url, req); // dispatch job
				conn_manager::ref().sub_consumer_cap(id, req.urls_size()); // modify the capacity of the consumer
				if (req.urls_size() < cap) return; // no more url need to be consumed
			}
		}
	}
}
