//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

struct my_error { };
typedef boost::error_info<struct answer_,int> answer;

int
f1() noexcept
    {
    return THROW_(my_error());
    }
int
f2() noexcept
    {
    if( auto r=try_(f1()) )
        return r.get();
    else
        {
        (*r.catch_<boost::exception>()) << answer(42);
        return throw_();
        }
    }
int
main( int argc, char const * argv[ ] )
    {
    if( auto r=try_(f2()) )
        BOOST_TEST(false);
    else
        {
        auto & info=*r.catch_<boost::exception>();
        BOOST_TEST(boost::get_error_info<answer>(info) && *boost::get_error_info<answer>(info)==42);
        }
    return boost::report_errors();
    }
