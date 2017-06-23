//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/noexcept_detail/error.hpp>
#include <boost/core/lightweight_test.hpp>
#include <exception>
#include <string>

using boost::noexcept_::noexcept_detail::error;

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
            new_nothrow_move( T && x ) noexcept
                {
                return new_succeeds? new (std::nothrow) T(std::move(x)) : 0;
                }
            }
        }
    }

struct small { };
struct big { unsigned char filler_[error::max_static_size+1]; };

int
main()
    {
    new_succeeds=true;
        {
        error x;
        x.put(small());
        BOOST_TEST(!x.empty());
        BOOST_TEST(x.get<std::bad_alloc>()==0);
        BOOST_TEST(x.get<small>()!=0);
        }
        {
        error x;
        x.put(big());
        BOOST_TEST(!x.empty());
        BOOST_TEST(x.get<std::bad_alloc>()==0);
        BOOST_TEST(x.get<big>()!=0);
        }
    new_succeeds=false;
        {
        error x;
        x.put(small());
        BOOST_TEST(!x.empty());
        BOOST_TEST(x.get<std::bad_alloc>()==0);
        BOOST_TEST(x.get<small>()!=0);
        }
        {
        error x;
        x.put(big());
        BOOST_TEST(!x.empty());
        BOOST_TEST(x.get<std::bad_alloc>()!=0);
        BOOST_TEST(x.get<big>()==0);
        }
    }
