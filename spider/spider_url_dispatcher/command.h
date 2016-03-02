//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef command_header
#define command_header

enum {
	cmd_pingpong = 0,
	cmd_producer_register = 1,
	cmd_consumer_register = 2,
	cmd_produce_url = 3,
	cmd_consume_url = 4,
	cmd_consumer_capacity = 5,
};

enum CONN_TYPE
{
	CONN_TYPE_UNVERIFIED,
	CONN_TYPE_PRODUCER,
	CONN_TYPE_CONSUMER,
};

#define conn_type_str(t) ((t==CONN_TYPE_PRODUCER)?"producer":((t==CONN_TYPE_CONSUMER)?"consumer":"unverified"))

#endif

