/**
 * @file Handler.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include "Handler.hpp"


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
    m_level = level;
}


/**
 *
 *
 */
HandlerPtr NullHandler::log( const string_type& str, const unsigned short level )
{
    return shared_from_this();
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
bool operator<( const HandlerPtr& lhs, const HandlerPtr& rhs )
{
    return lhs.get() < rhs.get();
}


} /* namespace pylogging */

