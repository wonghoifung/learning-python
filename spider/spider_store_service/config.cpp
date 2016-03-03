//
//  Created by huanghaifeng on 16-3-3.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#include "config.h"
#include "shared/utils/tinyxml2.h"
#include "shared/utils/logger.h"
#include "shared/utils/common_globals.h"
#include <assert.h>
#include <json/json.h>

using namespace tinyxml2;

static int get_int_attr(XMLElement* node, const char* attrname)
{
	const XMLAttribute* attr = node->FirstAttribute();
	while (attr)
	{
		if (strcmp(attr->Name(), attrname) == 0)
		{
			return str2int(attr->Value());
		}
		attr = attr->Next();
	}
	assert(0);
	return -1;
}

static bool init_reloadable(XMLElement* scene)
{
	// load logger node
	{
		XMLElement* logger_node = scene->FirstChildElement("logger");
		XMLElement* level_node = logger_node->FirstChildElement("level");
		config::ref().set_logger_level(str2int(level_node->GetText()));
		logstr("[config] logger level is %d", config::ref().logger_level());
	}

	return true;
}

config::config():pid_(-1), nodeid_(-1), logger_level_(ll_debug)
{

}

config::~config()
{

}

config& config::ref()
{
	static config c;
	return c;
}

bool config::init(const char* cfgfile)
{
	XMLDocument doc;
	doc.LoadFile(cfgfile);

	XMLElement* scene = doc.RootElement();

	// load pid
	{
		pid_ = get_int_attr(scene, "pid");
		logstr("[config] pid is %d", pid_);
		assert(pid_ != -1);
	}

	// load store server node
	{
		XMLElement* store_server_node = scene->FirstChildElement("store_server");

		// load nodeid
		nodeid_ = get_int_attr(store_server_node, "nid");
		logstr("[config] nodeid is %d", nodeid_);
		assert(nodeid_ != -1);

		XMLElement* listen_ip_node = store_server_node->FirstChildElement("listen_ip");
		listen_ip_ = listen_ip_node->GetText();
		logstr("[config] listen ip %s", listen_ip_.c_str());
		assert(listen_ip_.size());

		XMLElement* listen_port_node = store_server_node->FirstChildElement("listen_port");
		listen_port_ = listen_port_node->GetText();
		logstr("[config] listen port %s", listen_port_.c_str());
		assert(listen_port_.size());
	}

	// load mysql node
	{
		XMLElement* mysql_node = scene->FirstChildElement("mysql");

		XMLElement* db_name_node = mysql_node->FirstChildElement("db_name");
		mysql_db_name_ = db_name_node->GetText();
		logstr("[config] db_name is %s", mysql_db_name_.c_str());
		assert(mysql_db_name_.size());

		XMLElement* server_node = mysql_node->FirstChildElement("server");
		mysql_server_ = server_node->GetText();
		logstr("[config] server is %s", mysql_server_.c_str());
		assert(mysql_server_.c_str());

		XMLElement* user_node = mysql_node->FirstChildElement("user");
		mysql_user_ = user_node->GetText();
		logstr("[config] user is %s", mysql_user_.c_str());
		assert(mysql_user_.c_str());

		XMLElement* pass_node = mysql_node->FirstChildElement("pass");
		mysql_pass_ = pass_node->GetText();
		logstr("[config] pass is %s", mysql_pass_.c_str());
		assert(mysql_pass_.c_str());
	}

	return init_reloadable(scene);
}

bool config::reload(const char* cfgfile)
{
	XMLDocument doc;
	doc.LoadFile(cfgfile);

	XMLElement* scene = doc.RootElement();

	return init_reloadable(scene);
}

