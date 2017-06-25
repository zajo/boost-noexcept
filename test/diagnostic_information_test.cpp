//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

typedef boost::error_info<struct answer_,int> answer;

class
my_error:
    public std::exception
    {
    char const * what() const noexcept { return "my_error"; }
    public:
    my_error() noexcept { };
    };
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
        auto & err=*r.catch_<std::exception>();
        std::cout << boost::diagnostic_information(err) << '\n';
        }
    return boost::report_errors();
    }
