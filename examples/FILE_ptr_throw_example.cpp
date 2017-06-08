//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//This program demonstrates the use of result_traits_ptr (see FILE_ptr_example.cpp)
//in case when a caller wants to throw on failure.

#include <boost/noexcept/result_traits_ptr.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <stdio.h>

using namespace boost::noexcept_;

struct file_open_error: std::exception { };

//Return the FILE pointer on success or throw_s file_open_error.
FILE * open_file( char const * name ) noexcept {
    if( FILE * f=fopen(name,"rb") )
        return f;
    else
        return throw_(file_open_error());
}

FILE & open_file_throw_on_error( char const * name ) {
    return try_(open_file(name)).value();
}

int main() {
    try {
        FILE & f=open_file_throw_on_error("file_name");
        //Use the file, then close it
        fclose(&f);
    } catch( file_open_error & ) {
        //Handle error
    }
    return 0;
}
