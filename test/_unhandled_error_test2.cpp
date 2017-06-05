//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_try.hpp>
using namespace boost;

struct
error:
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
	(void) noexcept_try(fail1());
	return 42;
	}
int
main()
	{
	(void) fail2();
	return 0;
	}
