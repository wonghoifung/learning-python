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

#define URL_HASHMAP_PREFIX "spider_url_map_"
static std::string url_hashmap_key()
{
	std::stringstream sskey;
	sskey << URL_HASHMAP_PREFIX << config::ref().pid();
	return sskey.str();
}

bool redisdao::url_hexists(const std::string& url)
{
	if (!ctx_) { return false; }
	std::string key = url_hashmap_key();
	redisReply* reply = (redisReply*)redisCommand(ctx_, "HEXISTS %s %s", key.c_str(), url.c_str());
	if (!reply)
	{
		logstr("error: %s", ctx_->errstr);
		return false;
	}
	bool res = false;
	if (reply->type == REDIS_REPLY_INTEGER) 
	{
		res = (bool)(reply->integer);
	}
	freeReplyObject(reply);
	return res;
}

bool redisdao::url_hset(const std::string& url, int extracted_info)
{
	if (!ctx_) { return false; }
	std::string key = url_hashmap_key();
	redisReply* reply = (redisReply*)redisCommand(ctx_, "HSET %s %s %d", key.c_str(), url.c_str(), extracted_info);
	if (!reply)
	{
		logstr("error: %s", ctx_->errstr);
		return false;
	}
	bool ret = (reply->type == REDIS_REPLY_INTEGER);
	freeReplyObject(reply);
	return ret;
}

#define PENDING_QUEUE_PREFIX "spider_pending_queue_"
static std::string pending_queue_key()
{
	std::stringstream sskey;
	sskey << PENDING_QUEUE_PREFIX << config::ref().pid();
	return sskey.str();
}

bool redisdao::url_enqueue(const std::string& url)
{
	if (!ctx_) { return false; }
	std::string key = pending_queue_key();
	redisReply* reply = (redisReply*)redisCommand(ctx_, "LPUSH %s %s", key.c_str(), url.c_str());
	if (!reply)
	{
		logstr("error: %s", ctx_->errstr);
		return false;
	}
	bool ret = (reply->type == REDIS_REPLY_INTEGER);
	freeReplyObject(reply);
	return ret;
}

std::string redisdao::url_dequeue()
{
	if (!ctx_) { return ""; }
	std::string key = pending_queue_key();
	redisReply* reply = (redisReply*)redisCommand(ctx_, "RPOP %s", key.c_str());
	if (!reply)
	{
		logstr("error: %s", ctx_->errstr);
		return "";
	}
	std::string url;
	if (reply->type == REDIS_REPLY_STRING)
	{
		url = std::string(reply->str, reply->len);
	}
	freeReplyObject(reply);
	return url;
}

const int redisdao::url_queue_count()
{
	if (!ctx_) return 0;
	std::string key = pending_queue_key();
	redisReply* reply = (redisReply*)redisCommand(ctx_, "LLEN %s", key.c_str());
	if (!reply)
	{
		logstr("error: %s", ctx_->errstr);
		return 0;
	}
	int ret = 0;
	if (reply->type == REDIS_REPLY_INTEGER)
	{
		ret = reply->integer;
	}
	freeReplyObject(reply);
	return ret;
}

bool redisdao::connect()
{
	if (ctx_) { return false; }
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	ctx_ = redisConnectWithTimeout(ip_.c_str(), port_, timeout); 
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

