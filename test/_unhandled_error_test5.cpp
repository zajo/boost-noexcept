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
optional<int>
fail1()
    {
    return throw_(error());
    }
optional<int>
buggy()
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
