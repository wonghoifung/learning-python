//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef TCPCONN_HEADER
#define TCPCONN_HEADER

#include "shared/protocol/packparser.h"
#include "tcpconn_base.h"
#include "shared/protocol/decoder.h"
#include "shared/protocol/encoder.h"
#include "shared/protocol/pbcodec.h"

class tcpconn_handler;

class tcpconn : public tcpconn_base
{
public:
	explicit tcpconn(const boost::asio::io_service& io_service);
	virtual ~tcpconn();

	int put(int cmd, const google::protobuf::Message& message);
	int send(encoder* pack);
	int send(const char* data, size_t len) { return tcpconn_base::send(data, len); }
	void set_handler(tcpconn_handler* h) { handler_ = h; }
	//void set_connid(const std::string& id) { connid_ = id; }
	//const std::string& connid() const { return connid_; }

protected:
	virtual void on_connect(tcpconn_base_ptr conn);
	virtual void on_close(tcpconn_base_ptr conn, const int ec, const std::string& msg);
	virtual void on_data(tcpconn_base_ptr conn, char* buf, size_t len);
	virtual void on_highwatermark(tcpconn_base_ptr conn, size_t size, size_t count);

	int pack_parse_complete(decoder* pack);

private:
	boost::scoped_ptr<iparser> parser_;
	tcpconn_handler* handler_;
	//std::string connid_;
};

typedef boost::shared_ptr<tcpconn> tcpconn_ptr;

#endif

