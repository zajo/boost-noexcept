//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_try.hpp>
#include <boost/core/lightweight_test.hpp>
using namespace boost;

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
fallible<int>
fail1()
    {
    return noexcept_propagate(error());
    }
int
fail2()
    {
    auto tr=noexcept_try(fail1());
    BOOST_TEST(tr.noexcept_catch<wrong_error>()==0);
    return 42;
    }
int
main()
    {
    (void) fail2();
    return 0;
    }
