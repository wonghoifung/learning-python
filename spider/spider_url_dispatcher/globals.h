//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef globals_header
#define globals_header

#include "shared/net/tcpconn.h"
#include "conn_manager.h"

inline conn_info* extract_conn_info(tcpconn_ptr conn) 
{
	return (conn_info*)(conn->ud());
}

#endif


