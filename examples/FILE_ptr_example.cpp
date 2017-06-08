#include <boost/noexcept/result_traits_ptr.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <stdio.h>

using namespace boost::noexcept_;

struct file_open_error: std::exception { };

//Returns the FILE pointer on success or throw_s file_open_error.
FILE * open_file( char const * name ) {
	if( FILE * f=fopen(name,"rb") )
		return f;
	else
		return throw_(file_open_error());
}

int main() {
	if( auto tr=try_(open_file("file_name")) ) {
		//Success! Get the FILE pointer:
		FILE * f=tr.value();
		//Use the file, then close it
		fclose(f);
	} else if( file_open_error * err=tr.catch_<file_open_error>() ) {
		//The file failed to open! Handle error.
	}
	return 0;
}
