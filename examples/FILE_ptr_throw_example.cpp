//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//This program demonstrates the use of noexcept_result_traits_ptr (see FILE_ptr_example.cpp)
//in case when a caller wants to throw on failure.

#include <boost/noexcept/noexcept_result_traits_ptr.hpp>
#include <boost/noexcept/noexcept_try.hpp>
#include <boost/noexcept/propagate.hpp>
#include <stdio.h>

using namespace boost;

struct file_open_error: std::exception { };

//Return the FILE pointer on success or propagates file_open_error.
FILE *
open_file( char const * name )
	{
	if( FILE * f=fopen(name,"rb") )
		return f;
	else
		return propagate(file_open_error());
	}
FILE *
open_file_throw_on_error( char const * name )
	{
	return noexcept_try(open_file(name)).value();
	}
int
main()
	{
	try
		{
		FILE * f=open_file_throw_on_error("file_name");
		assert(f!=0); //Success, or we wouldn't be here!
		//Use the file, then close it
		fclose(f);
		}
	catch( file_open_error & )
		{
		//Handle error
		}
	return 0;
	}
