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
template<class FORMAT, int LEVEL>
void Logger::log( FORMAT& fmt )
{
    const scoped_lock lock( mtx );

    if( LEVEL >= m_level )
    {
        const typename FORMAT::string_type& str = fmt.str();

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


template void Logger::log<boost::format,  NOTSET>  ( boost::format&  fmt );
template void Logger::log<boost::wformat, NOTSET>  ( boost::wformat& fmt );

template void Logger::log<boost::format,  DEBUG>   ( boost::format&  fmt );
template void Logger::log<boost::wformat, DEBUG>   ( boost::wformat& fmt );

template void Logger::log<boost::format,  INFO>    ( boost::format&  fmt );
template void Logger::log<boost::wformat, INFO>    ( boost::wformat& fmt );

template void Logger::log<boost::format,  WARNING> ( boost::format&  fmt );
template void Logger::log<boost::wformat, WARNING> ( boost::wformat& fmt );

template void Logger::log<boost::format,  ERROR>   ( boost::format&  fmt );
template void Logger::log<boost::wformat, ERROR>   ( boost::wformat& fmt );

template void Logger::log<boost::format,  CRITICAL>( boost::format&  fmt );
template void Logger::log<boost::wformat, CRITICAL>( boost::wformat& fmt );


} /* namespace pylogging */


