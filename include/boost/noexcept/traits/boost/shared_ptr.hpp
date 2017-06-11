//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_8F4F67004CE811E795FDE142AD730A1C
#define UUID_8F4F67004CE811E795FDE142AD730A1C

#include <boost/noexcept/result_traits_defaults.hpp>
namespace boost { template <class> class shared_ptr; }

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class T> struct result_traits;
        template <class T> struct result_traits<shared_ptr<T> >: result_traits_defaults<shared_ptr<T> > { };
        }
    }


#endif
