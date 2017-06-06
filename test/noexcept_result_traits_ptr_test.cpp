//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_result_traits_ptr.hpp>
#include <boost/noexcept/noexcept_try.hpp>
#include <boost/noexcept/propagate.hpp>
#include <boost/core/lightweight_test.hpp>
#include <stdio.h>

using namespace boost;

struct file_open_error: std::exception { };

FILE *
open_file( char const * name )
	{
	if( FILE * f=fopen(name,"rb") )
		return f;
	else
		return propagate(file_open_error());
	}

int
main()
	{
	if( auto tr=noexcept_try(open_file("no_such_file")) )
		{
		//use file if opened, but it should fail
		BOOST_TEST(false);
		}
	else if( file_open_error * err=tr.noexcept_catch<file_open_error>() )
		{
		BOOST_TEST(err!=0);
		}
	return boost::report_errors();
	}
