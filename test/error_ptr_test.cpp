#include <boost/noexcept/error_ptr.hpp>
#include <boost/noexcept/error_handler.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

struct my_error { };

int
fail()
    {
    return throw_(my_error());
    }
int
refail( error_ptr const & ep )
    {
    return throw_(ep);
    }
int
main( int argc, char const * argv[ ] )
    {
    BOOST_TEST(!has_current_error());
    BOOST_TEST(!make_error_ptr());
    fail();
    BOOST_TEST(has_current_error());
    error_ptr ep=make_error_ptr();
    BOOST_TEST(ep);
    BOOST_TEST(!has_current_error());
    refail(ep);
    BOOST_TEST(has_current_error());
    error_handler err;
    BOOST_TEST(err.catch_<my_error>()!=0);
    return boost::report_errors();
    }
