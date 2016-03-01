//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef ASIOTHREAD_HEADER
#define ASIOTHREAD_HEADER

#include "asiothread_session.h"

class asiothread : public boost::noncopyable
{
	typedef boost::thread thread_t;
	typedef boost::shared_ptr<thread_t> thread_ptr;

public:
	asiothread(asiothread_message_callback cb);
	~asiothread();
	void init(localsocket& mainsock);
	void join();
	void run();
	void close_from_main_thread();

private:
	boost::asio::io_service io_service_;
	asiothread_session session_;
	thread_ptr thread_;
	latch initdone_;
};

#endif

