//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/traits/ptr.hpp>
#include <boost/noexcept/traits/boost/shared_ptr.hpp>
#include <boost/noexcept/traits/boost/unique_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/move/unique_ptr.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

struct obj { int answer; };

struct error { };

obj *
f1( bool succeed ) noexcept
    {
    static obj o={42};
    if( succeed )
        return &o;
    else
        return throw_(error());
    }
boost::shared_ptr<obj>
f2( bool succeed ) noexcept
    {
    if( succeed )
        return boost::shared_ptr<obj>(new obj{42});
    else
        return throw_(error());
    }
boost::movelib::unique_ptr<obj>
f3( bool succeed ) noexcept
    {
    if( succeed )
        return boost::movelib::unique_ptr<obj>(new obj{42});
    else
        return throw_(error());
    }
int
main()
    {
        {
        auto tr=try_(f1(true));
        BOOST_TEST(tr);
        BOOST_TEST(tr.result()->answer==42);
        }
        {
        auto tr=try_(f1(false));
        BOOST_TEST(!tr);
        BOOST_TEST(tr.catch_<error>()!=0);
        }
        {
        auto tr=try_(f2(true));
        BOOST_TEST(tr);
        BOOST_TEST(tr.result()->answer==42);
        }
        {
        auto tr=try_(f2(false));
        BOOST_TEST(!tr);
        BOOST_TEST(tr.catch_<error>()!=0);
        }
        {
        auto tr=try_(f3(true));
        BOOST_TEST(tr);
        BOOST_TEST(tr.result()->answer==42);
        }
        {
        auto tr=try_(f3(false));
        BOOST_TEST(!tr);
        BOOST_TEST(tr.catch_<error>()!=0);
        }
    return boost::report_errors();
    }
