//
//  codec.h
//  console
//
//  Created by huanghaifeng on 14-10-1.
//  Copyright (c) 2014 wonghoifung. All rights reserved.
//

#ifndef codec_header
#define codec_header

#include <memory>
#include <string>
#include <cstdarg>
#include <string.h>
#include <stdint.h>
#include "endian_op.h"

enum { c_default_version = 0x01, c_invalid_version };
enum { c_header_size = 8, c_buffer_size = 8192 };
#define max_body_len (c_buffer_size - c_header_size)

inline bool check_G(uint8_t g) 
{
	return g == 'G';
}

inline bool check_valid_version(uint8_t ver)
{
	return (ver >= c_default_version) && (ver < c_invalid_version);
}

class codec
{
public:
    codec(){}
    virtual ~codec(){}
            
    char*       buffer() { return buffer_; }
    const char* cbuffer() const	{ return buffer_; }
    int         size() const { return size_; }

	uint8_t       G();
	uint8_t       version();
    uint16_t      command();
	uint32_t      length();
    
	char* body_start() { return buffer_ + c_header_size; }
	void tune_size(int n) { size_ += n; } // for encoder

	void set_version(int v);
    void reset();
            
protected:
    bool  copy_b(const void* inbuf, int len);
	void  begin_b(uint16_t cmd);
    void  end_b();
            
    bool  read_b(char* outbuf, int len);
    bool  read_del_b(char* outbuf, int len);
    void  read_undo_b(int len);
    char* read_bytes_b(int len);
            
    bool  write_b(const char* inbuf, int len);
    bool  write_front_b(const char* inbuf, int len);
    bool  write_zero_b();
            
    void  read_header_b(char* outbuf, int len, int pos);
    void  write_header_b(const char* inbuf, int len, int pos);
            
private:
    char buffer_[c_buffer_size];
    int size_;
    int readptr_;
};

#endif
