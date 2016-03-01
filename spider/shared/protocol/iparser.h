//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef IPARSER_HEADER
#define IPARSER_HEADER

class iparser
{
public:
	virtual ~iparser() {}
	virtual int parse(const char* data, const size_t length) = 0;
};

#endif
