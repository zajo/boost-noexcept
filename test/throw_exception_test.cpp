//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_result_traits_optional.hpp>
#include <boost/noexcept/noexcept_try.hpp>
#include <boost/noexcept/propagate.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost;
using boost::noexcept_config::optional;

struct failure: std::exception { };

optional<int>
succeeds()
    {
    return 42;
    }
optional<int>
fails()
    {
    return propagate(failure());
    }
int
main()
    {
    BOOST_TEST(succeeds().value()==42);
    BOOST_TEST(noexcept_try(succeeds()).value()==42);
    try
        {
        (void) noexcept_try(fails()).value();
        BOOST_TEST(false);
        }
    catch( failure & )
        {
        }
    return boost::report_errors();
    }
