//
//  Created by huanghaifeng on 16-3-3.
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

	const std::string& mysql_db_name() const { return mysql_db_name_; }
	const std::string& mysql_server() const { return mysql_server_; }
	const std::string& mysql_user() const { return mysql_user_; }
	const std::string& mysql_pass() const { return mysql_pass_; }

	const int logger_level() const { return logger_level_; }
	void set_logger_level(int i) { logger_level_ = i; }

private:
	int pid_;
	int nodeid_;
	
	std::string listen_ip_;
	std::string listen_port_;

	std::string mysql_db_name_;
	std::string mysql_server_;
	std::string mysql_user_;
	std::string mysql_pass_;

	int logger_level_;
};

#endif

