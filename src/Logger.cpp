/**
 * @file Logger.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include "Logger.hpp"
#include "Handler.hpp"

#include <boost/python/errors.hpp>

namespace boost
{

namespace python
{

const char* encoding = "utf-8";

#if PY_MAJOR_VERSION < 3

const object builtins = import( "__builtin__" );
const object unicode  = builtins.attr( "unicode" );

#endif

} /* namespace python */

} /* namespace boost */


namespace pylogging
{

/**
 *
 *
 */
void Logger::addHandler( const HandlerPtr& handler )
{
    if( ! handlers.insert( handler ).second )
    {
        PyErr_SetString( PyExc_ValueError, "handler already exists");

        boost::python::throw_error_already_set();
    }
}


/**
 *
 *
 */
void Logger::removeHandler( const HandlerPtr& handler )
{
    if( ! handlers.erase( handler ) )
    {
        PyErr_SetString( PyExc_ValueError, "handler does not exists");

        boost::python::throw_error_already_set();
    }
}


/**
 *
 *
 */
bool Logger::hasHandler( const HandlerPtr& handler ) const
{
    return handlers.count( handler );
}


/**
 *
 *
 */
void Logger::setLevel( const unsigned short level )
{
    m_level = level;
}


/**
 *
 *
 */
template<int LEVEL>
void Logger::logFormat( format& fmt )
{
    if( LEVEL >= m_level )
    {
        const string& str = fmt.str();
        const wstring wstr( str.begin(), str.end() ); // naive conversion

        for( const HandlerPtr& handler : handlers )
        {
            handler->log( wstr, LEVEL );
        }
    }
    else
    {
        fmt.clear();
    }
}


/**
 *
 *
 */
template<int LEVEL>
void Logger::logWFormat( wformat& fmt )
{
    if( LEVEL >= m_level )
    {
        const wstring& wstr = fmt.str();

        for( const HandlerPtr& handler : handlers )
        {
            handler->log( wstr, LEVEL );
        }
    }
    else
    {
        fmt.clear();
    }
}


/**
 *
 *
 */
template<int LEVEL>
void Logger::logObject( py::object& obj )
{
    if( LEVEL >= m_level )
    {
#if PY_MAJOR_VERSION >= 3
        const wstring wstr = py::extract<wstring>( py::str( obj ) );
#else
        const wstring wstr = py::extract<wstring>( py::unicode( obj ) );
#endif

        for( const HandlerPtr& handler : handlers )
        {
            handler->log( wstr, LEVEL );
        }
    }
}

template void Logger::logFormat<NOTSET>   (  format& fmt );
template void Logger::logFormat<DEBUG>    (  format& fmt );
template void Logger::logFormat<INFO>     (  format& fmt );
template void Logger::logFormat<WARNING>  (  format& fmt );
template void Logger::logFormat<ERROR>    (  format& fmt );
template void Logger::logFormat<CRITICAL> (  format& fmt );

template void Logger::logWFormat<NOTSET>  ( wformat& fmt );
template void Logger::logWFormat<DEBUG>   ( wformat& fmt );
template void Logger::logWFormat<INFO>    ( wformat& fmt );
template void Logger::logWFormat<WARNING> ( wformat& fmt );
template void Logger::logWFormat<ERROR>   ( wformat& fmt );
template void Logger::logWFormat<CRITICAL>( wformat& fmt );

template void Logger::logObject<NOTSET>   ( py::object& obj );
template void Logger::logObject<DEBUG>    ( py::object& obj );
template void Logger::logObject<INFO>     ( py::object& obj );
template void Logger::logObject<WARNING>  ( py::object& obj );
template void Logger::logObject<ERROR>    ( py::object& obj );
template void Logger::logObject<CRITICAL> ( py::object& obj );


} /* namespace pylogging */

