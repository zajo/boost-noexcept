//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_try.hpp>
#include <boost/core/lightweight_test.hpp>
#include <iostream>

using namespace boost;

struct tag1;
struct tag2;
struct tag3;
template <class>
struct
compute_int_failed:
	std::exception
	{
	};
template <class Tag>
fallible<int>
compute_int( bool should_succeed )
	{
	if( should_succeed )
		return 42;
	else
		return noexcept_propagate(compute_int_failed<Tag>());
	}
int
main()
	{
	if( auto err1=noexcept_try(compute_int<tag1>(false)) )
		BOOST_TEST(false);
	else
		{
		BOOST_TEST(!err1.succeeded());
		BOOST_TEST(!err1.has_internal_error_());
		if( auto err2=noexcept_try(compute_int<tag2>(false)) )
			BOOST_TEST(false);
		else
			{
			BOOST_TEST(!err1.succeeded());
			BOOST_TEST(err1.has_internal_error_());
			BOOST_TEST(!err2.succeeded());
			BOOST_TEST(!err2.has_internal_error_());
			if( auto err3=noexcept_try(compute_int<tag3>(false)) )
				BOOST_TEST(false);
			else
				{
				BOOST_TEST(!err1.succeeded());
				BOOST_TEST(err1.has_internal_error_());
				BOOST_TEST(!err2.succeeded());
				BOOST_TEST(err2.has_internal_error_());
				BOOST_TEST(!err3.succeeded());
				BOOST_TEST(!err3.has_internal_error_());
				BOOST_TEST(err3.noexcept_catch<compute_int_failed<tag3> >()!=0);
				BOOST_TEST(!err3.succeeded());
				}
			BOOST_TEST(err2.noexcept_catch<compute_int_failed<tag2> >()!=0);
			BOOST_TEST(!err2.succeeded());
			}
		BOOST_TEST(err1.noexcept_catch<compute_int_failed<tag1> >()!=0);
		BOOST_TEST(!err1.succeeded());
		}		
	return boost::report_errors();
	}
