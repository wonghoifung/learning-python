//
//  Created by huanghaifeng on 16-3-3.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "store_service_handler.h"
#include "shared/utils/logger.h"
#include "mysqlconn_pool.h"
#include <assert.h>
#include <stdlib.h> 
#include <pthread.h>

static pthread_once_t ponce_ = PTHREAD_ONCE_INIT;
static mysqlconn_pool* pool_ = NULL;
static void destroy_dbpool()
{
	delete pool_;
	pool_ = NULL;
}
static void create_dbpool()
{
	pool_ = new mysqlconn_pool(5);
	::atexit(destroy_dbpool);
}
static mysqlconn_pool& dbpool()
{
	pthread_once(&ponce_, &create_dbpool);
	assert(pool_ != NULL);
	return *pool_;
}

store_service_handler::store_service_handler()
{
	logdebug(">>>>>>>>>> a store_service_handler created");
}

#include <boost/regex.hpp>
static std::string normalize_string(const std::string& str)
{
	std::string s1 = "'";
	std::string s2 = "\\\\'"; 
	boost::regex reg(s1);
	std::string res = str;
	std::string ret = boost::regex_replace(res, reg, s2, boost::match_default | boost::format_all);
	return ret;
}

int32_t store_service_handler::put(const movie_info& info)
{
	static const char* fmt = "INSERT INTO test.spider_movie_info(`url`,`movienum`,`initial_release_date`,`big_poster`,`small_poster`,`language`,"
		"`area`,`scriptwriter`,`actor`,`director`,`source`,`imdb`,`year`,`genre`,`runtime`,`moviename`,`otherName`) VALUES ("
		"'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');";

	char sql[8192] = { 0 };
	std::string url = normalize_string(info.url);
	std::string movienum = normalize_string(info.movienum);
	std::string initial_release_date = normalize_string(info.initial_release_date);
	std::string big_poster = normalize_string(info.big_poster);
	std::string small_poster = normalize_string(info.small_poster);
	std::string language = normalize_string(info.language);
	std::string area = normalize_string(info.area);
	std::string scriptwriter = normalize_string(info.scriptwriter);
	std::string actor = normalize_string(info.actor);
	std::string director = normalize_string(info.director);
	std::string source = normalize_string(info.source);
	std::string imdb = normalize_string(info.imdb);
	std::string year = normalize_string(info.year);
	std::string genre = normalize_string(info.genre);
	std::string runtime = normalize_string(info.runtime);
	std::string moviename = normalize_string(info.moviename);
	std::string otherName = normalize_string(info.otherName);
	snprintf(sql, sizeof(sql), fmt, url.c_str(), movienum.c_str(), initial_release_date.c_str(),
		big_poster.c_str(), small_poster.c_str(), language.c_str(), area.c_str(), scriptwriter.c_str(),
		actor.c_str(), director.c_str(), source.c_str(), imdb.c_str(), year.c_str(), genre.c_str(),
		runtime.c_str(), moviename.c_str(), otherName.c_str());
	assert(sql[strlen(sql) - 1] == ';');

	return dbpool().execute(sql);
}
