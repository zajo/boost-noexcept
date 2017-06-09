//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/noexcept/traits/boost/optional.hpp>
#include <boost/optional.hpp>

using namespace boost::noexcept_;

struct error { };

boost::optional<int>
fail1() noexcept
    {
    return throw_(error());
    }
boost::optional<int>
buggy() noexcept
    {
    auto r1=try_(fail1());
    //(void) r1.catch_<>(); //<--use this to ignore the error in r1
    return fail1();
    }
int
main()
    {
    (void) buggy();
    return 0;
    }
