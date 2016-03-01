//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef RWSPINLOCK_HEADER
#define RWSPINLOCK_HEADER

#include <boost/noncopyable.hpp>

#ifdef _WIN32
/* not support windows, make visual studio happy */
int __unuse__(...);
#define __sync_synchronize __unuse__
#define __sync_add_and_fetch __unuse__
#define __sync_sub_and_fetch __unuse__
#define __sync_lock_test_and_set __unuse__
#define __sync_lock_release __unuse__
#endif

class rwspinlock : private boost::noncopyable
{
public:
	int write;
	int read;

	rwspinlock() :write(0), read(0)
	{
	}

	void rlock()
	{
		for (;;) 
		{
			while (this->write) 
			{
				__sync_synchronize();
			}

			__sync_add_and_fetch(&this->read, 1);

			if (this->write) 
			{
				__sync_sub_and_fetch(&this->read, 1);
			}
			else 
			{
				break;
			}
		}
	}

	void wlock() 
	{
		while (__sync_lock_test_and_set(&this->write, 1)) { }

		while (this->read) 
		{
			__sync_synchronize();
		}
	}

	void wunlock() 
	{
		__sync_lock_release(&this->write);
	}

	void runlock() 
	{
		__sync_sub_and_fetch(&this->read, 1);
	}
};

class rwspinlock_guard : private boost::noncopyable
{
public:
	rwspinlock_guard(rwspinlock& lock, bool write = true) :lock_(lock), iswrite_(write)
	{
		if (iswrite_)
		{
			lock_.wlock();
		}
		else
		{
			lock_.rlock();
		}
	}

	~rwspinlock_guard()
	{
		if (iswrite_)
		{
			lock_.wunlock();
		}
		else
		{
			lock_.runlock();
		}
	}

private:
	rwspinlock& lock_;
	bool iswrite_;
};

#endif
