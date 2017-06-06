//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/result_traits_ptr.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/core/lightweight_test.hpp>
#include <stdio.h>

using namespace boost::noexcept_;

struct file_open_error: std::exception { };

FILE *
open_file( char const * name )
	{
	if( FILE * f=fopen(name,"rb") )
		return f;
	else
		return throw_(file_open_error());
	}

int
main()
	{
	if( auto tr=try_(open_file("no_such_file")) )
		{
		//use file if opened, but it should fail
		BOOST_TEST(false);
		}
	else if( file_open_error * err=tr.catch_<file_open_error>() )
		{
		BOOST_TEST(err!=0);
		}
	return boost::report_errors();
	}
