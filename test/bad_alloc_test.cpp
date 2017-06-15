//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/error_handler.hpp>
#include <boost/noexcept/error_ptr.hpp>
#include <boost/core/lightweight_test.hpp>
#include <exception>
#include <string>

using namespace boost::noexcept_;

static bool new_succeeds=true;

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
            new_nothrow_move( T && x )
                {
                return new_succeeds? new (std::nothrow) T(std::move(x)) : 0;
                }
            template <class T>
            T *
            new_nothrow_copy( T const & x )
                {
                return new_succeeds? new (std::nothrow) T(x) : 0;
                }
            }
        }
    }

struct small_error { };
struct big_error { unsigned char filler_[noexcept_detail::error_holder::max_static_size+1]; };

int
main()
    {
    new_succeeds=true;
        {
        noexcept_detail::put_dispatch<small_error>::put_(small_error());
        error_handler err;
        BOOST_TEST(err.has_error());
        BOOST_TEST(err.catch_<std::bad_alloc>()==0);
        BOOST_TEST(err.catch_<small_error>()!=0);
        }
        {
        noexcept_detail::put_dispatch<big_error>::put_(big_error());
        error_handler err;
        BOOST_TEST(err.has_error());
        BOOST_TEST(err.catch_<std::bad_alloc>()==0);
        BOOST_TEST(err.catch_<big_error>()!=0);
        }
    new_succeeds=false;
        {
        noexcept_detail::put_dispatch<small_error>::put_(small_error());
        error_handler err;
        BOOST_TEST(err.has_error());
        BOOST_TEST(err.catch_<std::bad_alloc>()==0);
        BOOST_TEST(err.catch_<small_error>()!=0);
        }
        {
        noexcept_detail::put_dispatch<big_error>::put_(big_error());
        error_handler err;
        BOOST_TEST(err.has_error());
        BOOST_TEST(err.catch_<big_error>()==0);
        BOOST_TEST(err.catch_<std::bad_alloc>()!=0);
        }
    }
