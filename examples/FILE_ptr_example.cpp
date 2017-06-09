#include <boost/noexcept.hpp>
#include <boost/noexcept/result_traits_ptr.hpp>  //<1>
#include <stdio.h>

using namespace boost::noexcept_;

struct file_open_error { };

//Returns the FILE pointer on success or throw_s file_open_error.
FILE * open_file( char const * name ) noexcept {
    if( FILE * f=fopen(name,"rb") )
        return f;
    else
        return throw_(file_open_error());  //<2>
}

int main() {
    if( auto tr=try_(open_file("file_name")) ) {  //<3>
        //Success! Get the FILE by reference.:
        FILE & f=tr.value();
        //Use the file, then close it
        fclose(&f);
    } else if( file_open_error * err=tr.catch_<file_open_error>() ) {  //<4>
        //The file failed to open! Handle error.
    }  //<5>
    return 0;
}
