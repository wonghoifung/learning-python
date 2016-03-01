//
//  Created by huanghaifeng on 16-3-1.
//  Copyright (c) 2016 wonghoifung. All rights reserved.
//
#ifndef pbcodec_header
#define pbcodec_header

#include "shared/net/tcpconn.h"
#include "shared/utils/logger.h"
#include <google/protobuf/message.h>

inline bool seri_message(encoder& out, const google::protobuf::Message& message) {
	int byte_size = message.ByteSize();
	if (byte_size > max_body_len) {
		logcritical("message too large...");
		return false;
	}

	uint8_t* start = reinterpret_cast<uint8_t*>(out.body_start());
	uint8_t* end = message.SerializeWithCachedSizesToArray(start);
	int n = end - start;
	if (n != byte_size) {
		logcritical("byte_size consistency error...");
		return false;
	}
	out.tune_size(n);

	return true;
}

inline bool unseri_message(decoder& in, google::protobuf::Message& message) {
	return message.ParseFromArray(in.body_start(), in.length());
}

#endif
