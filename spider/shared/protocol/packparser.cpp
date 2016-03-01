//
//  packparser.cpp
//  console
//
//  Created by huanghaifeng on 14-10-2.
//  Copyright (c) 2014 wonghoifung. All rights reserved.
//

#include "packparser.h"

packparser::packparser(complete_callback cb) : complete_cb_(cb)
{
    buf_ = decoder_.buffer();
    init();
}
        
packparser::~packparser()
{
}
        
int packparser::parse(const char* data, const size_t length)
{
    size_t ndx(0);
    while (ndx < length && state_ != c_error)
    {
        switch (state_)
        {
            case c_header:
                if (!read_header(data, length, ndx))
                { break; }
                        
                if (parse_header() != 0)
                { state_ = c_error; break; }
                else
                { state_ = c_body;/* dont break, go on parsing body */ }
                        
            case c_body:
                if (parse_body(data, length, ndx))
                { state_ = c_done;}
                break;
                        
            default:
                return -1;
        }
                
        if (state_ == c_error) { init(); }
                
        if (state_ == c_done)
        {
            if (complete_cb_) { complete_cb_(&decoder_); }
            init();
        }
    }
    return 0;
}
        
void packparser::init()
{
    state_ = c_header;
    packpos_ = 0;
    bodylen_ = 0;
    decoder_.reset();
}
        
bool packparser::read_header(const char* data, const size_t length, size_t& ndx)
{
    if (0 == ndx) { packpos_ = 0; }
            
    while (packpos_ < c_header_size && ndx < length)
    { buf_[packpos_++] = data[ndx++]; }
            
    if (packpos_ < c_header_size)
    { return false; } 
            
    return true;
}
        
int packparser::parse_header()
{
	uint8_t G = decoder_.G();
	uint8_t version = decoder_.version();

	if (!check_G(G) || !check_valid_version(version))
	{ return -2; }
            
    bodylen_ = decoder_.length();
	//if (bodylen_ < (c_buffer_size - c_header_size))
    if (bodylen_ <= (c_buffer_size - c_header_size))
    { return 0; }
            
    return -4;
}
        
bool packparser::parse_body(const char* data, const size_t length, size_t& ndx)
{
    size_t needlen = (bodylen_ + c_header_size) - packpos_;
    if (needlen <= 0)
    { return true; } /* done */
            
    size_t buflen = length - ndx;
    if (buflen <= 0)
    { return false; }
            
    size_t cplen = buflen < needlen ? buflen : needlen;
    if (!decoder_.append(data + ndx,  static_cast<int>(cplen)))
    { return false; }
            
    packpos_ += cplen;
    ndx += cplen;
            
    if (packpos_ < (bodylen_ + c_header_size))
    { return false; }
            
    return true;
}
