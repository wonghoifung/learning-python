//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#include "asiothread.h"
#include <string>
#include <cctype>
#include <iostream>
#include <boost/make_shared.hpp>

asiothread::asiothread(asiothread_message_callback cb) 
	:io_service_(), session_(io_service_, cb), initdone_(1)
{

}

asiothread::~asiothread()
{

}

void asiothread::init(localsocket& mainsock)
{
	session_.make_conn_pair(mainsock);
	thread_ = boost::make_shared<thread_t>(boost::bind(&asiothread::run, this));
	initdone_.wait();
}

void asiothread::join()
{
	thread_->join();
}

void asiothread::run()
{
	initdone_.done();

	session_.start();

	try
	{
		io_service_.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void asiothread::close_from_main_thread()
{
	session_.close_from_other_thread();
}

