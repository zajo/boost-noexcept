//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_F21B7EBA4CEC11E78CDC864BAD730A1C
#define UUID_F21B7EBA4CEC11E78CDC864BAD730A1C

#include <boost/noexcept/result_traits_defaults.hpp>
namespace boost { namespace movelib { template <class,class> class unique_ptr; } }

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class T> struct result_traits;
        template <class T,class D> struct result_traits<movelib::unique_ptr<T,D> >: result_traits_defaults<movelib::unique_ptr<T,D> > { };
        }
    }

#endif
