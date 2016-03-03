//
//  Created by huanghaifeng on 16-3-3.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include <concurrency/ThreadManager.h>
#include <concurrency/PosixThreadFactory.h>
#include <protocol/TBinaryProtocol.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>
#include <server/TNonblockingServer.h>
#include "store_service.h"
#include "store_constants.h"
#include "store_types.h"
#include "config.h"
#include "shared/utils/logger.h"
#include "shared/utils/pid_file.h"
#include "shared/utils/common_globals.h"
#include "store_service_handler.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

void init_rand()
{
	srand(time(0));
	for (size_t i = 0; i < 8; ++i) { rand(); }
}

int main(int argc, char **argv) {
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

	int port = str2int(config::ref().listen_port());

	shared_ptr<store_service_handler> handler(new store_service_handler());
	shared_ptr<TProcessor> processor(new store_serviceProcessor(handler));
	shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(5);
	shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
	threadManager->threadFactory(threadFactory);
	threadManager->start();

	TNonblockingServer server(processor, protocolFactory, port, threadManager);
	server.serve();

	return 0;
}

