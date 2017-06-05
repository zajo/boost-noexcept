//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/fallible.hpp>
using namespace boost;

struct
error:
    std::exception
    {
    };
fallible<int>
fail()
    {
    return noexcept_propagate(error());
    }
int
main()
    {
    (void) fail();
    return 0;
    }
