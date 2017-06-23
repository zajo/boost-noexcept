//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/throw.hpp>
#include <boost/optional.hpp>

using namespace boost::noexcept_;

struct my_error { };

boost::optional<int>
fail() noexcept
    {
    return throw_(my_error());
    }
int
main()
    {
    (void) fail();
    return 0;
    }
