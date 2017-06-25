//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_C95230D44A3311E781E9B0B2AD730A1C
#define UUID_C95230D44A3311E781E9B0B2AD730A1C

#include <boost/noexcept/noexcept_detail/error.hpp>
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
            template <class T>
            T *
            new_nothrow_move( T && x ) noexcept
                {
                return new (std::nothrow) T(std::move(x));
                }
            class
            handler_base
                {
                public:
                virtual void unhandle() const noexcept=0;
                protected:
                ~handler_base() noexcept;
                };
            class
            current_error_holder
                {
                current_error_holder( current_error_holder const & )=delete;
                current_error_holder & operator=( current_error_holder const & )=delete;
                void
                ensure_empty() noexcept
                    {
                    BOOST_NOEXCEPT_ASSERT(e_.empty() && "Unhandled error is present at the time a new error is being set()! Calling std::terminate()!");
                    if( !e_.empty() )
                        std::terminate();
                    BOOST_NOEXCEPT_ASSERT(e_.empty());
                    }
                public:
                current_error_holder() noexcept:
                    current_handler_(0)
                    {
                    }
                ~current_error_holder() noexcept
                    {
                    BOOST_NOEXCEPT_ASSERT(e_.empty() && "The thread terminates with unhandled error! Calling std::terminate()!");
                    if( !e_.empty() )
                        std::terminate();
                    }
                bool
                has_error() const noexcept
                    {
                    return  !e_.empty();
                    }
                //defined in throw.hpp:
                template <class E> void put( E && ) noexcept;
                template <class E> void put_with_location( E &&, char const * file, int line, char const * function ) noexcept;
                void throw_() noexcept;
                //defined in try.hpp:
                error extract() noexcept;
                void set( error && ) noexcept;
                void set_current_handler( handler_base const * ) noexcept;
                private:
                error e_;
                handler_base const * current_handler_;
                };
            current_error_holder &
            ceh() noexcept
                {
                return get_tl_object<current_error_holder>();
                }
            }
        inline
        bool
        has_current_error() noexcept
            {
            return noexcept_detail::ceh().has_error();
            }
        }
    }

#endif
