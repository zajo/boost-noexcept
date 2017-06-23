#include <boost/noexcept.hpp>
#include <stdio.h>

using namespace boost::noexcept_;

struct file_open_error { };

//Returns the FILE pointer on success or throw_s file_open_error.
FILE * open_file( char const * name ) noexcept {
    if( FILE * f=fopen(name,"rb") )
        return f;
    else
        return throw_(file_open_error());  //<1>
}

int main() {
    if( auto tr=try_(open_file("file_name")) ) {  //<2>
        //Success! Get the FILE pointer:
        FILE * f=tr.get();
        //Use the file, then close it
        fclose(f);
    } else if( file_open_error * err=tr.catch_<file_open_error>() ) {  //<3>
        //The file failed to open! Handle error.
    }  //<4>
    return 0;
}
