#include <boost/noexcept.hpp>
#include <stdio.h>

using namespace boost::noexcept_;

struct file_open_error { };

//Return the FILE pointer on success or throw_s file_open_error.
FILE * open_file( char const * name ) noexcept {
    if( FILE * f=fopen(name,"rb") )
        return f;
    else
        return throw_(file_open_error());
}

FILE * open_file_throw_on_error( char const * name ) {
    return try_(open_file(name)).get();
}

int main() {
    try {
        FILE * f=open_file_throw_on_error("file_name");
        //Use the file, then close it
        fclose(f);
    } catch( file_open_error & ) {
        //Handle error
    }
    return 0;
}
