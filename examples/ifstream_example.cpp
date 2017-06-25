#include <boost/noexcept.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <system_error>

using namespace boost::noexcept_;

std::ifstream open_stream( char const * name ) noexcept {
    std::ifstream f(name);
    if( f.good() )
        return f;  //<1>
    else
        return throw_( std::error_code{ errno, std::generic_category() } );  //<1>
}

std::string read_line( std::ifstream && f ) noexcept {
    BOOST_NOEXCEPT_CHECK
    assert(f.good());  //<2>
    std::string s;
    getline(f,s);
    if( f.good() )
        return s;  //<3>
    else
        return throw_( std::error_code{ errno, std::generic_category() } );  //<3>
}

std::string read_string_from_file( char const * name ) noexcept {
    return read_line(open_stream(name));  //<4>
}

int main() {
    if( auto r=try_(read_string_from_file("test.txt")) ) {
        //Success!
        std::cout << r.get() << '\n';
        return 0;
    } else if( auto err=r.catch_<std::error_code>() ) {  //<5>
        std::cerr << err->message();
    } /*else {  //<6>
        std::cerr <<
            "Unhandled error reached main!\n"
            "Diagnostic information below:\n" <<
            boost::diagnostic_information(*r.catch_<>());
    }*/
    return 1;
}
