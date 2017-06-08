//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/result_traits_optional.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;
using boost::noexcept_::config::optional;

struct
f1_failed:
    std::exception
    {
    int const val;
    explicit
    f1_failed( int val ):
        val(val)
        {
        }
    };
struct
f4_failed:
    f1_failed
    {
    explicit
    f4_failed( int val ):
        f1_failed(val)
        {
        }
    };
optional<int>
f1()
    {
    return throw_(f1_failed(1));
    }
optional<int>
f2()
    {
	return f1();
    }
optional<int>
f3()
    {
    auto tr=try_(f2());
    BOOST_TEST(!tr);
    return throw_();
    }
optional<int>
f4()
    {
    auto tr=try_(f3());
    BOOST_TEST(!tr);
    BOOST_TEST(tr.catch_<f1_failed>()->val==1);
    return throw_(f4_failed(2));
    }
optional<int>
f5()
    {
    BOOST_TEST(!f4());
    return throw_();
    }
int
f6_a()
    {
    auto tr=try_(f5());
    BOOST_TEST(!tr);
    BOOST_TEST(tr.catch_<f4_failed>()->val==2);
    return 42;
    }
int
f6_b()
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
