//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef redisdao_header
#define redisdao_header

#include <boost/noncopyable.hpp>
#include <hiredis.h>
#include <string>

class redisdao : private boost::noncopyable
{
private:
	redisdao();
	~redisdao();

	bool _del_key(const char* key);

public:
	static redisdao& ref()
	{
		static redisdao dao;
		return dao;
	}

	void set_ip(const std::string& ip) { ip_ = ip; }
	void set_port(uint16_t port) { port_ = port; }

	bool url_hexists(const std::string& url);
	bool url_hset(const std::string& url, int extracted_info);

	bool url_enqueue(const std::string& url);
	std::string url_dequeue();

	const int url_queue_count();

	bool connect();
	void disconnect();
	bool reconnect() { disconnect(); return connect(); }

private:
	std::string ip_;
	uint16_t port_;
	redisContext* ctx_;
};

#endif

