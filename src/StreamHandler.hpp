/**
 * @file StreamHandler.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef STREAM_HANDLER_HPP_
#define STREAM_HANDLER_HPP_

#include "Handler.hpp"

#include <iostream>


namespace pylogging
{


class StreamHandler: public Handler
{
public:
    StreamHandler( std::ostream& out, std::wostream& wout );

    HandlerPtr log( const string_type&  str, const unsigned short level );
    HandlerPtr log( const wstring_type& str, const unsigned short level );

private:
    std::ostream&  m_out;
    std::wostream& m_wout;
};


class StdOutHandler: public StreamHandler
{
    public:
        StdOutHandler();
};


class StdErrHandler: public StreamHandler
{
    public:
        StdErrHandler();
};


} /* namespace pylogging */


#endif /* STREAM_HANDLER_HPP_ */

