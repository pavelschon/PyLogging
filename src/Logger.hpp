/**
 * @file Logger.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "PyLogging.hpp"


namespace pylogging
{

bool operator<( const HandlerPtr& lhs, const HandlerPtr& rhs );


class Logger: public boost::enable_shared_from_this<Logger>
{
public:
    LoggerPtr operator<<( const std::string& msg );

    void addHandler( const HandlerPtr& handler );
    void removeHandler( const HandlerPtr& handler );
    bool hasHandler( const HandlerPtr& handler ) const;

    void setLevel( const unsigned short level );

    template<class FORMAT, int LEVEL>
    void log( const FORMAT& fmt );

private:
    std::set<HandlerPtr> handlers;

    unsigned short m_level = NOTSET;
};


} /* namespace pylogging */


#endif /* LOGGER_HPP_ */

