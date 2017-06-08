//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/result_traits_optional.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/try.hpp>

using namespace boost::noexcept_;
using boost::noexcept_::config::optional;

struct
error:
    std::exception
    {
    };
struct
wrong_error:
    std::exception
    {
    };
optional<int>
fail1()
    {
    return throw_(error());
    }
int
fail2()
    {
    auto tr=try_(fail1());
    (void) tr.catch_<wrong_error>();
    return 42;
    }
int
main()
    {
    (void) fail2();
    return 0;
    }
