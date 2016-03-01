//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef ASIOTHREAD_SESSION_HEADER
#define ASIOTHREAD_SESSION_HEADER

#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <deque>
#include "latch.h"
#include "asiothread_message.h"

class asiothread_session;
typedef boost::asio::local::stream_protocol::socket localsocket;
typedef std::deque<asiothread_message> asiothread_message_queue;
typedef boost::function<void(asiothread_session*, asiothread_message&)> asiothread_message_callback;

class asiothread_session
{
public:
	asiothread_session(boost::asio::io_service& ios, asiothread_message_callback cb);
	~asiothread_session();
	void start();
	localsocket& sock() { return socket_; }
	void make_conn_pair(localsocket& mainsock);
	void send_from_this_thread(const asiothread_message& msg);
	void close_from_other_thread();

protected:
	void handle_read_header(const boost::system::error_code& error);
	void handle_read_body(const boost::system::error_code& error);
	void handle_write(const boost::system::error_code& error);

	void do_write(asiothread_message msg);
	void do_close();

private:
	boost::asio::io_service& io_service_;
	localsocket socket_;
	asiothread_message read_msg_;
	asiothread_message_queue write_msgs_;
	asiothread_message_callback on_message_;
};

#endif

