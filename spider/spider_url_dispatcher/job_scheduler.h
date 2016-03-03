//
//  Created by huanghaifeng on 16-3-3.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef job_scheduler_header
#define job_scheduler_header

#include <boost/noncopyable.hpp>

class job_scheduler : private boost::noncopyable
{
private:
	job_scheduler() {}
	~job_scheduler() {}

public:
	static void schedule();
};

#endif
