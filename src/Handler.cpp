/**
 * @file Handler.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include "Handler.hpp"

#include <iostream>


std::mutex stdout_mtx;
std::mutex stderr_mtx;


namespace pylogging
{


/**
 * @brief Destructor
 *
 */
Handler::~Handler()
{

}


/**
 *
 *
 */
void Handler::setLevel( const unsigned short level )
{
    const scoped_lock lock( mtx );

    m_level = level;
}


/**
 *
 *
 */
HandlerPtr NullHandler::log( const wstring_type& str, const unsigned short level )
{
    return shared_from_this();
}


/**
 *
 *
 */
HandlerPtr StdOutHandler::log( const wstring_type& str, const unsigned short level )
{
    const scoped_lock lock( mtx );

    if( level >= m_level )
    {
        const scoped_lock stream_lock( stdout_mtx );

        std::wcout << str << '\n';
    }

    return shared_from_this();
}


/**
 *
 *
 */
HandlerPtr StdErrHandler::log( const wstring_type& str, const unsigned short level )
{
    const scoped_lock lock( mtx );

    if( level >= m_level )
    {
        const scoped_lock stream_lock( stderr_mtx );

        std::wcerr << str << '\n';
    }

    return shared_from_this();
}


/**
 *
 *
 */
FileHandler::FileHandler( const char* const filename )
{

}


/**
 *
 *
 */
HandlerPtr FileHandler::log( const wstring_type& str, const unsigned short level )
{
    const scoped_lock lock( mtx );

    if( level >= m_level )
    {
        const scoped_lock file_lock( file_mtx );

        //std::wcout << str << '\n';
    }

    return shared_from_this();
}


/**
 *
 *
 */
bool operator<( const HandlerPtr& lhs, const HandlerPtr& rhs )
{
    return lhs.get() < rhs.get();
}


} /* namespace pylogging */


