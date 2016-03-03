//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef config_header
#define config_header

#include <string>
#include "boost/noncopyable.hpp"

class config : private boost::noncopyable
{
private:
	config();
	~config();

public:
	static config& ref();
	bool init(const char* cfgfile);
	bool reload(const char* cfgfile);

	const int& pid() const { return pid_; }
	const int& nodeid() const { return nodeid_; }
	
	const std::string& listen_ip() const { return listen_ip_; }
	const std::string& listen_port() const { return listen_port_; }
	const int& pingpong_timeout() const { return pingpong_timeout_; }
	
	const std::string& redis_ip() const { return redis_ip_; }
	const std::string& redis_port() const { return redis_port_; }

	const int consumer_cap() const { return consumer_cap_; }
	void set_consumer_cap(int i) { consumer_cap_ = i; }

	const int logger_level() const { return logger_level_; }
	void set_logger_level(int i) { logger_level_ = i; }

private:
	int pid_;
	int nodeid_;
	
	std::string listen_ip_;
	std::string listen_port_;
	int pingpong_timeout_;

	std::string redis_ip_;
	std::string redis_port_;

	int consumer_cap_;

	int logger_level_;
};

#endif

