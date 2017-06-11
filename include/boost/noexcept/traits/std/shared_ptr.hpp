//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_2A197E124CEC11E7A042464AAD730A1C
#define UUID_2A197E124CEC11E7A042464AAD730A1C

#include <boost/noexcept/result_traits_defaults.hpp>
#include <memory>

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class T> struct result_traits;
        template <class T> struct result_traits<std::shared_ptr<T> >: result_traits_defaults<std::shared_ptr<T> > { };
        }
    }

#endif
