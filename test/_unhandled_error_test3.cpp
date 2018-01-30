//Copyright (c) 2017-2018 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/optional.hpp>

using namespace boost::noexcept_;

struct my_error { };
struct wrong_error { };

boost::optional<int>
fail1() noexcept
    {
    return throw_(my_error());
    }
int
fail2() noexcept
    {
    auto r=try_(fail1());
    (void) r.catch_<wrong_error>();
    return 42;
    }
int
main()
    {
    (void) fail2();
    return 0;
    }
