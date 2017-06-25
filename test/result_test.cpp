//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

template <int> struct my_error { };

int
main( int argc, char const * argv[ ] )
    {
        {
        result<int> h=try_(42);
        BOOST_TEST(!h.has_error());
        BOOST_TEST(!h.has_unhandled_error());
        BOOST_TEST(!h.catch_<my_error<1> >());
        BOOST_TEST(h.get()==42);
        }
    BOOST_TEST(!has_current_error());
    (void) throw_(my_error<1>());
    BOOST_TEST(has_current_error());
        {
        auto h=current_error();
        BOOST_TEST(!has_current_error());
        BOOST_TEST(h.has_error());
        BOOST_TEST(h.has_unhandled_error());
        }
    BOOST_TEST(has_current_error());
        {
        auto h=current_error();
        BOOST_TEST(!has_current_error());
        BOOST_TEST(h.has_error());
        BOOST_TEST(h.has_unhandled_error());
        BOOST_TEST(h.catch_<my_error<1> >()!=0);
        BOOST_TEST(h.has_error());
        BOOST_TEST(!h.has_unhandled_error());
        }
    BOOST_TEST(!has_current_error());
    (void) throw_(my_error<1>());
    BOOST_TEST(has_current_error());
        {
        auto h1=current_error();
        BOOST_TEST(h1.has_error());
        BOOST_TEST(h1.has_unhandled_error());
        (void) throw_(my_error<2>());
        BOOST_TEST(has_current_error());
            {
            auto h2=current_error();
            BOOST_TEST(!has_current_error());
            BOOST_TEST(h2.has_error());
           BOOST_TEST(h2.has_unhandled_error());
            BOOST_TEST(!h2.catch_<my_error<1> >());
            BOOST_TEST(h2.has_error());
            BOOST_TEST(h2.has_unhandled_error());
            BOOST_TEST(h2.catch_<my_error<2> >()!=0);
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
