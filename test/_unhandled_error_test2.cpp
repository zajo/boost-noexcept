//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_result_traits_optional.hpp>
#include <boost/noexcept/propagate.hpp>
#include <boost/noexcept/noexcept_try.hpp>

using namespace boost;
using boost::noexcept_config::optional;

struct
error:
    std::exception
    {
    };
optional<int>
fail1()
    {
    return propagate(error());
    }
int
fail2()
    {
    (void) noexcept_try(fail1());
    return 42;
    }
int
main()
    {
    (void) fail2();
    return 0;
    }
