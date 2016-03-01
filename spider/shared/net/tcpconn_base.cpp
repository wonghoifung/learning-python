//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#include "tcpconn_base.h"
#include "shared/utils/logger.h"
#include <boost/bind.hpp>

tcpconn_base::tcpconn_base(const boost::asio::io_service& io_service) : 
	socket_(const_cast<boost::asio::io_service&>(io_service)), 
	pending_send_bufsize_(0),
	readcnt_(0),
	writecnt_(0),
	readclosed_(false),
	id_(0),
	ud_(NULL)
{

}

tcpconn_base::~tcpconn_base()
{
	bufferlist_t::iterator it = buffers_.begin();
	for (; it != buffers_.end(); ++it)
	{
		delete *it;
	}
	buffers_.clear();
}

boost::asio::ip::tcp::socket& tcpconn_base::socket()
{
	return socket_;
}

void tcpconn_base::start()
{
	boost::system::error_code e;

//	boost::asio::socket_base::keep_alive op(true);
//	socket().set_option(op, e);
//
//#if !_WIN32
//	{
//		typedef boost::asio::detail::socket_option::integer<IPPROTO_TCP, TCP_KEEPIDLE> keep_aliveidle;
//		socket().set_option(keep_aliveidle(60), e);
//	}
//
//	{
//		typedef boost::asio::detail::socket_option::integer<IPPROTO_TCP, TCP_KEEPINTVL> keep_aliveintvl;
//		socket().set_option(keep_aliveintvl(30), e);
//	}
//
//	{
//		typedef boost::asio::detail::socket_option::integer<IPPROTO_TCP, TCP_KEEPCNT> keep_alivecnt;
//		socket().set_option(keep_alivecnt(3), e);
//	}
//#endif

	boost::asio::socket_base::linger lingeroption(true, 0);
	socket().set_option(lingeroption, e);

	boost::asio::ip::tcp::no_delay option(true);
	socket().set_option(option, e);

	receive();
}

void tcpconn_base::stop()
{
	if (writecnt_ > 0)
	{
		close_read();
	}
	else
	{
		//logstr("call from tcpconn_base::stop");
		handle_close(0);
	}
}

void tcpconn_base::connect(const std::string& host, const std::string& port)
{
	socket_.async_connect(
		boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), static_cast<unsigned short>(atoi(port.c_str()))), 
		boost::bind(&tcpconn_base::handle_connect, shared_from_this(), boost::asio::placeholders::error));
}

int tcpconn_base::send(const char* data, size_t len)
{
	if (!readclosed_)
	{
		if (overload())
		{
			logstr("WARNING: data send from %s to %s pending buffer size %um, count:%u",
				localaddr().c_str(),
				remoteaddr().c_str(),
				pending_send_bufsize_ / 1024 / 1024,
				buffers_.size());

			on_highwatermark(shared_from_this(), pending_send_bufsize_, buffers_.size());
		}

		buffers_.push_back(new buffer(data, len));
		pending_send_bufsize_ += len;

		if (writecnt_ == 0)
		{
			socket_.async_send(boost::asio::buffer(buffers_.front()->get(), buffers_.front()->size()),
				boost::bind(&tcpconn_base::handle_write, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
			++writecnt_;
		}
	}
	return 0;
}

void tcpconn_base::receive()
{
	socket_.async_read_some(boost::asio::buffer(buffer_),
		boost::bind(&tcpconn_base::handle_read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
	++readcnt_;
}

int tcpconn_base::set_sndbuf_size(int size, bool force)
{
	boost::system::error_code e;
	if (force)
	{
		boost::asio::socket_base::send_buffer_size op(size);
		socket().set_option(op, e);
	}
	else
	{
		boost::asio::socket_base::send_buffer_size sbs;
		socket().get_option(sbs, e);

		if (e.value() != 0 || sbs.value() < size)
		{
			boost::asio::socket_base::send_buffer_size op(size);
			socket().set_option(op, e);
		}
	}
	return e.value();
}

int tcpconn_base::set_rcvbuf_size(int size, bool force)
{
	boost::system::error_code e;
	if (force)
	{
		boost::asio::socket_base::receive_buffer_size  op(size);
		socket().set_option(op, e);
	}
	else
	{
		boost::asio::socket_base::receive_buffer_size rbs;
		socket().get_option(rbs, e);

		if (e.value() != 0 || rbs.value() < size)
		{
			boost::asio::socket_base::receive_buffer_size  op(size);
			socket().set_option(op, e);
		}
	}
	return e.value();
}

void tcpconn_base::handle_connect(const boost::system::error_code& e)
{
	on_connect(shared_from_this());
	receive();
}

void tcpconn_base::handle_read(const boost::system::error_code& e, std::size_t bytes_transferred)
{
	--readcnt_;
	if (e.value() == 0 && !readclosed_)
	{
		on_data(shared_from_this(), buffer_.data(), bytes_transferred);
		receive();
	}
	else
	{
		//logstr("call from tcpconn_base::handle_read, %d, %s", e.value(), e.message().c_str());
		handle_close(e.value(), e.message());
	}
}

void tcpconn_base::handle_write(const boost::system::error_code& e, std::size_t bytes_transferred)
{
	--writecnt_;
	assert(writecnt_ >= 0 && readcnt_ >= 0);
	if (e.value() != 0)
	{
		//logstr("call from tcpconn_base::handle_write 1");
		handle_close(e.value(), e.message());
	}
	else
	{
		buffer* p = buffers_.front();
		p->read(bytes_transferred);
		if (p->size() == 0)
		{
			buffers_.pop_front();
			delete p;
			p = NULL;
		}
		pending_send_bufsize_ -= bytes_transferred;

		if (!buffers_.empty())
		{
			socket_.async_send(boost::asio::buffer(buffers_.front()->get(), buffers_.front()->size()),
				boost::bind(&tcpconn_base::handle_write, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
			++writecnt_;
		}
		else if (readclosed_ && writecnt_ == 0)
		{
			//logstr("call from tcpconn_base::handle_write 2, readclosed:%d, writecnt_:%d", readclosed_, writecnt_);
			handle_close(0);
		}
	}
}

void tcpconn_base::handle_close(const int e, const std::string& msg)
{
	boost::system::error_code er;
	socket_.close(er);

	if (writecnt_ == 0 && readcnt_ == 0)
	{
		//logstr("writecnt_ and readcnt_ clear...");
		on_close(shared_from_this(), e, msg);
	}
}

void tcpconn_base::close_read()
{
	readclosed_ = true;
	boost::system::error_code e;
	socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_receive, e);
}

