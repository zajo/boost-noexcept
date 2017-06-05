//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_detail/exception_holder.hpp>
#include <boost/core/lightweight_test.hpp>
#include <exception>
#include <string>

int total_count_;
int small_count_;
int big_count_;

class
small:
    public std::exception
    {
    small & operator=( small const & )=delete;
    std::string tag;
    public:
    small() noexcept:
        tag("small")
        {
        ++small_count_;
        ++total_count_;
        }
    small( small const & x ) noexcept:
        tag(x.tag)
        {
        ++small_count_;
        ++total_count_;
        }
    small( small && x ) noexcept:
        tag(std::move(x.tag))
        {
        ++small_count_;
        ++total_count_;
        }
    ~small() noexcept
        {
        --small_count_;
        --total_count_;
        }
    char const *
    what() const noexcept
        {
        return tag.c_str();
        }
    };
class
big:
    public std::exception
    {
    big & operator=( big const & )=delete;
    unsigned char filler_[boost::noexcept_detail::max_static_size];
    std::string tag;
    public:
    big() noexcept:
        tag("big")
        {
        ++big_count_;
        ++total_count_;
        }
    big( big const & x ) noexcept:
        tag(x.tag)
        {
        ++big_count_;
        ++total_count_;
        }
    big( big && x ) noexcept:
        tag(std::move(x.tag))
        {
        ++big_count_;
        ++total_count_;
        }
    ~big() noexcept
        {
        --big_count_;
        --total_count_;
        }
    char const *
    what() const noexcept
        {
        return tag.c_str();
        }
    };
bool
check_counts( int sc, int bc )
    {
    return
        small_count_+big_count_==total_count_ &&
        small_count_==sc &&
        big_count_==bc;
    }
void
test_lifetime()
    {
    using namespace boost::noexcept_detail;
        {
        exception_holder ex;
        BOOST_TEST(ex.empty());
        BOOST_TEST(!ex.holds_static());
        BOOST_TEST(!ex.holds_dynamic());
        BOOST_TEST(check_counts(0,0));
        ex.put(small());
        BOOST_TEST(dynamic_cast<small *>(ex.get())!=0);
        BOOST_TEST(!ex.empty());
        BOOST_TEST(ex.holds_static());
        BOOST_TEST(!ex.holds_dynamic());
        BOOST_TEST(strcmp(ex.what(),"small")==0);
        BOOST_TEST(check_counts(1,0));
        ex.put(big());
        BOOST_TEST(dynamic_cast<big *>(ex.get())!=0);
        BOOST_TEST(!ex.empty());
        BOOST_TEST(!ex.holds_static());
        BOOST_TEST(ex.holds_dynamic());
        BOOST_TEST(strcmp(ex.what(),"big")==0);
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
        BOOST_TEST(strcmp(ex.what(),"small")==0);
        BOOST_TEST(check_counts(1,0));
            {
            exception_holder ex1(std::move(ex));
            BOOST_TEST(ex.empty());
            BOOST_TEST(ex.holds_static());
            BOOST_TEST(!ex.holds_dynamic());
            BOOST_TEST(dynamic_cast<small *>(ex1.get())!=0);
            BOOST_TEST(!ex1.empty());
            BOOST_TEST(ex1.holds_static());
            BOOST_TEST(!ex1.holds_dynamic());
            BOOST_TEST(strcmp(ex1.what(),"small")==0);
            BOOST_TEST(check_counts(2,0));
            }
        BOOST_TEST(check_counts(1,0));
        ex.put(big());
        BOOST_TEST(dynamic_cast<big *>(ex.get())!=0);
        BOOST_TEST(!ex.empty());
        BOOST_TEST(!ex.holds_static());
        BOOST_TEST(ex.holds_dynamic());
        BOOST_TEST(strcmp(ex.what(),"big")==0);
        BOOST_TEST(check_counts(0,1));
            {
            exception_holder ex1(std::move(ex));
            BOOST_TEST(ex.empty());
            BOOST_TEST(!ex.holds_static());
            BOOST_TEST(!ex.holds_dynamic());
            BOOST_TEST(dynamic_cast<big *>(ex1.get())!=0);
            BOOST_TEST(!ex1.empty());
            BOOST_TEST(!ex1.holds_static());
            BOOST_TEST(ex1.holds_dynamic());
            BOOST_TEST(strcmp(ex1.what(),"big")==0);
            BOOST_TEST(check_counts(0,1));
            }
        }
    BOOST_TEST(check_counts(0,0));
    }
void
test_throw_exception()
    {
    using namespace boost::noexcept_detail;
        {
        exception_holder ex;
        ex.put(big());
        try
            {
            ex.throw_exception();
            BOOST_TEST(false);
            }
        catch( big & b )
            {
            BOOST_TEST(strcmp(b.what(),"big")==0);
            }
        }
        {
        exception_holder ex;
        ex.put(small());
        try
            {
            ex.throw_exception();
            BOOST_TEST(false);
            }
        catch( small & s )
            {
            BOOST_TEST(strcmp(s.what(),"small")==0);
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
