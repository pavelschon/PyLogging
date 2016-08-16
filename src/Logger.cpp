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
void Logger::log( wformat& fmt )
{
    const scoped_lock lock( mtx );

    if( LEVEL >= m_level )
    {
        const wstring_type& str = fmt.str();

        for( const HandlerPtr& handler : handlers )
        {
            handler->log( str, LEVEL );
        }
    }
    else
    {
        fmt.clear();
    }
}


template void Logger::log<NOTSET>  ( boost::wformat& fmt );
template void Logger::log<DEBUG>   ( boost::wformat& fmt );
template void Logger::log<INFO>    ( boost::wformat& fmt );
template void Logger::log<WARNING> ( boost::wformat& fmt );
template void Logger::log<ERROR>   ( boost::wformat& fmt );
template void Logger::log<CRITICAL>( boost::wformat& fmt );


} /* namespace pylogging */


