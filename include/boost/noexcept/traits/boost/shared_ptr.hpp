//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_8F4F67004CE811E795FDE142AD730A1C
#define UUID_8F4F67004CE811E795FDE142AD730A1C

namespace boost { template <class> class shared_ptr; }

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
        result_traits<shared_ptr<T> >
            {
            typedef shared_ptr<T> result_type;
            typedef T value_type;
            static
            bool
            succeeded( result_type const & x ) noexcept
                {
                return bool(x);
                }
            static
            result_type
            error_result() noexcept
                {
                return result_type();;
                }
            static
            value_type const &
            success_value( result_type const & x ) noexcept
                {
                return *x;
                }
            static
            value_type &
            success_value( result_type & x ) noexcept
                {
                return *x;
                }
            };
        }
    }

#endif
