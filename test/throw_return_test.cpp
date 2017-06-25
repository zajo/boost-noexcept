//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/shared_ptr.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

template <class T> T test_throw_return();
template <> bool test_throw_return<bool>() { return throw_(); }
template <> char test_throw_return<char>() { return throw_(); }
template <> signed char test_throw_return<signed char>() { return throw_(); }
template <> unsigned char test_throw_return<unsigned char>() { return throw_(); }
template <> wchar_t test_throw_return<wchar_t>() { return throw_(); }
template <> char16_t test_throw_return<char16_t>() { return throw_(); }
template <> char32_t test_throw_return<char32_t>() { return throw_(); }
template <> short test_throw_return<short>() { return throw_(); }
template <> unsigned short test_throw_return<unsigned short>() { return throw_(); }
template <> int test_throw_return<int>() { return throw_(); }
template <> unsigned int test_throw_return<unsigned int>() { return throw_(); }
template <> long test_throw_return<long>() { return throw_(); }
template <> unsigned long test_throw_return<unsigned long>() { return throw_(); }
template <> long long test_throw_return<long long>() { return throw_(); }
template <> unsigned long long test_throw_return<unsigned long long>() { return throw_(); }
template <> int * test_throw_return<int *>() { return throw_(); }
template <> boost::shared_ptr<int> test_throw_return<boost::shared_ptr<int> >() { return throw_(); }

struct my_error { };
int
throw_error() noexcept
    {
    return throw_(my_error());
    }

int
main()
    {
    throw_error();
    BOOST_TEST((test_throw_return<bool>()==false));
    BOOST_TEST((test_throw_return<char>()==static_cast<char>(-1)));
    BOOST_TEST((test_throw_return<signed char>()==static_cast<signed char>(-1)));
    BOOST_TEST((test_throw_return<unsigned char>()==static_cast<unsigned char>(-1)));
    BOOST_TEST((test_throw_return<wchar_t>()==static_cast<wchar_t>(-1)));
    BOOST_TEST((test_throw_return<char16_t>()==static_cast<char16_t>(-1)));
    BOOST_TEST((test_throw_return<char32_t>()==static_cast<char32_t>(-1)));
    BOOST_TEST((test_throw_return<short>()==static_cast<short>(-1)));
    BOOST_TEST((test_throw_return<unsigned short>()==static_cast<unsigned short>(-1)));
    BOOST_TEST((test_throw_return<int>()==static_cast<int>(-1)));
    BOOST_TEST((test_throw_return<unsigned int>()==static_cast<unsigned int>(-1)));
    BOOST_TEST((test_throw_return<long>()==static_cast<long>(-1)));
    BOOST_TEST((test_throw_return<unsigned long>()==static_cast<unsigned long>(-1)));
    BOOST_TEST((test_throw_return<long long>()==static_cast<long long>(-1)));
    BOOST_TEST((test_throw_return<unsigned long long>()==static_cast<unsigned long long>(-1)));
    BOOST_TEST((test_throw_return<int *>()==0));
    BOOST_TEST((test_throw_return<boost::shared_ptr<int> >()==boost::shared_ptr<int>()));
    current_error().catch_<>();
    return boost::report_errors();
    }
