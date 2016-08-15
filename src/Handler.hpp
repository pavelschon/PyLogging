/**
 * @file Handler.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef HANDLER_HPP_
#define HANDLER_HPP_

#include "PyLogging.hpp"


namespace pylogging
{


class Handler: public boost::enable_shared_from_this<Handler>, public boost::noncopyable
{
public:
    virtual ~Handler();

    virtual HandlerPtr log( const string_type&  str, const unsigned short level ) = 0;
    virtual HandlerPtr log( const wstring_type& str, const unsigned short level ) = 0;

    void setLevel( const unsigned short level );

protected:
    unsigned short m_level = NOTSET;
};


class NullHandler: public Handler
{
public:
    HandlerPtr log( const string_type&  str, const unsigned short level );
    HandlerPtr log( const wstring_type& str, const unsigned short level );
};


} /* namespace pylogging */


#endif /* HANDLER_HPP_ */

