//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/optional.hpp>
#include <boost/core/lightweight_test.hpp>
#include <iostream>

using namespace boost::noexcept_;

struct tag1;
struct tag2;
struct tag3;
template <class> struct compute_int_failed { };

template <class Tag>
boost::optional<int>
compute_int( bool should_succeed ) noexcept
    {
    if( should_succeed )
        return 42;
    else
        return throw_(compute_int_failed<Tag>());
    }
void
test1() noexcept
    {
    if( auto err1=try_(compute_int<tag1>(false)) )
        BOOST_TEST(false);
    else
        {
        BOOST_TEST(!err1);
        BOOST_TEST(!err1.has_internal_error_());
        if( auto err2=try_(compute_int<tag2>(false)) )
            BOOST_TEST(false);
        else
            {
            BOOST_TEST(!err1);
            BOOST_TEST(err1.has_internal_error_());
            BOOST_TEST(!err2);
            BOOST_TEST(!err2.has_internal_error_());
            if( auto err3=try_(compute_int<tag3>(false)) )
                BOOST_TEST(false);
            else
                {
                BOOST_TEST(!err1);
                BOOST_TEST(err1.has_internal_error_());
                BOOST_TEST(!err2);
                BOOST_TEST(err2.has_internal_error_());
                BOOST_TEST(!err3);
                BOOST_TEST(!err3.has_internal_error_());
                BOOST_TEST(err3.catch_<compute_int_failed<tag3> >()!=0);
                BOOST_TEST(!err3);
                }
            BOOST_TEST(err2.catch_<compute_int_failed<tag2> >()!=0);
            BOOST_TEST(!err2);
            }
        BOOST_TEST(err1.catch_<compute_int_failed<tag1> >()!=0);
        BOOST_TEST(!err1);
        }
    }
void
test2() noexcept
    {
    auto err1=try_(compute_int<tag1>(false));
    auto err2=try_(compute_int<tag2>(false));
    auto err3=try_(compute_int<tag3>(false));
    BOOST_TEST(!err1);
    BOOST_TEST(!err2);
    BOOST_TEST(!err3);
    BOOST_TEST(err1.catch_<compute_int_failed<tag1> >()!=0);
    BOOST_TEST(err2.catch_<compute_int_failed<tag2> >()!=0);
    BOOST_TEST(err3.catch_<compute_int_failed<tag3> >()!=0);
    }
int
main()
    {
    test1();
    test2();
    return boost::report_errors();
    }
