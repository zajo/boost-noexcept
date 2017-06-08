//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_detail/any_movable.hpp>
#include <boost/core/lightweight_test.hpp>
#include <exception>
#include <string>

static int const max_static_size=256;
static int total_count_;
static int small_count_;
static int big_count_;

class
common_base:
    public std::exception
    {
    char const *
    what() const noexcept
        {
        return tag.c_str();
        }
    public:
    std::string tag;
    protected:
    explicit
    common_base( std::string const & tag ) noexcept:
        tag(tag)
        {
        ++total_count_;
        }
    common_base( common_base const & x ) noexcept:
        tag(x.tag)
        {
        ++total_count_;
        }
    common_base( common_base && x ) noexcept:
        tag(std::move(x.tag))
        {
        ++total_count_;
        }
    ~common_base() noexcept
        {
        --total_count_;
        }
    };
class
small:
    public common_base
    {
    small & operator=( small const & )=delete;
    public:
    small() noexcept:
        common_base("small")
        {
        ++small_count_;
        }
    small( small const & x ) noexcept:
        common_base(x)
        {
        ++small_count_;
        }
    small( small && x ) noexcept:
        common_base(std::move(static_cast<common_base &&>(x)))
        {
        ++small_count_;
        }
    ~small() noexcept
        {
        --small_count_;
        }
    };
class
big:
    public common_base
    {
    big & operator=( big const & )=delete;
    unsigned char filler_[max_static_size];
    public:
    big() noexcept:
        common_base("big")
        {
        ++big_count_;
        }
    big( big const & x ) noexcept:
        common_base(x)
        {
        ++big_count_;
        }
    big( big && x ) noexcept:
        common_base(std::move(static_cast<common_base &&>(x)))
        {
        ++big_count_;
        }
    ~big() noexcept
        {
        --big_count_;
        }
    };
typedef boost::noexcept_::noexcept_detail::any_movable<max_static_size,common_base> test_type;
bool
check_counts( int sc, int bc ) noexcept
    {
    return
        small_count_+big_count_==total_count_ &&
        small_count_==sc &&
        big_count_==bc;
    }
void
test_lifetime() noexcept
    {
    using namespace boost::noexcept_::noexcept_detail;
        {
        test_type ex;
        BOOST_TEST(ex.empty());
        BOOST_TEST(!ex.holds_static());
        BOOST_TEST(!ex.holds_dynamic());
        BOOST_TEST(check_counts(0,0));
        ex.put(small());
        BOOST_TEST(dynamic_cast<small *>(ex.get())!=0);
        BOOST_TEST(!ex.empty());
        BOOST_TEST(ex.holds_static());
        BOOST_TEST(!ex.holds_dynamic());
        BOOST_TEST(ex.get()->tag=="small");
        BOOST_TEST(check_counts(1,0));
        ex.put(big());
        BOOST_TEST(dynamic_cast<big *>(ex.get())!=0);
        BOOST_TEST(!ex.empty());
        BOOST_TEST(!ex.holds_static());
        BOOST_TEST(ex.holds_dynamic());
        BOOST_TEST(ex.get()->tag=="big");
        BOOST_TEST(check_counts(0,1));
        ex.clear();
        BOOST_TEST(ex.empty());
        BOOST_TEST(!ex.holds_static());
        BOOST_TEST(!ex.holds_dynamic());
        BOOST_TEST(check_counts(0,0));
        ex.put(small());
        BOOST_TEST(dynamic_cast<small *>(ex.get())!=0);
        BOOST_TEST(!ex.empty());
        BOOST_TEST(ex.holds_static());
        BOOST_TEST(!ex.holds_dynamic());
        BOOST_TEST(ex.get()->tag=="small");
        BOOST_TEST(check_counts(1,0));
            {
            test_type ex1(std::move(ex));
            BOOST_TEST(ex.empty());
            BOOST_TEST(!ex.holds_static());
            BOOST_TEST(!ex.holds_dynamic());
            BOOST_TEST(dynamic_cast<small *>(ex1.get())!=0);
            BOOST_TEST(!ex1.empty());
            BOOST_TEST(ex1.holds_static());
            BOOST_TEST(!ex1.holds_dynamic());
            BOOST_TEST(ex1.get()->tag=="small");
            BOOST_TEST(check_counts(1,0));
            }
        BOOST_TEST(check_counts(0,0));
        ex.put(big());
        BOOST_TEST(dynamic_cast<big *>(ex.get())!=0);
        BOOST_TEST(!ex.empty());
        BOOST_TEST(!ex.holds_static());
        BOOST_TEST(ex.holds_dynamic());
        BOOST_TEST(ex.get()->tag=="big");
        BOOST_TEST(check_counts(0,1));
            {
            test_type ex1(std::move(ex));
            BOOST_TEST(ex.empty());
            BOOST_TEST(!ex.holds_static());
            BOOST_TEST(!ex.holds_dynamic());
            BOOST_TEST(dynamic_cast<big *>(ex1.get())!=0);
            BOOST_TEST(!ex1.empty());
            BOOST_TEST(!ex1.holds_static());
            BOOST_TEST(ex1.holds_dynamic());
            BOOST_TEST(ex1.get()->tag=="big");
            BOOST_TEST(check_counts(0,1));
            }
        }
    BOOST_TEST(check_counts(0,0));
    }

template <class T>
void
throw_exception_( common_base * obj )
    {
    throw *static_cast<T *>(obj);
    }

void
test_throw_exception() noexcept
    {
    using namespace boost::noexcept_::noexcept_detail;
        {
        test_type ex;
        ex.put(big(),&throw_exception_<big>);
        try
            {
            ex.call_observer();
            BOOST_TEST(false);
            }
        catch( big & b )
            {
            BOOST_TEST(b.tag=="big");
            }
        try
            {
            ex.call_observer();
            BOOST_TEST(false);
            }
        catch( std::exception & e )
            {
            BOOST_TEST(strcmp(e.what(),"big")==0);
            }
        }
        {
        test_type ex;
        ex.put(small(),&throw_exception_<small>);
        try
            {
            ex.call_observer();
            BOOST_TEST(false);
            }
        catch( small & s )
            {
            BOOST_TEST(s.tag=="small");
            }
        try
            {
            ex.call_observer();
            BOOST_TEST(false);
            }
        catch( std::exception & e )
            {
            BOOST_TEST(strcmp(e.what(),"small")==0);
            }
        }
    }
int
main()
    {
    test_lifetime();
    test_throw_exception();
    return boost::report_errors();
    }
