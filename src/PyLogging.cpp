/**
 * @file PyLogging.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include "PyLogging.hpp"
#include "Logger.hpp"
#include "Handler.hpp"
#include "StreamHandler.hpp"

#include <boost/python.hpp>
#include <boost/make_shared.hpp>


/**
 *
 *
 */
template<typename T, typename... Params>
boost::shared_ptr<T> make_shared_( Params... parameters )
{
    return boost::make_shared<T>( parameters... );
}


/**
 *
 *
 */
BOOST_PYTHON_MODULE( pylogging )
{
    using namespace ::boost::python;
    using namespace ::pylogging;


    class_<Handler, boost::shared_ptr<Handler>, boost::noncopyable>( "Handler", no_init )
        // no __init__ here, the class is abstract!
        .def( "set_level", &Handler::setLevel )
        ;

    class_<NullHandler, boost::shared_ptr<NullHandler>, bases<Handler>, boost::noncopyable>( "NullHandler", no_init )
        .def( "__init__", make_constructor( &make_shared_<NullHandler> ) )
        ;

    class_<StreamHandler, boost::shared_ptr<StreamHandler>, bases<Handler>, boost::noncopyable>( "StreamHandler", no_init )
        // no __init__ here, the class is abstract!
        ;

    class_<StdOutHandler, boost::shared_ptr<StdOutHandler>, bases<StreamHandler>, boost::noncopyable>( "StdOutHandler", no_init )
        .def( "__init__", make_constructor( &make_shared_<StdOutHandler> ) )
        ;

    class_<StdErrHandler, boost::shared_ptr<StdErrHandler>, bases<StreamHandler>, boost::noncopyable>( "StdErrHandler", no_init )
       .def( "__init__", make_constructor( &make_shared_<StdErrHandler> ) )
       ;

    class_<Logger, boost::noncopyable>( "Logger", init<>() )
        .def( "__contains__",   &Logger::hasHandler )
        .def( "add_handler",    &Logger::addHandler )
        .def( "remove_handler", &Logger::removeHandler )
        .def( "set_level",      &Logger::setLevel )
        .def( "debug",          &Logger::log<boost::format,  DEBUG> )
        .def( "debug",          &Logger::log<boost::wformat, DEBUG> )
        .def( "info",           &Logger::log<boost::format,  INFO> )
        .def( "info",           &Logger::log<boost::wformat, INFO> )
        .def( "warning",        &Logger::log<boost::format,  WARNING> )
        .def( "warning",        &Logger::log<boost::wformat, WARNING> )
        .def( "error",          &Logger::log<boost::format,  ERROR> )
        .def( "error",          &Logger::log<boost::wformat, ERROR> )
        .def( "critical",       &Logger::log<boost::format,  CRITICAL> )
        .def( "critical",       &Logger::log<boost::wformat, CRITICAL> )
        ;

    enum_<LogLevel>( "LogLevel" )
        .value( "NOTSET",   NOTSET   )
        .value( "DEBUG",    DEBUG    )
        .value( "INFO",     INFO     )
        .value( "WARNING",  WARNING  )
        .value( "ERROR",    ERROR    )
        .value( "CRITICAL", CRITICAL )
        ;

    auto module = scope();

    module.attr( "__doc__"     ) = "PyLogging - fast python logging";
    module.attr( "__author__"  ) = "Pavel Schon <pavel@schon.cz>";
    module.attr( "__version__" ) = "0.1.0";

}



