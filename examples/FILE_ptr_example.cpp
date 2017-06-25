#include <boost/noexcept.hpp>
#include <system_error>
#include <stdio.h>

using namespace boost::noexcept_;

FILE * open_file( char const * name ) noexcept {
    if( FILE * f=fopen(name,"rb") )
        return f;
    else
        return throw_( std::error_code { errno, std::generic_category() } );  //<1>
}

int main() {
    if( auto r=try_(open_file("file_name")) ) {  //<2>
        //Success! Get the FILE pointer:
        FILE * f=r.get();
        //Use the file, then close it
        fclose(f);
    } else if( std::error_code * err=r.catch_<std::error_code>() ) {  //<3>
        //The file failed to open! Handle error.
    }  //<4>
    return 0;
}
