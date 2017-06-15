#include <boost/noexcept/error_ptr.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

struct my_error { };

int
succeed()
    {
    return 42;
    }
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
        {
        auto tr=try_(succeed());
        BOOST_TEST(tr);
        BOOST_TEST(!tr.make_error_ptr());
        }
        {
        error_ptr ep;
            {
            auto tr=try_(fail());
            ep=tr.make_error_ptr();
            BOOST_TEST(tr.catch_<my_error>()!=0);
            }
        BOOST_TEST(ep);
        refail(ep);
        BOOST_TEST(has_current_error());
        error_handler err;
        BOOST_TEST(err.catch_<my_error>()!=0);
        }
        {
        error_ptr ep;
            {
            auto tr=try_(fail());
            BOOST_TEST(tr.catch_<my_error>()!=0);
            ep=tr.make_error_ptr();
            }
        BOOST_TEST(ep);
        refail(ep);
        BOOST_TEST(has_current_error());
        error_handler err;
        BOOST_TEST(err.catch_<my_error>()!=0);
        }
    return boost::report_errors();
    }
