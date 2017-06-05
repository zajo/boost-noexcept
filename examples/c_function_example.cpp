//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept.hpp>
#include <stdlib.h>
#include <iostream>

using namespace boost;

#define ERROR_FOO 1
#define ERROR_BAR 2

int
erratic( float * answer ) noexcept
	{
	switch( rand() % 3 )
		{
		case 0: return ERROR_FOO;
		case 1: return ERROR_BAR;
		default: *answer=42; return 0;
		}
	}

fallible<float>
erratic_caller() noexcept
	{
	float answer;
	if( int err=erratic(&answer) )
		return propagate_error_code(err);
	else
		return answer;
	}

int
main()
	{
	for( int i=0; i!=10; ++i )
		if( auto tr=noexcept_try(erratic_caller()) )
			std::cout << "Answer: " << tr.value() << std::endl;
		else if( int const * err = tr.noexcept_catch_error_code<int>() )
			std::cout << "FAILED! error=" << *err << std::endl;
	return 0;
	}
