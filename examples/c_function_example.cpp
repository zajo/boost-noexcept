//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept.hpp>
#include <boost/noexcept/result_traits_optional.hpp>
#include <boost/optional.hpp>
#include <stdlib.h>
#include <iostream>

using namespace boost::noexcept_;

//A C function which may fail, returning different error codes
extern "C" {
    #define ERRATIC_ERROR_FOO 1
    #define ERRATIC_ERROR_BAR 2

    int
    erratic( float * answer ) {
        switch( rand() % 3 ) {
            default: *answer=42; return 0;
            case 1: return ERRATIC_ERROR_FOO;
            case 2: return ERRATIC_ERROR_BAR;
        }
    }
}

struct erratic_error { int error_code; };

boost::optional<float> erratic_caller() noexcept {
    float answer;
    if( int err=erratic(&answer) )
        return throw_(erratic_error{err});
    else
        return answer;
}

int main() {
    for( int i=0; i!=10; ++i )
        if( auto tr=try_(erratic_caller()) )
            std::cout << "Answer: " << tr.value() << std::endl;
        else if( erratic_error const * err = tr.catch_<erratic_error>() )
            std::cout << "FAILED! error code=" << err->error_code << std::endl;
        else
            assert(0);
    return 0;
}
