//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef TCPCONN_BASE_HEADER
#define TCPCONN_BASE_HEADER

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>
#include "buffer.h"

#define TCPCONN_LOWWATERMARK (32 * 1024 * 1024)
#define TCPCONN_HIGHWATERMARK (64 * 1024 * 1024)
#define TCPCONN_SEND_BUF_MAX_COUNT (10000)

class tcpconn_base;
typedef boost::shared_ptr<tcpconn_base> tcpconn_base_ptr;

class tcpconn_base
	: public boost::enable_shared_from_this<tcpconn_base>,
	  private boost::noncopyable
{
public:
	explicit tcpconn_base(const boost::asio::io_service& io_service);
	virtual ~tcpconn_base();
	
	boost::asio::ip::tcp::socket& socket();

	void start();
	void stop();
	void connect(const std::string& host, const std::string& port);

	int send(const char* data, size_t len);
	void receive();

	int set_sndbuf_size(int size, bool force = false);
	int set_rcvbuf_size(int size, bool force = false);

	const bool lowwatermark() const { return pending_send_bufsize_ > TCPCONN_LOWWATERMARK; }
	const bool overload() const { return pending_send_bufsize_ > TCPCONN_HIGHWATERMARK || buffers_.size() > TCPCONN_SEND_BUF_MAX_COUNT; }

	void set_remoteaddr(const std::string& addr) { remoteaddr_ = addr; }
	const std::string& remoteaddr() const { return remoteaddr_; }

	void set_localaddr(const std::string& addr) { localaddr_ = addr; }
	const std::string& localaddr() const { return localaddr_; }

	void set_ud(void* ud) { ud_ = ud; }
	const void* ud() const { return ud_; }

	void set_id(int id) { id_ = id; }
	const int id() const { return id_; }

	virtual void on_connect(tcpconn_base_ptr) = 0;
	virtual void on_close(tcpconn_base_ptr, const int, const std::string&) = 0;
	virtual void on_data(tcpconn_base_ptr, char*, size_t) = 0;
	virtual void on_highwatermark(tcpconn_base_ptr, size_t, size_t) = 0;

protected:
	void handle_connect(const boost::system::error_code& e);
	void handle_read(const boost::system::error_code& e, std::size_t bytes_transferred);
	void handle_write(const boost::system::error_code& e, std::size_t bytes_transferred);
	void handle_close(const int e, const std::string& msg = "");
	void close_read();

private:
	boost::asio::ip::tcp::socket socket_;
	boost::array<char, 8192> buffer_;
	bufferlist_t buffers_;
	size_t pending_send_bufsize_;

	int readcnt_;
	int writecnt_;
	bool readclosed_;

	std::string remoteaddr_;
	std::string localaddr_;

	int id_;
	void* ud_;
};

#endif

