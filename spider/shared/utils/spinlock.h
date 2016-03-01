//
//  Created by huanghaifeng on 15-11-23.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef SPINLOCK_HEADER
#define SPINLOCK_HEADER

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

class spinlock :private boost::noncopyable
{
private:
	int l;
public:
	spinlock() :l(0)
	{

	}
	~spinlock()
	{

	}
	void lock()
	{
		while (__sync_lock_test_and_set(&l, 1))
		{

		}
	}
	void unlock()
	{
		__sync_lock_release(&l);
	}
};

class spinlock_guard : private boost::noncopyable
{
public:
	spinlock_guard(spinlock& lock) :lock_(lock)
	{
		lock_.lock();
	}

	~spinlock_guard()
	{
		lock_.unlock();
	}

private:
	spinlock& lock_;
};

#endif

