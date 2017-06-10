//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

struct error { };
struct my_result_type { int answer; };

namespace
boost
    {
    namespace
    noexcept_
        {
        template <>
        struct
        result_traits<my_result_type>
            {
            typedef my_result_type result_type;
            typedef int value_type;
            static
            bool
            succeeded( result_type x ) noexcept
                {
                return x.answer!=-1;
                }
            static
            result_type
            error_result() noexcept
                {
                return my_result_type {-1};
                }
            static
            value_type const &
            success_value( result_type const & x ) noexcept
                {
                return x.answer;
                }
            static
            value_type &
            success_value( result_type & x ) noexcept
                {
                return x.answer;
                }
            };
        }
    }
my_result_type
f1( bool succeed ) noexcept
    {
    if( succeed )
        return my_result_type {42};
    else
        return throw_(error());
    }
my_result_type
f2( bool succeed ) noexcept
    {
    auto x=f1(succeed);
    if( succeeded_(x) )
        return x;
    else
        return throw_();
    }
void
test_success() noexcept
    {
    auto x = f2(true);
    if( succeeded_(x) )
        BOOST_TEST(x.answer==42);
    else
        BOOST_TEST(false);
    }
void
test_failure() noexcept
    {
    if( auto x=try_(f2(false)) )
        BOOST_TEST(false);
    else
        BOOST_TEST(x.catch_<error>()!=0);
    }
int
main()
    {
    test_success();
    test_failure();
    return boost::report_errors();
    }
