//
//  Created by huanghaifeng on 16-3-3.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef store_service_handler_header
#define store_service_handler_header

#include "store_service.h"
#include "store_constants.h"
#include "store_types.h"

class store_service_handler : virtual public store_serviceIf {
public:
	store_service_handler();
	int32_t put(const movie_info& info);

};

#endif
