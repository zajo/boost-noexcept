#include <boost/noexcept/error_handler.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

template <int> struct my_error { };

int
main( int argc, char const * argv[ ] )
    {
        {
        error_handler   h;
        BOOST_TEST(!h.has_error());
        BOOST_TEST(!h.has_unhandled_error());
        BOOST_TEST(!h.catch_<my_error<1> >());
        h.throw_exception();
        }
    BOOST_TEST(!has_current_error());
    throw_(my_error<1>());
    BOOST_TEST(has_current_error());
        {
        error_handler   h;
        BOOST_TEST(!has_current_error());
        BOOST_TEST(h.has_error());
        BOOST_TEST(h.has_unhandled_error());
        }
    BOOST_TEST(has_current_error());
        {
        error_handler   h;
        BOOST_TEST(!has_current_error());
        BOOST_TEST(h.has_error());
        BOOST_TEST(h.has_unhandled_error());
        BOOST_TEST(h.catch_<my_error<1> >()!=0);
        BOOST_TEST(h.has_error());
        BOOST_TEST(!h.has_unhandled_error());
        }
    BOOST_TEST(!has_current_error());
    throw_(my_error<1>());
    BOOST_TEST(has_current_error());
        {
        error_handler   h1;
        BOOST_TEST(h1.has_error());
        BOOST_TEST(h1.has_unhandled_error());
        throw_(my_error<2>());
        BOOST_TEST(has_current_error());
            {
            error_handler h2;
            BOOST_TEST(!has_current_error());
            BOOST_TEST(h2.has_error());
           BOOST_TEST(h2.has_unhandled_error());
            BOOST_TEST(!h2.catch_<my_error<1> >());
            BOOST_TEST(h2.has_error());
            BOOST_TEST(h2.has_unhandled_error());
            BOOST_TEST(h2.catch_<my_error<2>    >()!=0);
            BOOST_TEST(h2.has_error());
            BOOST_TEST(!h2.has_unhandled_error());
            }
        BOOST_TEST(!has_current_error());
        BOOST_TEST(!h1.catch_<my_error<2> >());
        BOOST_TEST(h1.has_error());
        BOOST_TEST(h1.has_unhandled_error());
        BOOST_TEST(h1.catch_<my_error<1> >()!=0);
        BOOST_TEST(h1.has_error());
        BOOST_TEST(!h1.has_unhandled_error());
        }
    BOOST_TEST(!has_current_error());
    return boost::report_errors();
    }
