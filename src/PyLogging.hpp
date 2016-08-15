/**
 * @file PyLogging.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef PYLOGGING_HPP_
#define PYLOGGING_HPP_

#include <boost/python.hpp>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <iostream>
#include <set>


namespace pylogging
{


class Logger;
class Handler;
class NullHandler;
class StreamHandler;
class StdOutHandler;
class StdErrHandler;


typedef boost::shared_ptr<Logger>             LoggerPtr;
typedef boost::shared_ptr<Handler>            HandlerPtr;
typedef boost::shared_ptr<NullHandler>        NullHandlerPtr;
typedef boost::shared_ptr<StreamHandler>      StreamHandlerPtr;
typedef boost::shared_ptr<StdOutHandler>      StdOutHandlerPtr;
typedef boost::shared_ptr<StdErrHandler>      StdErrHandlerPtr;

typedef boost::format::string_type  string_type;
typedef boost::wformat::string_type wstring_type;


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

