/**
 * @file StreamHandler.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef STREAM_HANDLER_HPP_
#define STREAM_HANDLER_HPP_

#include "Handler.hpp"


namespace pylogging
{


class StdOutHandler: public Handler
{
public:
    HandlerPtr log( const string_type&  str, const unsigned short level );
    HandlerPtr log( const wstring_type& str, const unsigned short level );
};


class StdErrHandler: public Handler
{
public:
    HandlerPtr log( const string_type&  str, const unsigned short level );
    HandlerPtr log( const wstring_type& str, const unsigned short level );
};


} /* namespace pylogging */


#endif /* STREAM_HANDLER_HPP_ */

