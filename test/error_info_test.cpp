#include <boost/noexcept.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

struct my_error: boost::exception { };
typedef boost::error_info<struct answer_,int> answer;

int
f1()
    {
    return throw_(my_error());
    }
int
f2()
    {
    if( auto tr=try_(f1()) )
        return tr.result();
    else
        {
        (*tr.catch_<boost::exception>()) << answer(42);
        return throw_();
        }
    }
int
main( int argc, char const * argv[ ] )
    {
    if( auto tr=try_(f2()) )
        BOOST_TEST(false);
    else
        {
        my_error & err=*tr.catch_<my_error>();
        BOOST_TEST(boost::get_error_info<answer>(err) && *boost::get_error_info<answer>(err)==42);
        }
    return boost::report_errors();
    }
