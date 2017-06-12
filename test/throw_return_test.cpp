//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

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
    BOOST_TEST(throw_return<bool>::value()==false);
    BOOST_TEST(throw_return<char>::value()==static_cast<char>(-1));
    BOOST_TEST(throw_return<signed char>::value()==static_cast<signed char>(-1));
    BOOST_TEST(throw_return<unsigned char>::value()==static_cast<unsigned char>(-1));
    BOOST_TEST(throw_return<wchar_t>::value()==static_cast<wchar_t>(-1));
    BOOST_TEST(throw_return<char16_t>::value()==static_cast<char16_t>(-1));
    BOOST_TEST(throw_return<char32_t>::value()==static_cast<char32_t>(-1));
    BOOST_TEST(throw_return<short>::value()==static_cast<short>(-1));
    BOOST_TEST(throw_return<unsigned short>::value()==static_cast<unsigned short>(-1));
    BOOST_TEST(throw_return<int>::value()==static_cast<int>(-1));
    BOOST_TEST(throw_return<unsigned int>::value()==static_cast<unsigned int>(-1));
    BOOST_TEST(throw_return<long>::value()==static_cast<long>(-1));
    BOOST_TEST(throw_return<unsigned long>::value()==static_cast<unsigned long>(-1));
    BOOST_TEST(throw_return<long long>::value()==static_cast<long long>(-1));
    BOOST_TEST(throw_return<unsigned long long>::value()==static_cast<unsigned long long>(-1));
    BOOST_TEST(throw_return<int *>::value()==0);
    BOOST_TEST(throw_return<boost::shared_ptr<int> >::value()==boost::shared_ptr<int>());    
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
