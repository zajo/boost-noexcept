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
optional<int>
buggy()
    {
	auto r1=noexcept_try(fail1());
	//(void) r1.noexcept_catch_all(); //<--use this to ignore the error in r1
	return fail1();
    }
int
main()
    {
    (void) buggy();
    return 0;
    }
