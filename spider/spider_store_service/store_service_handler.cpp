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

int32_t store_service_handler::put(const movie_info& info)
{
	static const char* fmt = "INSERT INTO test.spider_movie_info(`url`,`movienum`,`initial_release_date`,`big_poster`,`small_poster`,`language`,"
		"`area`,`scriptwriter`,`actor`,`director`,`source`,`imdb`,`year`,`genre`,`runtime`,`moviename`,`otherName`) VALUES ("
		"'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');";
	char sql[2048] = { 0 };
	snprintf(sql, sizeof(sql), fmt, info.url.c_str(), info.movienum.c_str(), info.initial_release_date.c_str(),
		info.big_poster.c_str(), info.small_poster.c_str(), info.language.c_str(), info.area.c_str(), info.scriptwriter.c_str(),
		info.actor.c_str(), info.director.c_str(), info.source.c_str(), info.imdb.c_str(), info.year.c_str(), info.genre.c_str(),
		info.runtime.c_str(), info.moviename.c_str(), info.otherName.c_str());
	assert(sql[strlen(sql) - 1] == ';');
	return dbpool().execute(sql);
}
