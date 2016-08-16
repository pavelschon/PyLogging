/**
 * @file Logger.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include "Logger.hpp"
#include "Handler.hpp"

#include <boost/python/errors.hpp>


namespace pylogging
{


/**
 *
 *
 */
void Logger::addHandler( const HandlerPtr& handler )
{
    const scoped_lock lock( mtx );

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
    const scoped_lock lock( mtx );

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
    const scoped_lock lock( mtx );

    return handlers.count( handler );
}


/**
 *
 *
 */
void Logger::setLevel( const unsigned short level )
{
    const scoped_lock lock( mtx );

    m_level = level;
}


/**
 *
 *
 */
template<int LEVEL>
void Logger::logFormat( wformat& fmt )
{
    const scoped_lock lock( mtx );

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


template<int LEVEL>
void Logger::logObject( object& obj )
{
    const scoped_lock lock( mtx );

    if( LEVEL >= m_level )
    {
        const wstring wstr = py::extract<wstring>( py::str( obj ) );

        for( const HandlerPtr& handler : handlers )
        {
            handler->log( wstr, LEVEL );
        }
    }
}


template void Logger::logFormat<NOTSET>  ( wformat& fmt );
template void Logger::logFormat<DEBUG>   ( wformat& fmt );
template void Logger::logFormat<INFO>    ( wformat& fmt );
template void Logger::logFormat<WARNING> ( wformat& fmt );
template void Logger::logFormat<ERROR>   ( wformat& fmt );
template void Logger::logFormat<CRITICAL>( wformat& fmt );

template void Logger::logObject<NOTSET>  ( object& obj );
template void Logger::logObject<DEBUG>   ( object& obj );
template void Logger::logObject<INFO>    ( object& obj );
template void Logger::logObject<WARNING> ( object& obj );
template void Logger::logObject<ERROR>   ( object& obj );
template void Logger::logObject<CRITICAL>( object& obj );


} /* namespace pylogging */


