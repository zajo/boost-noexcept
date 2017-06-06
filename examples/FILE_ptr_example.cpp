//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//This program demonstrates the use of noexcept_result_traits_ptr, which is based on the
//observation that functions returning pointers (always?) return 0 on error.

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
int
main()
	{
	if( auto tr=noexcept_try(open_file("file_name")) )
		{
		//Success! Get the FILE pointer:
		FILE * f=tr.value();
		//Use the file, then close it
		fclose(f);
		}
	else if( file_open_error * err=tr.noexcept_catch<file_open_error>() )
		{
		//The file failed to open! Handle error.
		}
	return 0;
	}
