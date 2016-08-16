/**
 * @file Handler.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include "Handler.hpp"


namespace pylogging
{

std::mutex stdout_mtx;
std::mutex stderr_mtx;
std::mutex stdlog_mtx;


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
HandlerPtr NullHandler::log( const wstring& wstr, const unsigned short level )
{
    return shared_from_this();
}


/**
 *
 *
 */
HandlerPtr StdOutHandler::log( const wstring& wstr, const unsigned short level )
{
    const scoped_lock lock( mtx );

    if( level >= m_level )
    {
        const scoped_lock stream_lock( stdout_mtx );

        std::wcout << wstr << '\n';
    }

    return shared_from_this();
}


/**
 *
 *
 */
HandlerPtr StdErrHandler::log( const wstring& wstr, const unsigned short level )
{
    const scoped_lock lock( mtx );

    if( level >= m_level )
    {
        const scoped_lock stream_lock( stderr_mtx );

        std::wcerr << wstr << '\n';
    }

    return shared_from_this();
}


/**
 *
 *
 */
HandlerPtr StdLogHandler::log( const wstring& wstr, const unsigned short level )
{
    const scoped_lock lock( mtx );

    if( level >= m_level )
    {
        const scoped_lock stream_lock( stdlog_mtx );

        std::wclog << wstr << '\n';
    }

    return shared_from_this();
}


/**
 *
 *
 */
FileHandler::FileHandler()
{

}


/**
 *
 *
 */
FileHandler::FileHandler( const char* const filename ):
    wout{ std::make_unique<std::wofstream>( filename ) }
{

}


/**
 *
 *
 */
HandlerPtr FileHandler::log( const wstring& wstr, const unsigned short level )
{
    const scoped_lock lock( mtx );

    if( level >= m_level )
    {
        const scoped_lock file_lock( file_mtx );

        if( wout )
        {
            *wout << wstr << '\n';
        }
    }

    return shared_from_this();
}



/**
 *
 *
 */
void FileHandler::open( const char* const filename )
{
    const scoped_lock file_lock( file_mtx );

    wout = std::make_unique<std::wofstream>( filename );
}


/**
 *
 *
 */
void FileHandler::close()
{
    const scoped_lock file_lock( file_mtx );

    wout.reset(); // destructor automatically calls close()
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

