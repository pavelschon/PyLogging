/**
 * @file StreamHandler.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include "StreamHandler.hpp"

#include <iostream>
#include <mutex>


namespace pylogging
{

std::mutex stdout_mtx;
std::mutex stderr_mtx;


/**
 *
 *
 */
HandlerPtr StdOutHandler::log( const string_type& str, const unsigned short level )
{
    const scoped_lock lock( mtx );

    if( level >= m_level )
    {
        const scoped_lock stream_lock( stdout_mtx );

        std::cout << str << '\n';
    }

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
HandlerPtr StdErrHandler::log( const string_type& str, const unsigned short level )
{
    const scoped_lock lock( mtx );

    if( level >= m_level )
    {
        const scoped_lock stream_lock( stderr_mtx );

        std::cerr << str << '\n';
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


} /* namespace pylogging */


