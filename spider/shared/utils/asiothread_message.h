//
//  Created by huanghaifeng on 15-9-1.
//  Copyright (c) 2015 wonghoifung. All rights reserved.
//
#ifndef ASIOTHREAD_MESSAGE_HEADER
#define ASIOTHREAD_MESSAGE_HEADER

#include <cstdio>
#include <cstdlib>
#include <cstring>

class asiothread_message
{
public:
	enum { max_message_length = 8192 };
	enum { header_length = 4 };
	enum { max_body_length = max_message_length - header_length };

	asiothread_message()
		: body_length_(0), body_read_pos_(0)
	{
	}

	void reset()
	{
		body_length_ = 0;
		body_read_pos_ = 0;
	}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	size_t length() const
	{
		return header_length + body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	void body_length(size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}

	bool decode_header()
	{
		using namespace std; // For strncat and atoi.
		char header[header_length + 1] = "";
		strncat(header, data_, header_length);
		body_length_ = atoi(header);
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}

	void encode_header()
	{
		using namespace std; // For sprintf and memcpy.
		char header[header_length + 1] = "";
		sprintf(header, "%4d", static_cast<int>(body_length_));
		memcpy(data_, header, header_length);
	}

	bool write_int(int val)
	{
		return write_buf_((char*)&val, sizeof(int));
	}

	int read_int()
	{
		int val(0);
		read_buf_((char*)&val, sizeof(int));
		return val;
	}

	bool write_cstring(const char* cstr)
	{
		int len = (int)strlen(cstr);
		write_int(len + 1);
		return write_buf_(cstr, len) && write_zero_();
	}

	char* read_cstring()
	{
		int len = read_int();
		if (len <= 0 || len >= max_body_length)
			return NULL;
		return read_cstring_(len);
	}

	bool write_binary(const char* inbuf, size_t len)
	{
		write_int(len);
		return write_buf_(inbuf, len);
	}

	int read_binary(char* outbuf, int maxlen)
	{
		int len = read_int();
		if (len <= 0)
			return -1;
		if (len > maxlen)
		{
			body_read_pos_ -= len;
			return -1;
		}
		if (read_buf_(outbuf, len))
			return len;
		return 0;
	}

protected:
	bool write_buf_(const char* buf, size_t len)
	{
		if (len + body_length_ > max_body_length)
		{
			return false;
		}
		memcpy(body() + body_length_, buf, len);
		body_length_ += len;
		return true;
	}

	bool read_buf_(char* buf, size_t len)
	{
		if (len + body_read_pos_ > max_body_length ||
			len + body_read_pos_ > body_length_)
		{
			return false;
		}
		memcpy(buf, body() + body_read_pos_, len);
		body_read_pos_ += len;
		return true;
	}

	bool write_zero_()
	{
		return write_buf_("\0", 1);
	}

	char* read_cstring_(size_t len)
	{
		if (len + body_read_pos_ > body_length_)
		{
			return NULL;
		}
		char* p = body() + body_read_pos_;
		body_read_pos_ += len;
		return p;
	}

private:
	char data_[header_length + max_body_length];
	size_t body_length_;
	size_t body_read_pos_;
};

#endif 
