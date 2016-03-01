//
//  codec.cpp
//  console
//
//  Created by huanghaifeng on 14-10-1.
//  Copyright (c) 2014 wonghoifung. All rights reserved.
//

#include "codec.h"

/* header: | G_1 | version_1 | command_2 | bodylength_4 | */   

uint8_t codec::G()
{
	uint8_t v;
	read_header_b((char*)&v, sizeof(uint8_t), 0);
	return endian_op(v);
}

uint8_t codec::version()
{
	uint8_t v;
	read_header_b((char*)&v, sizeof(uint8_t), 1);
	return endian_op(v);
}

uint16_t codec::command()
{
	uint16_t cmd;
	read_header_b((char*)&cmd, sizeof(uint16_t), 2);
    return endian_op(cmd);
}
        
uint32_t codec::length()
{
	uint32_t bodylen;
	read_header_b((char*)&bodylen, sizeof(uint32_t), 4);
    return endian_op(bodylen);
}

void codec::set_version(int v)
{
	uint8_t version = endian_op((uint8_t)v);
	write_header_b((char*)&version, sizeof(version), 1);
}

void codec::reset()
{
    readptr_ = c_header_size;
    size_ = c_header_size;
}
     
bool codec::copy_b(const void* inbuf, int len)
{
    if(len > c_buffer_size)
    { return false; }
    reset();
    memcpy(buffer_, inbuf, len);
    size_ = len;
    return true;
}

void codec::begin_b(uint16_t cmd)
{
    reset();

	cmd = endian_op(cmd);
	uint8_t G = 'G';
	uint8_t version = c_default_version;
	uint32_t length = 0;

	write_header_b((char*)&G, sizeof(G), 0);
	write_header_b((char*)&version, sizeof(version), 1);
    write_header_b((char*)&cmd, sizeof(cmd), 2);
	write_header_b((char*)&length, sizeof(length), 4);
}

void codec::end_b()
{
	uint32_t bodylen = static_cast<uint32_t>(size_ - c_header_size);
	bodylen = endian_op(bodylen);
	write_header_b((char*)&bodylen, sizeof(uint32_t), 4);
}

bool codec::read_b(char* outbuf, int len)
{
    if((len + readptr_) > size_ || (len + readptr_) > c_buffer_size)
    { return false; }
    memcpy(outbuf, buffer_ + readptr_, len);
    readptr_ += len;
    return true;
}
        
bool codec::read_del_b(char* outbuf, int len)
{
    if(!read_b(outbuf, len))
    { return false; }
    memmove(buffer_ + readptr_ - len, buffer_ + readptr_, size_ - readptr_);
    readptr_ -= len;
    size_ -= len;
    end_b();
    return true;
}
        
void codec::read_undo_b(int len)
{
    readptr_ -= len;
}
        
char* codec::read_bytes_b(int len)
{
    if((len + readptr_) > size_)
    { return NULL; }
    char* p = &buffer_[readptr_];
    readptr_ += len;
    return p;      
}
        
bool codec::write_b(const char* inbuf, int len)
{
    if((size_ < 0) || ((len + size_) > c_buffer_size))
    { return false; }
    memcpy(buffer_+size_, inbuf, len);
    size_ += len;
    return true;
}
        
bool codec::write_front_b(const char* inbuf, int len)
{
    if((len + size_) > c_buffer_size)
    { return false; }
    memmove(buffer_ + c_header_size + len, buffer_ + c_header_size, size_ - c_header_size);
    memcpy(buffer_ + c_header_size, inbuf, len);
    size_ += len;
    end_b();
    return true;
}
        
bool codec::write_zero_b()
{
    if((size_ + 1) > c_buffer_size)
    { return false; }
    memset(buffer_+size_, '\0', sizeof(char));
    ++size_;
    return true;
}
        
void codec::read_header_b(char* outbuf, int len, int pos)
{
    //if(pos > 0 || pos+len < c_header_size)
	if (pos >= 0 && pos + len <= c_header_size)
    { memcpy(outbuf, buffer_+pos, len); }
}
        
void codec::write_header_b(const char* inbuf, int len, int pos)
{
    //if(pos > 0 || pos+len < c_header_size)
	if (pos >= 0 && pos+len <= c_header_size)
    { memcpy(buffer_+pos, inbuf, len); }
}
        
