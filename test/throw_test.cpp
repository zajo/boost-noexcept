//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/core/lightweight_test.hpp>
#include <system_error>

using namespace boost::noexcept_;

struct
f1_failed
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
int
f1() noexcept
    {
    return throw_(f1_failed(1));
    }
int
f2() noexcept
    {
    return f1();
    }
int
f3() noexcept
    {
    auto r=try_(f2());
    BOOST_TEST(!r);
    return r.throw_();
    }
int
f4() noexcept
    {
    auto r=try_(f3());
    BOOST_TEST(!r);
    BOOST_TEST(r.catch_<f1_failed>()->val==1);
    return throw_(f4_failed(2));
    }
int
f5() noexcept
    {
    BOOST_TEST(f4()==-1);
    return throw_();
    }
void
f6_a() noexcept
    {
    auto r=try_(f5());
    BOOST_TEST(!r);
    BOOST_TEST(r.catch_<f4_failed>()->val==2);
    }
void
f6_b() noexcept
    {
    auto r=try_(f5());
    BOOST_TEST(!r);
    if( auto v=r.catch_<f1_failed>() )
        BOOST_TEST(v->val==2);
    else
        (void) r.catch_<f4_failed>(); //In case of no RTTI
    }
struct derives_from_std_exception: std::exception { };
int
throw_std_exception() noexcept
    {
    return throw_(derives_from_std_exception());
    }
void
std_exception_test() noexcept
    {
    if( auto r=try_(throw_std_exception()) )
        BOOST_TEST(false);
    else
        BOOST_TEST(r.catch_<>()!=0);
    }
int
rethrow_fn() noexcept
    {
    auto r=try_(f1());
    BOOST_TEST(!r);
    BOOST_TEST(!has_current_error());
    BOOST_TEST(r.catch_<>()!=0);
    return r.throw_();
    }
void
rethrow_test() noexcept
    {
    auto r=try_(rethrow_fn());
    BOOST_TEST(!r);
    BOOST_TEST(!has_current_error());
    BOOST_TEST(r.catch_<>()!=0);
    }
void
throw_void_test() noexcept
    {
    return (void) throw_(f1_failed(42));
    }
int
throw_error_code_test()
    {
    return throw_(std::error_code{42,std::system_category()});
    }
int
main()
    {
    f6_a();
    f6_b();
    std_exception_test();
    rethrow_test();
        {
        throw_void_test();
        auto r=current_error();
        BOOST_TEST(r.has_error());
        BOOST_TEST(r.catch_<f1_failed>() && r.catch_<f1_failed>()->val==42);
        }
        {
        auto r=try_(throw_error_code_test());
        BOOST_TEST(!r);
        BOOST_TEST(r.catch_<std::error_code>()->value()==42);
        }
    return boost::report_errors();
    }
