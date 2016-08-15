/**
 * @file StreamHandler.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include "StreamHandler.hpp"


namespace pylogging
{

std::mutex cout_mtx;
std::mutex cerr_mtx;

/**
 *
 *
 */
template<class DERIVED>
StreamHandler<DERIVED>::StreamHandler( std::ostream& out, std::wostream& wout ):
      Handler()
    , m_out{ out }
    , m_wout{ wout }
{

}


/**
 *
 *
 */
template<class DERIVED>
HandlerPtr StreamHandler<DERIVED>::log( const string_type&  str, const unsigned short level )
{
    const std::unique_lock<decltype( mtx )>( mtx );

    if( level >= m_level )
    {
        m_out << str << '\n';
    }

    return shared_from_this();
}


/**
 *
 *
 */
template<class DERIVED>
HandlerPtr StreamHandler<DERIVED>::log( const wstring_type&  str, const unsigned short level )
{
    const std::unique_lock<decltype( mtx )>( mtx );

    if( level >= m_level )
    {
        m_wout << str << '\n';
    }

    return shared_from_this();
}



/**
 *
 *
 */
StdOutHandler::StdOutHandler(): StreamHandler( std::cout, std::wcout )
{

}


/**
 *
 *
 */
StdErrHandler::StdErrHandler(): StreamHandler( std::cerr, std::wcerr )
{

}


} /* namespace pylogging */


