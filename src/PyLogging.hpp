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
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/python.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <locale>
#include <mutex>
#include <set>


namespace pylogging
{

namespace py       = boost::python;

using wformat      = boost::wformat;
using wstring      = boost::wformat::string_type;
using wstring_type = boost::wformat::string_type;
using object       = boost::python::object;

using HandlerPtr   = boost::shared_ptr<class Handler>;
using scoped_lock  = std::unique_lock<std::mutex>;

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

