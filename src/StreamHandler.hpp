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
#include <mutex>


namespace pylogging
{


template<class DERIVED>
class StreamHandler: public Handler
{
public:
    StreamHandler( std::ostream& out, std::wostream& wout );

    HandlerPtr log( const string_type&  str, const unsigned short level );
    HandlerPtr log( const wstring_type& str, const unsigned short level );

private:
    std::ostream&  m_out;
    std::wostream& m_wout;

    static std::mutex mtx; // must be static
};


class StdOutHandler: public StreamHandler<StdOutHandler>
{
    public:
        StdOutHandler();
};


class StdErrHandler: public StreamHandler<StdErrHandler>
{
    public:
        StdErrHandler();
};


} /* namespace pylogging */


#endif /* STREAM_HANDLER_HPP_ */

