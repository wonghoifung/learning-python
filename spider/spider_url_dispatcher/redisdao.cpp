//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "redisdao.h"
#include "shared/utils/logger.h"
#include "shared/utils/common_globals.h"
#include "config.h"
#include <sstream>
#include <time.h>
#include <sys/time.h>

redisdao::redisdao() 
	:ip_(config::ref().redis_ip()), 
	port_((uint16_t)str2int(config::ref().redis_port())), 
	ctx_(NULL)
{
}

redisdao::~redisdao()
{
	disconnect();
}

bool redisdao::_del_key(const char* key)
{
	if (!ctx_) { return false; }
	redisReply* reply = (redisReply*)redisCommand(ctx_, "DEL %s", key);
	if (!reply)
	{
		logstr("error: %s", ctx_->errstr);
		return false;
	}
	bool ret = (reply->type == REDIS_REPLY_INTEGER);
	freeReplyObject(reply);
	return ret;
}

bool redisdao::connect()
{
	if (ctx_) { return false; }
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	ctx_ = redisConnectWithTimeout(ip_.c_str(), port_, timeout); // TODO
	if (ctx_ == NULL || ctx_->err) {
		if (ctx_) {
			logstr("Connection error: %s", ctx_->errstr);
			redisFree(ctx_);
		}
		else {
			logstr("Connection error: can't allocate redis context");
		}
		return false;
	}
	return true;
}

void redisdao::disconnect()
{
	if (ctx_)
	{
		redisFree(ctx_);
		ctx_ = NULL;
	}
}

