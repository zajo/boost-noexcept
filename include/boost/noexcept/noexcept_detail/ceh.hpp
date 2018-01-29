//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_C95230D44A3311E781E9B0B2AD730A1C
#define UUID_C95230D44A3311E781E9B0B2AD730A1C

#include <boost/noexcept/noexcept_detail/eh.hpp>
#include <boost/noexcept/noexcept_config/thread_local.hpp>

namespace
boost
    {
    namespace
    noexcept_
        {
        namespace
        noexcept_detail
            {
            template <class R,bool IsIntegral=std::is_integral<R>::value> struct default_throw_return;
            template <class R>
            struct
            default_throw_return<R,true>
                {
                static R value() noexcept { return static_cast<R>(-1); }
                };
            template <class R>
            struct
            default_throw_return<R,false>
                {
                static R value() noexcept { return R(); }
                };
            class error;
            class
            current_error_holder
                {
                private:
                current_error_holder( current_error_holder const & )=delete;
                current_error_holder( current_error_holder && )=delete;
                current_error_holder & operator=( current_error_holder const & )=delete;
                current_error_holder & operator=( current_error_holder && )=delete;
                error_storage storage_;
                mover_t * mover_;
                error_base * px_;
                void
                ensure_empty() noexcept
                    {
                    BOOST_NOEXCEPT_ASSERT(empty() && "Unhandled error is present at the time a new error is being set()! Calling std::terminate()!");
                    if( !empty() )
                        std::terminate();
                    }
                public:
                constexpr current_error_holder() noexcept:
                    storage_(),
                    mover_(0),
                    px_(0)
                    {
                    }
                ~current_error_holder() noexcept
                    {
                    BOOST_NOEXCEPT_ASSERT(empty() && "The thread terminates with unhandled error! Calling std::terminate()!");
                    if( !empty() )
                        std::terminate();
                    }
                bool
                empty() const noexcept
                    {
                    return px_==0;
                    }
                //defined in throw.hpp:
                template <class E> void put( E && ) noexcept;
                template <class E> void put_with_location( E &&, char const * file, int line, char const * function ) noexcept;
                //defined in try.hpp:
                error extract() noexcept;
                void set( error && ) noexcept;
                };
            inline
            current_error_holder &
            ceh() noexcept
                {
                BOOST_NOEXCEPT_THREAD_LOCAL(current_error_holder,errh);
                return errh;
                }
            }
        inline
        bool
        has_current_error() noexcept
            {
            return !noexcept_detail::ceh().empty();
            }
        template <class R>
        struct
        throw_return: noexcept_detail::default_throw_return<R>
            {
            };
        template <>
        struct
        throw_return<bool>
            {
            static bool value() noexcept { return false; }
            };
        }
    }

#endif
