//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#include "asiothread_session.h"

asiothread_session::asiothread_session(boost::asio::io_service& ios, asiothread_message_callback cb)
	: io_service_(ios), socket_(ios), on_message_(cb)
{

}

asiothread_session::~asiothread_session()
{

}

void asiothread_session::start()
{
	boost::asio::async_read(socket_,
		boost::asio::buffer(read_msg_.data(), asiothread_message::header_length),
		boost::bind(&asiothread_session::handle_read_header, this,
		boost::asio::placeholders::error));
}

void asiothread_session::make_conn_pair(localsocket& mainsock)
{
	boost::asio::local::connect_pair(mainsock, socket_);
}

void asiothread_session::send_from_this_thread(const asiothread_message& msg)
{
	//io_service_.post(boost::bind(&asiothread_session::do_write, this, msg));
	do_write(msg);
}

void asiothread_session::close_from_other_thread()
{
	io_service_.post(boost::bind(&asiothread_session::do_close, this));
}

void asiothread_session::handle_read_header(const boost::system::error_code& error)
{
	if (!error && read_msg_.decode_header())
	{
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			boost::bind(&asiothread_session::handle_read_body, this,
			boost::asio::placeholders::error));
	}
	else
	{
		do_close();
		throw boost::system::system_error(error);
	}
}

void asiothread_session::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		if (on_message_)
		{
			on_message_(this, read_msg_);
		}

		read_msg_.reset();

		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), asiothread_message::header_length),
			boost::bind(&asiothread_session::handle_read_header, this,
			boost::asio::placeholders::error));
	}
	else
	{
		do_close();
		throw boost::system::system_error(error);
	}
}

void asiothread_session::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		write_msgs_.pop_front();
		if (!write_msgs_.empty())
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
				boost::bind(&asiothread_session::handle_write, this,
				boost::asio::placeholders::error));
		}
	}
	else
	{
		do_close();
		throw boost::system::system_error(error);
	}
}

void asiothread_session::do_write(asiothread_message msg)
{
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(msg);
	if (!write_in_progress)
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
			write_msgs_.front().length()),
			boost::bind(&asiothread_session::handle_write, this,
			boost::asio::placeholders::error));
	}
}

void asiothread_session::do_close()
{
	socket_.close();
}
