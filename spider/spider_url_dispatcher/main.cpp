//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <boost/bind.hpp>
#include "dispatcher.h"
#include "config.h"
#include "redisdao.h"
#include "shared/utils/logger.h"
#include "shared/utils/pid_file.h"
#include "shared/utils/common_globals.h"

void init_rand()
{
	srand(time(0));
	for (size_t i = 0; i < 8; ++i) { rand(); }
}

bool init_redis()
{
	redisdao::ref().set_ip(config::ref().redis_ip());
	redisdao::ref().set_port((uint16_t)str2int(config::ref().redis_port()));
	return redisdao::ref().connect();
}

int main(int argc, char* argv[])
{
	create_pid_file();
	set_rlimit();

	if (!logger::ref().init("s_dispatcher", "./"))
	{
		logcritical("init logger error");
		return -1;
	}

	init_rand();

	if (!config::ref().init("../config/config.xml"))
	{
		logcritical("init config error");
		return -1;
	}
	set_logger_level((logger_level)config::ref().logger_level());

	if (!init_redis())
	{
		logcritical("cannot init redis");
		return -1;
	}

	boost::asio::io_service io_service;
	global_io_service::ref().init(io_service);

	const std::string& ip = config::ref().listen_ip();
	const std::string& port = config::ref().listen_port();

	dispatcher s(io_service, ip, port);

	io_service.run();

	return 0;
}

