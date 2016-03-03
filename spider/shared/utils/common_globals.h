//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef COMMON_GLOBALS_HEADER
#define COMMON_GLOBALS_HEADER

#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/resource.h>
#include <uuid/uuid.h>
#include <boost/asio.hpp>
//#include "shared/net/tcpconn.h"
#include "shared/utils/logger.h"

inline int str2int(const std::string& str)
{
	int ret = 0;
	std::stringstream ss;
	ss << str;
	ss >> ret;
	return ret;
}

class global_io_service : private boost::noncopyable
{
public:
	static global_io_service& ref()
	{
		static global_io_service gis;
		return gis;
	}

	void init(boost::asio::io_service& ios)
	{
		assert(ios_ == NULL);
		ios_ = &ios;
	}

	boost::asio::io_service& get()
	{
		assert(ios_ != NULL);
		return *ios_;
	}

private:
	global_io_service():ios_(NULL) {}
	~global_io_service() {}
	boost::asio::io_service* ios_;
};

#ifdef _WIN32
#define snprintf 
#endif

inline void set_rlimit()
{
	struct rlimit rlim, rlim_new;

	if (getrlimit(RLIMIT_NOFILE, &rlim) == 0)
	{
		rlim_new.rlim_cur = rlim_new.rlim_max = 100000;
		if (setrlimit(RLIMIT_NOFILE, &rlim_new) != 0)
		{
			printf("set rlimit file failure\n");
			exit(0);
		}
	}

	if (getrlimit(RLIMIT_CORE, &rlim) == 0)
	{
		rlim_new.rlim_cur = rlim_new.rlim_max = RLIM_INFINITY;
		if (setrlimit(RLIMIT_CORE, &rlim_new) != 0)
		{
			printf("set rlimit core failure\n");
			exit(0);
		}
	}
}

inline void tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters)
{
	std::string::size_type lastpos = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos = str.find_first_of(delimiters, lastpos);
	while (std::string::npos != pos || std::string::npos != lastpos)
	{
		tokens.push_back(str.substr(lastpos, pos - lastpos));
		lastpos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastpos);
	}
}

#define UUID_BYTE_COUNT 32
#define UUID_WORD_COUNT (UUID_BYTE_COUNT>>1)
inline void get_uuid(char* buf, size_t len = UUID_BYTE_COUNT)
{
	assert(len >= UUID_BYTE_COUNT);
	uuid_t uu;
	uuid_generate(uu);
	for (size_t i = 0; i < UUID_WORD_COUNT; ++i)
	{
		sprintf(buf + i * 2, "%02X", uu[i]);
	}
}

#endif

