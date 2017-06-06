//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_394C40FA48D611E783AC84CE7E4E887A
#define UUID_394C40FA48D611E783AC84CE7E4E887A

#include <boost/noexcept/propagate.hpp>
#include <boost/noexcept/noexcept_try.hpp>

namespace
boost
    {
    class
    propagate_error_code:
        public propagate
        {
        propagate_error_code( propagate_error_code const & )=delete;
        propagate_error_code & operator=( propagate_error_code const & )=delete;

        public:

        template <class ErrorCodeType>
        class
        wrapper:
            public std::exception
            {
            public:
            ErrorCodeType const err;
            explicit
            wrapper( ErrorCodeType err ):
                err(err)
                {
                }
            };

        template <class ErrorCodeType>
        propagate_error_code( ErrorCodeType err )
            {
            BOOST_NOEXCEPT_ASSERT(noexcept_detail::current_exception().get_exception().empty());
            noexcept_detail::current_exception().put(wrapper<ErrorCodeType>(std::move(err)));
            }
        };

    template <class T>
    template <class ErrorCodeType>
    ErrorCodeType const *
    noexcept_handler<T>::
    noexcept_catch_error_code() noexcept
        {
        std::exception * f=caught().get();
        BOOST_NOEXCEPT_ASSERT(f!=0);
        if( auto * e=dynamic_cast<propagate_error_code::wrapper<ErrorCodeType> *>(f) )
            {
            handled_=true;
            return &e->err;
            }
        return 0;
        }
    }

#endif
