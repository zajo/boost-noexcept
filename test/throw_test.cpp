//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/result_traits_optional.hpp>
#include <boost/optional.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

struct
f1_failed:
    std::exception
    {
    int const val;
    explicit
    f1_failed( int val ) noexcept:
        val(val)
        {
        }
    };
struct
f4_failed:
    f1_failed
    {
    explicit
    f4_failed( int val ) noexcept:
        f1_failed(val)
        {
        }
    };
boost::optional<int>
f1() noexcept
    {
    return throw_(f1_failed(1));
    }
boost::optional<int>
f2() noexcept
    {
    return f1();
    }
boost::optional<int>
f3() noexcept
    {
    auto tr=try_(f2());
    BOOST_TEST(!tr);
    return throw_();
    }
boost::optional<int>
f4() noexcept
    {
    auto tr=try_(f3());
    BOOST_TEST(!tr);
    BOOST_TEST(tr.catch_<f1_failed>()->val==1);
    return throw_(f4_failed(2));
    }
boost::optional<int>
f5() noexcept
    {
    BOOST_TEST(!f4());
    return throw_();
    }
int
f6_a() noexcept
    {
    auto tr=try_(f5());
    BOOST_TEST(!tr);
    BOOST_TEST(tr.catch_<f4_failed>()->val==2);
    return 42;
    }
int
f6_b() noexcept
    {
    auto tr=try_(f5());
    BOOST_TEST(!tr);
    BOOST_TEST(tr.catch_<f1_failed>()->val==2);
    return 42;
    }
int
main()
    {
    BOOST_TEST(f6_a()==42);
    BOOST_TEST(f6_b()==42);
    return boost::report_errors();
    }
