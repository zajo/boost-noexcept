#include <boost/noexcept.hpp>
#include <boost/optional.hpp>
#include <stdlib.h>
#include <iostream>

using namespace boost::noexcept_;

//A C function which may fail, returning different error codes
extern "C" {
    #define ERRATIC_ERROR_FOO 1
    #define ERRATIC_ERROR_BAR 2

    int erratic( float * answer ) {  //<1>
        switch( rand() % 3 ) {
            default: *answer=42; return 0;
            case 1: return ERRATIC_ERROR_FOO;
            case 2: return ERRATIC_ERROR_BAR;
        }
    }
}

struct erratic_error { int error_code; };  //<2>

boost::optional<float> erratic_caller() noexcept {  //<3>
    float answer;
    if( int err=erratic(&answer) )
        return throw_(erratic_error{err});
    else
        return answer;
}

int main() {
    for( int i=0; i!=10; ++i )
        if( auto r=try_(erratic_caller()) )  //<4>
            std::cout << "Answer: " << r.get().value() << std::endl;
        else if( erratic_error const * err = r.catch_<erratic_error>() )  //<5>
            std::cout << "FAILED! error code=" << err->error_code << std::endl;
        else
            assert(0);
    return 0;
}
