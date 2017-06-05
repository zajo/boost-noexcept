//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_try.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost;

struct
f1_failed:
	std::exception
	{
	int const val;
	explicit
	f1_failed( int val ):
		val(val)
		{
		}
	};
struct
f4_failed:
	f1_failed
	{
	explicit
	f4_failed( int val ):
		f1_failed(val)
		{
		}
	};
fallible<int>
f1()
	{
	return noexcept_propagate(f1_failed(1));
	}
fallible<int>
f2()
	{
	BOOST_TEST(!f1());
	return noexcept_propagate();
	}
fallible<int>
f3()
	{
	auto tr=noexcept_try(f1());
	BOOST_TEST(!tr);
	return noexcept_propagate();
	}
fallible<int>
f4()
	{
	auto tr=noexcept_try(f3());
	BOOST_TEST(!tr);
	BOOST_TEST(tr.noexcept_catch<f1_failed>()->val==1);
	return noexcept_propagate(f4_failed(2));
	}
fallible<int>
f5()
	{
	BOOST_TEST(!f4());
	return noexcept_propagate();
	}
int
f6_a()
	{
	auto tr=noexcept_try(f5());
	BOOST_TEST(!tr);
	BOOST_TEST(tr.noexcept_catch<f4_failed>()->val==2);
	return 42;
	}
int
f6_b()
	{
	auto tr=noexcept_try(f5());
	BOOST_TEST(!tr);
	BOOST_TEST(tr.noexcept_catch<f1_failed>()->val==2);
	return 42;
	}
int
main()
	{
	BOOST_TEST(f6_a()==42);
	BOOST_TEST(f6_b()==42);
	return boost::report_errors();
	}
