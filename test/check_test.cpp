//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/try.hpp>
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <algorithm>

using namespace boost::noexcept_;

struct get_int_failed { };
struct negate_failed { };
struct convert_to_string_failed { };
struct reverse_string_failed { };
struct do_work1_failed { };
struct do_work2_failed { };
struct do_work3_failed { };

static int in_get_int_=0;
static int in_negate_=0;
static int in_convert_to_string_=0;
static int in_reverse_string_=0;
static int in_do_work1_=0;
static int in_do_work2_=0;
static int in_do_work3_=0;

bool
check_counters( int in_get_int, int in_negate, int in_convert_to_string, int in_reverse_string, bool clear=true ) noexcept
    {
    bool r = in_get_int==in_get_int_ && in_negate==in_negate_ && in_convert_to_string==in_convert_to_string_ && in_reverse_string==in_reverse_string_;
    if( clear )
        in_get_int_=in_negate_=in_convert_to_string_=in_reverse_string_=0;
    return r;
    }
int
get_int( bool succeed ) noexcept
    {
    ++in_get_int_;
    if( succeed )
        return 42;
    else
        return throw_(get_int_failed());
    }
int
negate( bool succeed, int x ) noexcept
    {
    BOOST_NOEXCEPT_CHECK
    ++in_negate_;
    if( succeed )
        return -x;
    else
        return throw_(negate_failed());
    }
std::string
convert_to_string( bool succeed, int x ) noexcept
    {
    BOOST_NOEXCEPT_CHECK
    ++in_convert_to_string_;
    if( succeed )
        return std::to_string(x);
    else
        return throw_(convert_to_string_failed());
    }
std::string
reverse_string( bool succeed, std::string x ) noexcept
    {
    BOOST_NOEXCEPT_CHECK
    ++in_reverse_string_;
    if( succeed )
        {
        std::reverse(x.begin(),x.end());
        return x;
        }
    else
        return throw_(reverse_string_failed());
    }
bool
check_do_work_counters( int in_do_work1, int in_do_work2, int in_do_work3, bool clear=true ) noexcept
    {
    bool r = in_do_work1==in_do_work1_ && in_do_work2==in_do_work2_ && in_do_work3==in_do_work3_;
    if( clear )
        in_do_work1_=in_do_work2_=in_do_work3_=0;
    return r;
    }
bool
do_work1( bool succeed ) noexcept
    {
    BOOST_NOEXCEPT_CHECK
    ++in_do_work1_;
    if( succeed )
        return true;
    else
        return throw_(do_work1_failed());
    }
bool
do_work2( bool succeed ) noexcept
    {
    BOOST_NOEXCEPT_CHECK
    ++in_do_work2_;
    if( succeed )
        return true;
    else
        return throw_(do_work2_failed());
    }
bool
do_work3( bool succeed ) noexcept
    {
    BOOST_NOEXCEPT_CHECK
    ++in_do_work3_;
    if( succeed )
        return true;
    else
        return throw_(do_work3_failed());
    }
bool
do_work( bool succeed1, bool succeed2, bool succeed3 ) noexcept
    {
    return
        do_work1(succeed1) &&
        do_work2(succeed2) &&
        do_work3(succeed3);
    }
int
main()
    {
    BOOST_TEST(
        reverse_string( true,
            convert_to_string( true,
                negate( true,
                    get_int( true ) ) ) ) == "24-" );
    BOOST_TEST(!has_current_error());
    BOOST_TEST(check_counters(1,1,1,1));
    if( auto r=try_(
        reverse_string( true,
            convert_to_string( true,
                negate( true,
                    get_int( false ) ) ) ) ) )
        BOOST_TEST(false);
    else
        {
        BOOST_TEST(check_counters(1,0,0,0));
        BOOST_TEST(r.catch_<get_int_failed>()!=0);
        }
    if( auto r=try_(
        reverse_string( true,
            convert_to_string( true,
                negate( false,
                    get_int( true ) ) ) ) ) )
        BOOST_TEST(false);
    else
        {
        BOOST_TEST(check_counters(1,1,0,0));
        BOOST_TEST(r.catch_<negate_failed>()!=0);
        }
    if( auto r=try_(
        reverse_string( true,
            convert_to_string( false,
                negate( true,
                    get_int( true ) ) ) ) ) )
        BOOST_TEST(false);
    else
        {
        BOOST_TEST(check_counters(1,1,1,0));
        BOOST_TEST(r.catch_<convert_to_string_failed>()!=0);
        }
    if( auto r=try_(
        reverse_string( false,
            convert_to_string( true,
                negate( true,
                    get_int( true ) ) ) ) ) )
        BOOST_TEST(false);
    else
        {
        BOOST_TEST(check_counters(1,1,1,1));
        BOOST_TEST(r.catch_<reverse_string_failed>()!=0);
        }
    if( auto r=try_(do_work(false,true,true)) )
        BOOST_TEST(false);
    else
        {
        BOOST_TEST(check_do_work_counters(1,0,0));
        BOOST_TEST(r.catch_<do_work1_failed>()!=0);
        }
    if( auto r=try_(do_work(true,false,true)) )
        BOOST_TEST(false);
    else
        {
        BOOST_TEST(check_do_work_counters(1,1,0));
        BOOST_TEST(r.catch_<do_work2_failed>()!=0);
        }
    if( auto r=try_(do_work(true,true,false)) )
        BOOST_TEST(false);
    else
        {
        BOOST_TEST(check_do_work_counters(1,1,1));
        BOOST_TEST(r.catch_<do_work3_failed>()!=0);
        }
        {
        auto r=try_(do_work(true,true,true));
        BOOST_TEST(r);
        check_do_work_counters(1,1,1);
        }
    return boost::report_errors();
    }
