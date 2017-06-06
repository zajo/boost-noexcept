//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/result_traits_optional.hpp>
#include <boost/noexcept/throw_error_code.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;
using boost::noexcept_::config::optional;

struct error_domain { typedef int error_code_type; };

optional<int>
fail_with_error_code( int err ) noexcept
    {
    return throw_error_code<error_domain>(err);
    }
optional<int>
f1() noexcept
    {
    BOOST_TEST(!fail_with_error_code(42));
    return throw_();
    }
optional<int>
f2() noexcept
    {
    auto tr=try_(f1());
    BOOST_TEST(!tr);
    return throw_();
    }
int
main()
    {
    auto tr=try_(f2());
    BOOST_TEST(!tr);
    BOOST_TEST(*catch_error_code<error_domain>(tr)==42);
    return boost::report_errors();
    }
