//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_704300904C0411E7A09C0D65AD730A1C
#define UUID_704300904C0411E7A09C0D65AD730A1C

#include <boost/noexcept/noexcept_config/assert.hpp>
#include <utility>

namespace boost { namespace noexcept_ { template <class> struct result_traits; } }

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class T>
        class
        checker
            {
            checker( checker const & )=delete;
            checker & operator=( checker const & )=delete;
            T val_;
            public:
            explicit
            checker( T && val ) noexcept:
                val_(std::move(val))
                {
                }
            checker( checker && x ) noexcept:
                val_(std::move(x.val_))
                {
                }
            explicit operator bool() const noexcept
                {
                return result_traits<T>::succeeded(val_);
                }
            typename result_traits<T>::value_type const &
            value() const noexcept
                {
                BOOST_NOEXCEPT_ASSERT(result_traits<T>::succeeded(val_));
                return result_traits<T>::success_value(val_);
                }
            typename result_traits<T>::value_type &
            value() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(result_traits<T>::succeeded(val_));
                return result_traits<T>::success_value(val_);
                }
            };
        template <class T>
        checker<T>
        succeeded_( T && x ) noexcept //Takes any type for which the result_traits template is specialized
            {
            return checker<T>(std::move(x));
            }
        }
    }

#endif
