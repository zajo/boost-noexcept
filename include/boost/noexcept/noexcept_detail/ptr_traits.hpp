//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_60F6CFD84CED11E79AB6604CAD730A1C
#define UUID_60F6CFD84CED11E79AB6604CAD730A1C

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class>
        struct result_traits;

        namespace
        noexcept_detail
            {
            template <class P,class T>
            struct
            ptr_traits
                {
                typedef P result_type;
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
                    return result_type();
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
    }

#endif
