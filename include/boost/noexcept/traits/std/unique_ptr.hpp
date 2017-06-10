//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_3A89AA724CEE11E7AEE1324DAD730A1C
#define UUID_3A89AA724CEE11E7AEE1324DAD730A1C

#include <memory>

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class>
        struct result_traits;

        template <class T,class D>
        struct
        result_traits<std::unique_ptr<T,D> >
            {
            static
            bool
            succeeded( std::unique_ptr<T,D> const & x ) noexcept
                {
                return x!=nullptr;
                }
            static
            std::unique_ptr<T,D>
            error_result() noexcept
                {
                return std::unique_ptr<T,D>();
                }
            };
        }
    }

#endif
