/**
 * @file Handler.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef HANDLER_HPP_
#define HANDLER_HPP_

#include "PyLogging.hpp"

#include <boost/enable_shared_from_this.hpp>


namespace pylogging
{


class Handler: public boost::enable_shared_from_this<Handler>, public boost::noncopyable
{
public:
    virtual ~Handler();

    virtual HandlerPtr log( const wstring_type& str, const unsigned short level ) = 0;

    void setLevel( const unsigned short level );

protected:
    unsigned short m_level = NOTSET;

    mutable std::mutex mtx;
};


class NullHandler: public Handler
{
public:
    HandlerPtr log( const wstring_type& str, const unsigned short level );
};


class StdOutHandler: public Handler
{
public:
    HandlerPtr log( const wstring_type& str, const unsigned short level );
};


class StdErrHandler: public Handler
{
public:
    HandlerPtr log( const wstring_type& str, const unsigned short level );
};


class FileHandler: public Handler
{
public:
    explicit FileHandler( const char* const filename );

    HandlerPtr log( const wstring_type& str, const unsigned short level );

private:
    std::mutex file_mtx;
};


} /* namespace pylogging */


#endif /* HANDLER_HPP_ */

