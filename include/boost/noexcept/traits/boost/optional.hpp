//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_3E0F79DC4A2E11E7B4B6E8AAAD730A1C
#define UUID_3E0F79DC4A2E11E7B4B6E8AAAD730A1C

#include <boost/noexcept/result_traits_defaults.hpp>
namespace boost { template <class> class optional; }

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class T> struct result_traits;
        template <class T> struct result_traits<optional<T> >: result_traits_defaults<optional<T> > { };
        }
    }

#endif
