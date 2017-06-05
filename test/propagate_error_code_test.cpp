//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_error_code.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost;

fallible<int>
fail_with_error_code( int err ) noexcept
	{
	return propagate_error_code(err);
	}
fallible<int>
f1() noexcept
	{
	BOOST_TEST(!fail_with_error_code(42));
	return noexcept_propagate();
	}
fallible<int>
f2() noexcept
	{
	auto tr=noexcept_try(f1());
	BOOST_TEST(!tr);
	return noexcept_propagate();
	}
int
main()
	{
	auto tr=noexcept_try(f2());
	BOOST_TEST(!tr);
	BOOST_TEST(*tr.noexcept_catch_error_code<int>()==42);
	return boost::report_errors();
	}
