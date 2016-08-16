/**
 * @file PyLogging.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include "PyLogging.hpp"
#include "Logger.hpp"
#include "Handler.hpp"


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

    std::locale::global(std::locale(""));


    class_<Handler, boost::shared_ptr<Handler>, boost::noncopyable>( "Handler", no_init )
        .def( "set_level", &Handler::setLevel )
        ;

    class_<NullHandler, boost::shared_ptr<NullHandler>, bases<Handler>, boost::noncopyable>( "NullHandler", no_init )
        .def( "__init__", make_constructor( &make_shared_<NullHandler> ) )
        ;

    class_<StdOutHandler, boost::shared_ptr<StdOutHandler>, bases<Handler>, boost::noncopyable>( "StdOutHandler", no_init )
        .def( "__init__", make_constructor( &make_shared_<StdOutHandler> ) )
        ;

    class_<StdErrHandler, boost::shared_ptr<StdErrHandler>, bases<Handler>, boost::noncopyable>( "StdErrHandler", no_init )
       .def( "__init__", make_constructor( &make_shared_<StdErrHandler> ) )
       ;

    class_<StdLogHandler, boost::shared_ptr<StdLogHandler>, bases<Handler>, boost::noncopyable>( "StdLogHandler", no_init )
        .def( "__init__", make_constructor( &make_shared_<StdLogHandler> ) )
       ;

    class_<FileHandler, boost::shared_ptr<FileHandler>, bases<Handler>, boost::noncopyable>( "FileHandler", no_init )
       .def( "__init__", make_constructor( &make_shared_<FileHandler, const char*> ) )
       .def( "open",  &FileHandler::open )
       .def( "close", &FileHandler::close )
       ;

    class_<Logger, boost::noncopyable>( "Logger", init<>()   )
        .def( "__contains__",   &Logger::hasHandler          )
        .def( "add_handler",    &Logger::addHandler          )
        .def( "remove_handler", &Logger::removeHandler       )
        .def( "set_level",      &Logger::setLevel            )
        .def( "debug",          &Logger::logObject<DEBUG>    )
        .def( "debug",          &Logger::logFormat<DEBUG>    )
        .def( "info",           &Logger::logObject<INFO>     )
        .def( "info",           &Logger::logFormat<INFO>     )
        .def( "warning",        &Logger::logObject<WARNING>  )
        .def( "warning",        &Logger::logFormat<WARNING>  )
        .def( "error",          &Logger::logObject<ERROR>    )
        .def( "error",          &Logger::logFormat<ERROR>    )
        .def( "critical",       &Logger::logObject<CRITICAL> )
        .def( "critical",       &Logger::logFormat<CRITICAL> )
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



