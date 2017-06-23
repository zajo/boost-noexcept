//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/result.hpp>

using namespace boost::noexcept_;

struct my_error { };

int
fail1() noexcept
    {
    return throw_(my_error());
    }
result<int>
get_result() noexcept
    {
    return make_result(fail1());
    }
void
buggy( result<int> && r ) noexcept
    {
    }
int
main()
    {
    (void) buggy(get_result());;
    return 0;
    }
