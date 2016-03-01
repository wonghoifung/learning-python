//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef BUFFER_HEADER
#define BUFFER_HEADER

#include <memory>
#include <string.h>
#include <list>

class buffer
{
public:
	buffer(const char * p = NULL, size_t len = 0): to_write_byte_(len), transferred_(0)
	{
		memcpy(recv_buffer_, p, len);

#if __CHECK__
		++nObjectCount;
#endif
	}

	~buffer()
	{
#if __CHECK__
		--nObjectCount;

		if (nTime_ != time(NULL))
		{
			nTime_ = time(NULL);
		}
#endif
	}

	char * get()
	{
		return recv_buffer_ + transferred_;
	}

	void read(const size_t toRead)
	{
		to_write_byte_ -= toRead;
		transferred_ += toRead;
	}

	size_t size()const { return to_write_byte_; }

private:
	enum { PACKET_BUFFER_SIZE = 1024 * 8};

	size_t	to_write_byte_;
	size_t	transferred_;
	char	recv_buffer_[PACKET_BUFFER_SIZE];

#if __CHECK__
	static unsigned int nObjectCount;
	static time_t nTime_;
#endif 
};

typedef std::list<buffer*> bufferlist_t;

#endif 




