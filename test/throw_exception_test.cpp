//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/traits/boost/optional.hpp>
#include <boost/optional.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

struct failure { };

boost::optional<int>
succeeds() noexcept
    {
    return 42;
    }
boost::optional<int>
fails() noexcept
    {
    return throw_(failure());
    }
int
main()
    {
    BOOST_TEST(succeeds().value()==42);
    BOOST_TEST(try_(succeeds()).value()==42);
    try
        {
        (void) try_(fails()).value();
        BOOST_TEST(false);
        }
    catch( failure & )
        {
        }
    return boost::report_errors();
    }
