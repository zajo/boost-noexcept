//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_detail/error.hpp>
#include <boost/core/lightweight_test.hpp>
#include <exception>
#include <string.h>

using boost::noexcept_::noexcept_detail::error;
using boost::noexcept_::exception_info;

namespace
boost
    {
    namespace
    noexcept_
        {
        namespace
        noexcept_detail
            {
            template <class T>
            T *
            new_nothrow_move( T && x ) noexcept
                {
                return new (std::nothrow) T(std::move(x));
                }
            }
        }
    }

static int total_count_;
static int small_count_;
static int big_count_;

class
common_base
    {
    public:
    char const * tag;
    protected:
    explicit
    common_base( char const * tag ) noexcept:
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
    virtual ~common_base() noexcept
        {
        --total_count_;
        }
    };
class
small_base:
    public common_base
    {
    small_base & operator=( small_base const & )=delete;
    public:
    small_base() noexcept:
        common_base("small")
        {
        ++small_count_;
        }
    small_base( small_base const & x ) noexcept:
        common_base(x)
        {
        ++small_count_;
        }
    small_base( small_base && x ) noexcept:
        common_base(std::move(static_cast<common_base &&>(x)))
        {
        ++small_count_;
        }
    ~small_base() noexcept
        {
        --small_count_;
        }
    };
template <bool DeriveFromStdException,bool DeriveFromExceptionInfo> class small;
template <> class small<false,false>: public small_base { };
template <> class small<true,false>: public small_base, public std::exception { };
template <> class small<false,true>: public small_base, public exception_info { };
template <> class small<true,true>: public small_base, public std::exception, public exception_info { };
class
big_base:
    public common_base
    {
    big_base & operator=( big_base const & )=delete;
    unsigned char filler_[error::max_static_size];
    public:
    big_base() noexcept:
        common_base("big")
        {
        ++big_count_;
        }
    big_base( big_base const & x ) noexcept:
        common_base(x)
        {
        ++big_count_;
        }
    big_base( big_base && x ) noexcept:
        common_base(std::move(static_cast<common_base &&>(x)))
        {
        ++big_count_;
        }
    ~big_base() noexcept
        {
        --big_count_;
        }
    };
template <bool DeriveFromStdException,bool DeriveFromExceptionInfo> class big;
template <> class big<false,false>: public big_base { };
template <> class big<true,false>: public big_base, public std::exception { };
template <> class big<false,true>: public big_base, public exception_info { };
template <> class big<true,true>: public big_base, public std::exception, public exception_info { };

bool
check_counts( int sc, int bc ) noexcept
    {
    return
        small_count_+big_count_==total_count_ &&
        small_count_==sc &&
        big_count_==bc;
    }
//////////////////////////////////
void
check_small_base( small_base const * x ) noexcept
    {
    BOOST_TEST(x!=0);
    BOOST_TEST(strcmp(x->tag,"small")==0);
    }
void
check_small_std_exception( std::exception const * x ) noexcept
    {
    BOOST_TEST(x!=0);
    BOOST_TEST(dynamic_cast<exception_info const *>(x)!=0);
    check_small_base(dynamic_cast<small_base const *>(x));
    }
void
check_small_exception_info( exception_info const * x ) noexcept
    {
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
    BOOST_TEST(x==0);
#else
    BOOST_TEST(x!=0);
    BOOST_TEST(dynamic_cast<std::exception const *>(x)!=0);
    check_small_base(dynamic_cast<small_base const *>(x));
#endif
    }
template <class Small>
void
check_small( error & err ) noexcept
    {
    BOOST_TEST(!err.empty());
    BOOST_TEST(err.holds_static());
    BOOST_TEST(!err.holds_dynamic());
    check_small_base(err.get<Small>());
    check_small_std_exception(err.get<std::exception>());
    check_small_exception_info(err.get<exception_info>());
    check_small_base(err.get<Small const>());
    check_small_std_exception(err.get<std::exception const>());
    check_small_exception_info(err.get<exception_info const>());
    error const & cerr=err;
    check_small_base(cerr.get<Small>());
    check_small_std_exception(cerr.get<std::exception>());
    check_small_exception_info(cerr.get<exception_info>());
    check_small_base(cerr.get<Small const>());
    check_small_std_exception(cerr.get<std::exception const>());
    check_small_exception_info(cerr.get<exception_info const>());
    }
//////////////////////////////////
void
check_big_base( big_base const * x ) noexcept
    {
    BOOST_TEST(x!=0);
    BOOST_TEST(strcmp(x->tag,"big")==0);
    }
void
check_big_std_exception( std::exception const * x ) noexcept
    {
    BOOST_TEST(x!=0);
    BOOST_TEST(dynamic_cast<exception_info const *>(x)!=0);
    check_big_base(dynamic_cast<big_base const *>(x));
    }
void
check_big_exception_info( exception_info const * x ) noexcept
    {
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
    BOOST_TEST(x==0);
#else
    BOOST_TEST(x!=0);
    BOOST_TEST(dynamic_cast<std::exception const *>(x)!=0);
    check_big_base(dynamic_cast<big_base const *>(x));
#endif
    }
template <class Big>
void
check_big( error & err ) noexcept
    {
    BOOST_TEST(!err.empty());
    BOOST_TEST(!err.holds_static());
    BOOST_TEST(err.holds_dynamic());
    check_big_base(err.get<Big>());
    check_big_std_exception(err.get<std::exception>());
    check_big_exception_info(err.get<exception_info>());
    check_big_base(err.get<Big const>());
    check_big_std_exception(err.get<std::exception const>());
    check_big_exception_info(err.get<exception_info const>());
    error const & cerr=err;
    check_big_base(cerr.get<Big>());
    check_big_std_exception(cerr.get<std::exception>());
    check_big_exception_info(cerr.get<exception_info>());
    check_big_base(cerr.get<Big const>());
    check_big_std_exception(cerr.get<std::exception const>());
    check_big_exception_info(cerr.get<exception_info const>());
    }
