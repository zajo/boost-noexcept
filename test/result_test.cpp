//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/result.hpp>
#include <boost/core/lightweight_test.hpp>

using namespace boost::noexcept_;

int count_=0;

struct
test_type
    {
    private:
    test_type & operator=( test_type const & )=delete;
    public:
    int value;
    explicit
    test_type( int value ) noexcept:
        value(value)
        {
        ++count_;
        }
    test_type( test_type const & x ) noexcept:
        value(x.value)
        {
        ++count_;
        }
    test_type( test_type && x ) noexcept:
        value(x.value)
        {
        ++count_;
        }
    ~test_type() noexcept
        {
        --count_;
        }
    };
namespace
boost
    {
    namespace
    noexcept_
        {
        template <>
        struct
        throw_return<test_type>
            {
            static test_type value() noexcept { return test_type(-1); }
            };
        }
    }
test_type
succeeds() noexcept
    {
    return test_type(42);
    }
int
fails() noexcept
    {
    return throw_(test_type(43));
    }
int
main()
    {
        {
        result<void> x=make_result(throw_(test_type(43)));
        BOOST_TEST(count_==1);
        if( auto tr=try_(std::move(x)) )
            BOOST_TEST(false);
        else
            BOOST_TEST(tr.catch_<test_type>()->value==43);
        }
        {
        result<test_type> x=make_result(succeeds());
        BOOST_TEST(count_==1);
        result<test_type> y(std::move(x));
        BOOST_TEST(count_==2);
        }
        {
        auto tr=try_(make_result(succeeds()));
        BOOST_TEST(count_==1);
        BOOST_TEST(tr);
        BOOST_TEST(tr.get().value==42);
        }
        {
        result<int> x=make_result(fails());
        BOOST_TEST(count_==1);
        result<int> y(std::move(x));
        BOOST_TEST(count_==1);
        auto tr=try_(std::move(y));
        BOOST_TEST(count_==1);
        BOOST_TEST(!tr);
        BOOST_TEST(tr.catch_<test_type>()->value==43);
        }
    BOOST_TEST(count_==0);
    return boost::report_errors();
    }
