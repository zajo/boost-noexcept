#include <boost/noexcept.hpp>
#include <fstream>
#include <string>
#include <iostream>

using namespace boost::noexcept_;

struct io_error { };
struct file_error: io_error { };
struct file_open_error: file_error { };
struct file_read_error: file_error { };

std::ifstream open_stream( char const * name ) noexcept {
    std::ifstream f(name);
    if( f.good() )
        return f;  //<1>
    else
        return throw_(file_open_error());  //<1>
}

std::string read_line( std::ifstream && f ) {
    BOOST_NOEXCEPT_CHECK
    assert(f.good());  //<2>
    std::string s;
    getline(f,s);
    if( f.good() )
        return s;  //<3>
    else
        return throw_(file_read_error());  //<3>
}

std::string read_string_from_file( char const * name ) {
    return read_line(open_stream(name));  //<4>
}

int main() {
    if( auto tr=try_(read_string_from_file("test.txt")) ) {
        //Success!
        std::cout << tr.get() << '\n';
        return 0;
    } else if( tr.catch_<file_open_error>() ) {  //<5>
        std::cerr << "Failed to open file!\n";
    } else if( tr.catch_<file_read_error>() ) {  //<5>
        std::cerr << "Failed to read file!\n";
    } /*else {  //<6>
        std::cerr <<
            "Unhandled error reached main!\n"
            "Diagnostic information below:\n" <<
            boost::diagnostic_information(*tr.catch_<>());
    }*/
    return 1;
}
