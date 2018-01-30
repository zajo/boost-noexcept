//Copyright (c) 2017-2018 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

struct my_error { };

int
main()
    {
    BOOST_TEST(!has_current_error());
    void * a=throw_(my_error());
    BOOST_TEST(!a);
    BOOST_TEST(has_current_error());
        {
        auto r=try_(std::move(a));
        BOOST_TEST(!has_current_error());
        }
    BOOST_TEST(has_current_error());
        {
        auto r=try_(std::move(a));
        BOOST_TEST(!has_current_error());
        BOOST_TEST(r.catch_<>()!=0);
        }
    BOOST_TEST(!has_current_error());
    return boost::report_errors();
    }
