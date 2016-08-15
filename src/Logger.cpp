/**
 * @file Logger.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include "Logger.hpp"
#include "Handler.hpp"


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
template<class FORMAT, int LEVEL>
void Logger::log( const FORMAT& fmt )
{
    const typename FORMAT::string_type& str = fmt.str();

    if( LEVEL >= m_level )
    {
        for( const HandlerPtr& handler : handlers )
        {
            handler->log( str, LEVEL );
        }
    }
}


template void Logger::log<boost::format,  NOTSET>  ( const boost::format&  fmt );
template void Logger::log<boost::wformat, NOTSET>  ( const boost::wformat& fmt );

template void Logger::log<boost::format,  DEBUG>   ( const boost::format&  fmt );
template void Logger::log<boost::wformat, DEBUG>   ( const boost::wformat& fmt );

template void Logger::log<boost::format,  INFO>    ( const boost::format&  fmt );
template void Logger::log<boost::wformat, INFO>    ( const boost::wformat& fmt );

template void Logger::log<boost::format,  WARNING> ( const boost::format&  fmt );
template void Logger::log<boost::wformat, WARNING> ( const boost::wformat& fmt );

template void Logger::log<boost::format,  ERROR>   ( const boost::format&  fmt );
template void Logger::log<boost::wformat, ERROR>   ( const boost::wformat& fmt );

template void Logger::log<boost::format,  CRITICAL>( const boost::format&  fmt );
template void Logger::log<boost::wformat, CRITICAL>( const boost::wformat& fmt );


} /* namespace pylogging */


