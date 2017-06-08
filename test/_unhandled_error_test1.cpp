//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/result_traits_optional.hpp>
#include <boost/noexcept/throw.hpp>

using namespace boost::noexcept_;
using boost::noexcept_::config::optional;

struct
error:
    std::exception
    {
    };
optional<int>
fail()
    {
    return throw_(error());
    }
int
main()
    {
    (void) fail();
    return 0;
    }