//////////////////////////////////
void
check_int( error & err ) noexcept
    {
    BOOST_TEST(!err.empty());
    BOOST_TEST(err.holds_static());
    BOOST_TEST(!err.holds_dynamic());
    BOOST_TEST(err.get<int>() && *err.get<int>()==42);
    BOOST_TEST(err.get<std::exception>()!=0);
    BOOST_TEST(err.get<int const>() && *err.get<int const>()==42);
    BOOST_TEST(err.get<std::exception const>()!=0);
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
    BOOST_TEST(err.get<exception_info>()==0);
    BOOST_TEST(err.get<exception_info const>()==0);
#else
    BOOST_TEST(err.get<exception_info>()!=0);
    BOOST_TEST(err.get<exception_info const>()!=0);
#endif
    error const & cerr=err;
    BOOST_TEST(cerr.get<int>() && *err.get<int>()==42);
    BOOST_TEST(cerr.get<std::exception>()!=0);
    BOOST_TEST(cerr.get<int const>() && *err.get<int const>()==42);
    BOOST_TEST(cerr.get<std::exception const>()!=0);
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
    BOOST_TEST(cerr.get<exception_info>()==0);
    BOOST_TEST(cerr.get<exception_info const>()==0);
#else
    BOOST_TEST(cerr.get<exception_info>()!=0);
    BOOST_TEST(cerr.get<exception_info const>()!=0);
#endif
    }
//////////////////////////////////
void
check_empty( error & err ) noexcept
    {
    BOOST_TEST(err.empty());
    BOOST_TEST(!err.holds_static());
    BOOST_TEST(!err.holds_dynamic());
    BOOST_TEST(!err.get<std::exception>());
    BOOST_TEST(!err.get<exception_info>());
    BOOST_TEST(!err.get<std::exception const>());
    BOOST_TEST(!err.get<exception_info const>());
    error const & cerr=err;
    BOOST_TEST(!cerr.get<std::exception>());
    BOOST_TEST(!cerr.get<exception_info>());
    BOOST_TEST(!cerr.get<std::exception const>());
    BOOST_TEST(!cerr.get<exception_info const>());
    }
//////////////////////////////////
template <class Small,class Big>
void
test_lifetime() noexcept
    {
        {
        error ex;
        check_empty(ex);
        BOOST_TEST(check_counts(0,0));
        ex.put(Small());
        check_small<Small>(ex);
        BOOST_TEST(check_counts(1,0));
        ex.put(Big());
        check_big<Big>(ex);
        BOOST_TEST(check_counts(0,1));
        ex.put(42);
        BOOST_TEST(check_counts(0,0));
        check_int(ex);
        ex.clear();
        check_empty(ex);
        BOOST_TEST(check_counts(0,0));
        ex.put(Small());
        check_small<Small>(ex);
        BOOST_TEST(check_counts(1,0));
            {
            error ex1(std::move(ex));
            check_empty(ex);
            check_small<Small>(ex1);
            BOOST_TEST(check_counts(1,0));
            ex1.put(42);
            BOOST_TEST(check_counts(0,0));
            check_int(ex1);
            }
        BOOST_TEST(check_counts(0,0));
        ex.put(Big());
        check_big<Big>(ex);
        BOOST_TEST(check_counts(0,1));
            {
            error ex1(std::move(ex));
            check_empty(ex);
            check_big<Big>(ex1);
            BOOST_TEST(check_counts(0,1));
            ex1.put(42);
            BOOST_TEST(check_counts(0,0));
            check_int(ex1);
            }
        }
    BOOST_TEST(check_counts(0,0));
    }
template <class Small,class Big>
void
test_throw_exception() noexcept
    {
        {
        error ex;
        ex.put(Big());
        try
            {
            ex.throw_exception();
            BOOST_TEST(false);
            }
        catch( big_base & b )
            {
            check_big_base(&b);
            }
        try
            {
            ex.throw_exception();
            BOOST_TEST(false);
            }
        catch( std::exception & e )
            {
            check_big_std_exception(&e);
            }
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
        try
            {
            ex.throw_exception();
            BOOST_TEST(false);
            }
        catch( exception_info & e )
            {
            check_big_exception_info(&e);
            }
#endif
        }
        {
        error ex;
        ex.put(Small());
        try
            {
            ex.throw_exception();
            BOOST_TEST(false);
            }
        catch( small_base & s )
            {
            check_small_base(&s);
            }
        try
            {
            ex.throw_exception();
            BOOST_TEST(false);
            }
        catch( std::exception & e )
            {
            check_small_std_exception(&e);
            }
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
        try
            {
            ex.throw_exception();
            BOOST_TEST(false);
            }
        catch( exception_info & e )
            {
            check_small_exception_info(&e);
            }
#endif
        }
        {
        error ex;
        ex.put(42);
        try
            {
            ex.throw_exception();
            BOOST_TEST(false);
            }
        catch( int & s )
            {
            BOOST_TEST(s==42);
            }
        }
    }
int
main()
    {
    test_lifetime<small<false,false>, big<false,false> >();
    test_lifetime<small<true,false>, big<true,false> >();
    test_lifetime<small<false,true>, big<false,true> >();
    test_lifetime<small<true,true>, big<true,true> >();
    test_throw_exception<small<false,false>, big<false,false> >();
    test_throw_exception<small<true,false>, big<true,false> >();
    test_throw_exception<small<false,true>, big<false,true> >();
    test_throw_exception<small<true,true>, big<true,true> >();
    return boost::report_errors();
    }
