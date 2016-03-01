//
//  logger.h
//  console
//
//  Created by huanghaifeng on 14-11-1.
//  Copyright (c) 2014 wonghoifung. All rights reserved.
//

#ifndef logger_header
#define logger_header

#include <stdio.h>
#include <string>
#include <boost/noncopyable.hpp>
//#include "rwspinlock.h"
#include "spinlock.h"

enum logger_level
{
	ll_critical=0,
	ll_error = 1,
	ll_warning = 2,
	ll_info = 3,
	ll_debug = 4,
};

void set_logger_level(logger_level l);

int logger_print(char* buf, int maxlen, const char* fmt, ...);
bool logger_init(std::string& basename, const std::string& fname, const std::string& path);
/* buggy with std::string */
//bool logger_write(FILE* f, const std::string& prefix1, const std::string& prefix2, int prefix3, const char* cbuf);
//bool logger_write_hex(FILE* f, const std::string& prefix1, const std::string& prefix2, int prefix3, const char* buf, int len);
FILE* logger_openfile(const std::string& basename);

class logger : public boost::noncopyable
{
private:
    logger();
    ~logger();
            
public:
    static logger& ref();
    bool init(const std::string& fname, const std::string& path);
	bool write(logger_level level, const std::string& prefix1, const std::string& prefix2, int prefix3, const char* fmt, ...);
	bool write_hex(logger_level level, const std::string& prefix1, const std::string& prefix2, int prefix3, const char* buf, int len);
            
private:
    FILE* getfile();
    FILE* openfile();
            
private:
    std::string basename_;
	spinlock lock_;
};

#ifdef _WIN32
#define logstr(...)
#define loghex(...)

#define logcritical(...)
#define logerror(...)
#define logwarning(...)
#define loginfo(...)
#define logdebug(...)
#else
#define logstr(fmt,args...) logger::ref().write(ll_critical, __FILE__,__FUNCTION__,__LINE__,fmt,##args)
#define loghex(buf,len) logger::ref().write_hex(ll_critical, __FILE__,__FUNCTION__,__LINE__,buf,len)

#define logcritical(fmt,args...) logger::ref().write(ll_critical, __FILE__,__FUNCTION__,__LINE__,fmt,##args)
#define logerror(fmt,args...) logger::ref().write(ll_error, __FILE__,__FUNCTION__,__LINE__,fmt,##args)
#define logwarning(fmt,args...) logger::ref().write(ll_warning, __FILE__,__FUNCTION__,__LINE__,fmt,##args)
#define loginfo(fmt,args...) logger::ref().write(ll_info, __FILE__,__FUNCTION__,__LINE__,fmt,##args)
#define logdebug(fmt,args...) logger::ref().write(ll_debug, __FILE__,__FUNCTION__,__LINE__,fmt,##args)
#endif

#endif 

