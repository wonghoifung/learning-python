//
//  Created by huanghaifeng on 16-3-1.
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

config::config():pid_(-1), nodeid_(-1), pingpong_timeout_(300), logger_level_(ll_debug)
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

	// load dispatcher node
	{
		XMLElement* dispatcher_node = scene->FirstChildElement("dispatcher");

		// load nodeid
		nodeid_ = get_int_attr(dispatcher_node, "nid");
		logstr("[config] nodeid is %d", nodeid_);
		assert(nodeid_ != -1);

		XMLElement* listen_ip_node = dispatcher_node->FirstChildElement("listen_ip");
		listen_ip_ = listen_ip_node->GetText();
		logstr("[config] listen ip %s", listen_ip_.c_str());
		assert(listen_ip_.size());

		XMLElement* listen_port_node = dispatcher_node->FirstChildElement("listen_port");
		listen_port_ = listen_port_node->GetText();
		logstr("[config] listen port %s", listen_port_.c_str());
		assert(listen_port_.size());

		XMLElement* pingpong_timeout_node = dispatcher_node->FirstChildElement("pingpong_timeout");
		pingpong_timeout_ = str2int(pingpong_timeout_node->GetText());
		logstr("[config] pingpong_timeout is %d", pingpong_timeout_);
		assert(pingpong_timeout_ > 0);
	}

	// load redis node
	{
		XMLElement* redis_node = scene->FirstChildElement("redis");

		XMLElement* ip_node = redis_node->FirstChildElement("ip");
		redis_ip_ = ip_node->GetText();
		logstr("[config] redis ip is %s", redis_ip_.c_str());
		assert(redis_ip_.size());

		XMLElement* port_node = redis_node->FirstChildElement("port");
		redis_port_ = port_node->GetText();
		logstr("[config] redis port is %s", redis_port_.c_str());
		assert(redis_port_.size());
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

