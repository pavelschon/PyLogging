/**
 * @file PyLogging.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef PYLOGGING_HPP_
#define PYLOGGING_HPP_

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <mutex>


namespace pylogging
{

typedef boost::shared_ptr<class Handler> HandlerPtr;

typedef boost::format::string_type  string_type;
typedef boost::wformat::string_type wstring_type;

typedef std::unique_lock<std::mutex> scoped_lock;


enum LogLevel
{
    NOTSET      = 0,
    DEBUG       = 10,
    INFO        = 20,
    WARNING     = 30,
    ERROR       = 40,
    CRITICAL    = 50
};


} /* namespace pylogging */


#endif /* PYLOGGING_HPP_ */

