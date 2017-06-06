//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_result_traits_optional.hpp>
#include <boost/noexcept/propagate_error_code.hpp>
#include <boost/noexcept/noexcept_try.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost;
using boost::noexcept_config::optional;

optional<int>
fail_with_error_code( int err ) noexcept
    {
    return propagate_error_code(err);
    }
optional<int>
f1() noexcept
    {
    BOOST_TEST(!fail_with_error_code(42));
    return propagate();
    }
optional<int>
f2() noexcept
    {
    auto tr=noexcept_try(f1());
    BOOST_TEST(!tr);
    return propagate();
    }
int
main()
    {
    auto tr=noexcept_try(f2());
    BOOST_TEST(!tr);
    BOOST_TEST(*tr.noexcept_catch_error_code<int>()==42);
    return boost::report_errors();
    }
