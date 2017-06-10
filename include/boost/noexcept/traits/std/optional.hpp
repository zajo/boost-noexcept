//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_15ABFA184BFC11E7B3CEBE59AD730A1C
#define UUID_15ABFA184BFC11E7B3CEBE59AD730A1C

#include <optional>

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class>
        struct result_traits;

        template <class T>
        struct
        result_traits<std::optional<T> >
            {
            static
            bool
            succeeded( std::optional<T> const & x ) noexcept
                {
                return bool(x);
                }
            static
            std::optional<T>
            error_result() noexcept
                {
                return std::optional<T>();
                }
            };
        }
    }

#endif
