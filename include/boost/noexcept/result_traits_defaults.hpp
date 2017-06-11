//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_7A4626864E6A11E7BF51BAE0AD730A1C
#define UUID_7A4626864E6A11E7BF51BAE0AD730A1C

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class T>
        struct
        result_traits_defaults
            {
            static bool succeeded( T const & x ) noexcept { return bool(x); }
            static T error_result() noexcept { return T(); }
            };
        }
    }

#endif
