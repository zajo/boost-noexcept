//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_5872130C482B11E7B84F4C607F4E887A
#define UUID_5872130C482B11E7B84F4C607F4E887A

#include <boost/noexcept/error_handler.hpp>

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class R>
        class
        try_handler:
            public error_handler
            {
            try_handler( try_handler const & )=delete;
            try_handler & operator=( try_handler const & )=delete;
            R res_;
            public:
            explicit
            try_handler( R && res ) noexcept:
                res_(std::move(res))
                {
                }
            try_handler( try_handler && x ) noexcept:
                error_handler(std::move(x)),
                res_(std::move(x.res_))
                {
                }
            explicit operator bool() const noexcept
                {
                return !has_error();
                }
            R const &
            result() const
                {
                if( has_error() )
                    {
                    BOOST_NOEXCEPT_ASSERT(has_error());
                    throw_exception();
                    std::terminate();
                    }
                else
                    return res_;
                }
            R &
            result()
                {
                if( has_error() )
                    {
                    BOOST_NOEXCEPT_ASSERT(has_error());
                    throw_exception();
                    std::terminate();
                    }
                else
                    return res_;
                }
            };
        template <class R>
        try_handler<R>
        try_( R && x ) noexcept //Takes any type for which the result_traits template is specialized
            {
            return try_handler<R>(std::move(x));
            }
        }
    }

#endif
