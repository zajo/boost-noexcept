//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_07C5D8B64D9011E7BD94803AAE730A1C
#define UUID_07C5D8B64D9011E7BD94803AAE730A1C

#include <boost/noexcept/noexcept_detail/current_error.hpp>

namespace
boost
    {
    namespace
    noexcept_
        {
        namespace
        noexcept_detail
            {
            inline
            bool
            current_error_holder::
            has_current_error() noexcept
                {
                return !e_.empty() && !h_;
                }
            }
        inline
        bool
        has_current_error() noexcept
            {
            return noexcept_detail::current_error().has_current_error();
            }
        }
    }

#endif
