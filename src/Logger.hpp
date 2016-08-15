/**
 * @file Logger.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "PyLogging.hpp"

#include <set>


namespace pylogging
{

bool operator<( const HandlerPtr& lhs, const HandlerPtr& rhs );


class Logger: public boost::noncopyable
{
public:
    void addHandler( const HandlerPtr& handler );
    void removeHandler( const HandlerPtr& handler );
    bool hasHandler( const HandlerPtr& handler ) const;

    void setLevel( const unsigned short level );

    template<class FORMAT, int LEVEL>
    void log( FORMAT& fmt );

private:
    std::set<HandlerPtr> handlers;

    unsigned short m_level = NOTSET;
};


} /* namespace pylogging */


#endif /* LOGGER_HPP_ */

