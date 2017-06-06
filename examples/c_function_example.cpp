//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept.hpp>
#include <boost/noexcept/throw_error_code.hpp>
#include <stdlib.h>
#include <iostream>

using namespace boost::noexcept_;
using boost::noexcept_::config::optional;

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

struct erratic_error { typedef int error_code_type; };

optional<float>
erratic_caller() noexcept
    {
    float answer;
    if( int err=erratic(&answer) )
        return throw_error_code<erratic_error>(err);
    else
        return answer;
    }

int
main()
    {
    for( int i=0; i!=10; ++i )
        if( auto tr=try_(erratic_caller()) )
            std::cout << "Answer: " << tr.value() << std::endl;
        else if( int const * err = catch_error_code<erratic_error>(tr) )
            std::cout << "FAILED! error=" << *err << std::endl;
    return 0;
    }
