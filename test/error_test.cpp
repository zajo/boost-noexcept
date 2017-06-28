//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/core/lightweight_test.hpp>
#include <string>

using namespace boost::noexcept_::noexcept_detail;

struct
test_base
    {
    std::shared_ptr<void> track_;
    protected:
    test_base( std::weak_ptr<void> & track ) noexcept:
        track_(std::make_shared<int>(42))
        {
        track=track_;
        }
    virtual
    ~test_base()
        {
        }
    test_base( test_base const & ) = default;
    test_base( test_base && ) = default;
    };
struct
test_type00:
    test_base
    {
    test_type00( std::weak_ptr<void> & track ) noexcept: test_base(track) { }
    test_type00( test_type00 const & ) = default;
    test_type00( test_type00 && ) = default;
    };
struct
test_type01:
    test_base,
    boost::noexcept_::exception_info
    {
    test_type01( std::weak_ptr<void> & track ) noexcept: test_base(track) { }
    test_type01( test_type01 const & ) = default;
    test_type01( test_type01 && ) = default;
    };
struct
test_type10:
    test_base,
    std::exception
    {
    test_type10( std::weak_ptr<void> & track ) noexcept: test_base(track) { }
    test_type10( test_type10 const & ) = default;
    test_type10( test_type10 && ) = default;
    };
struct
test_type11:
    test_base,
    std::exception,
    boost::noexcept_::exception_info
    {
    test_type11( std::weak_ptr<void> & track ) noexcept: test_base(track) { }
    test_type11( test_type11 const & ) = default;
    test_type11( test_type11 && ) = default;
    };
template <class T>
bool
check( error_base * eb, bool dynamic ) noexcept
    {
    return
        eb &&
        eb->get_std_exception() &&
        dynamic_cast<error_base *>(eb->get_std_exception())==eb &&
        eb->get_exception_info() &&
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
        dynamic_cast<error_base *>(eb->get_exception_info())==eb &&
#endif
        eb->get_obj(&tid_<T const>) &&
        (!dynamic || dynamic_cast<std::exception *>(static_cast<test_base *>(eb->get_obj(&tid_<T const>)))==eb->get_std_exception());
    }
template <class T>
void
test_lifetime() noexcept
    {
    error_storage st1;
    error_base * err1=0;
    mover_t * mv1=0;
    std::weak_ptr<void> tr;
        {
        error e1((T(tr)));
        BOOST_TEST(e1.get<T>() && e1.get<T>()->track_ && tr.lock()==e1.get<T>()->track_);
        error e2(std::move(e1));
        BOOST_TEST(e1.get<T>()==0);
        BOOST_TEST(e2.get<T>() && e2.get<T>()->track_ && tr.lock()==e2.get<T>()->track_);
        e2.move_to(mv1,&st1,err1);
        BOOST_TEST(e1.get<T>()==0);
        BOOST_TEST(e2.get<T>()==0);
        BOOST_TEST(!tr.expired());
        }
    BOOST_TEST(!tr.expired());
    BOOST_TEST(err1!=0);
    BOOST_TEST(mv1==&move_<typename wrap<T>::type>);
    BOOST_TEST(check<T>(err1,true));
        {
        error e1(mv1,&st1,err1);
        BOOST_TEST(err1==0);
        BOOST_TEST(e1.get<T>() && e1.get<T>()->track_ && tr.lock()==e1.get<T>()->track_);
        error e2(std::move(e1));
        BOOST_TEST(e1.get<T>()==0);
        BOOST_TEST(e2.get<T>() && e2.get<T>()->track_ && tr.lock()==e2.get<T>()->track_);
        BOOST_TEST(!tr.expired());
        }
    BOOST_TEST(tr.expired());
    }
template <>
void
test_lifetime<int>() noexcept
    {
    error_storage st1;
    error_base * err1=0;
    mover_t * mv1=0;
        {
        error e1(42);
        BOOST_TEST(e1.get<int>()!=0);
        error e2(std::move(e1));
        BOOST_TEST(e1.get<int>()==0);
        BOOST_TEST(e2.get<int>()!=0);
        e2.move_to(mv1,&st1,err1);
        BOOST_TEST(e1.get<int>()==0);
        BOOST_TEST(e2.get<int>()==0);
        }
    BOOST_TEST(err1!=0);
    BOOST_TEST(mv1==&move_<typename wrap<int>::type>);
    BOOST_TEST(check<int>(err1,false));
        {
        error e1(mv1,&st1,err1);
        BOOST_TEST(err1==0);
        BOOST_TEST(e1.get<int>()!=0);
        error e2(std::move(e1));
        BOOST_TEST(e1.get<int>()==0);
        BOOST_TEST(e2.get<int>()!=0);
        }
    }
template <class T>
void
test_ceh() noexcept
    {
    std::weak_ptr<void> tr;
    ceh().put(T(tr));
    BOOST_TEST(tr.lock().use_count()==2);
    BOOST_TEST(ceh().extract().get<T>()!=0);
    }
template <>
void
test_ceh<int>() noexcept
    {
    ceh().put(42);
    BOOST_TEST(*ceh().extract().get<int>()==42);
    }
template <class T>
void
test_throw_exception()
    {
    std::weak_ptr<void> tr;
    error e((T(tr)));
    BOOST_TEST(!tr.expired());
    try
        {
        e.throw_exception();
        BOOST_TEST(false);
        }
    catch( T & e )
        {
        BOOST_TEST(tr.lock()==e.track_);
        BOOST_TEST(check<T>(dynamic_cast<error_base *>(&e),true));
        }
    try
        {
        e.throw_exception();
        BOOST_TEST(false);
        }
    catch( std::exception & e )
        {
        BOOST_TEST(check<T>(dynamic_cast<error_base *>(&e),true));
        }
    try
        {
        e.throw_exception();
        BOOST_TEST(false);
        }
    catch( boost::noexcept_::exception_info & e )
        {
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
        BOOST_TEST(check<T>(dynamic_cast<error_base *>(&e),true));
#endif
        }
    }
template <>
void
test_throw_exception<int>()
    {
    error e(42);
    try
        {
        e.throw_exception();
        BOOST_TEST(false);
        }
    catch( int & e )
        {
        BOOST_TEST(e==42);
        }
    }
int
main()
    {
    test_lifetime<test_type00>();
    test_lifetime<test_type01>();
    test_lifetime<test_type10>();
    test_lifetime<test_type11>();
    test_lifetime<int>();
    test_throw_exception<test_type00>();
    test_throw_exception<test_type01>();
    test_throw_exception<test_type10>();
    test_throw_exception<test_type11>();
    test_throw_exception<int>();
    test_ceh<test_type00>();
    test_ceh<test_type01>();
    test_ceh<test_type10>();
    test_ceh<test_type11>();
    test_ceh<int>();
    return boost::report_errors();
    }
