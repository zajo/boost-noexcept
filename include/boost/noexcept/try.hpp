//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_5872130C482B11E7B84F4C607F4E887A
#define UUID_5872130C482B11E7B84F4C607F4E887A

#include <boost/noexcept/noexcept_detail/current_error.hpp>

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class> class handler;
        handler<void> void_try_() noexcept;
        template <>
        class
        handler<void>:
            public noexcept_detail::handler_base
            {
            friend handler<void> void_try_() noexcept;
            handler( handler const & )=delete;
            handler & operator=( handler const & )=delete;
            noexcept_detail::error internal_;
            noexcept_detail::error * caught_;
            bool handled_;
            void
            store_internally( noexcept_detail::error && x ) noexcept
                {
                BOOST_NOEXCEPT_ASSERT(caught_!=&internal_);
                BOOST_NOEXCEPT_ASSERT(internal_.empty());
                internal_ = std::move(x);
                caught_ = &internal_;
                }
            void
            unhandle() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(has_error());
                handled_=false;
                noexcept_detail::current_error().unset_handler(caught_,handled_);
                }
            protected:
            handler() noexcept:
                caught_(noexcept_detail::current_error().set_handler(this)),
                handled_(false)
                {
                }
            public:
            handler( handler && x ) noexcept:
                caught_(noexcept_detail::current_error().set_handler(this)),
                handled_(false)
                {
                x.caught_=0;
                }
            ~handler() noexcept
                {
                noexcept_detail::current_error().unset_handler(caught_,handled_);
                }
            explicit operator bool() const noexcept
                {
                return !has_error();
                }
            bool
            has_error() const noexcept
                {
                return caught_!=0;
                }
            bool
            has_unhandled_error() const noexcept
                {
                return has_error() && !handled_;
                }
            bool
            has_internal_error_() const noexcept
                {
                return caught_==&internal_;
                }
            template <class E=std::exception>
            E *
            catch_() noexcept
                {
                if( caught_ )
                    if( E * e=caught_->get<E>() )
                        {
                        handled_=true;
                        return e;
                        }
                return 0;
                }
            BOOST_NOEXCEPT_NORETURN
            void
            throw_exception()
                {
                BOOST_NOEXCEPT_ASSERT(has_error());
                handled_=true;
                caught_->throw_exception();
                }
            };
        template <class T>
        class
        handler:
            public handler<void>
            {
            handler( handler const & )=delete;
            handler & operator=( handler const & )=delete;
            T res_;
            public:
            explicit
            handler( T && res ) noexcept:
                res_(std::move(res))
                {
                }
            handler( handler && x ) noexcept:
                handler<void>(std::move(x)),
                res_(std::move(x.res_))
                {
                }
            T const &
            get() const
                {
                if( has_error() )
                    throw_exception();
                else
                    return res_;
                }
            T &
            get()
                {
                if( has_error() )
                    throw_exception();
                else
                    return res_;
                }
            };
        template <class T>
        handler<T>
        try_( T && x ) noexcept
            {
            return handler<T>(std::move(x));
            }
        inline
        handler<void>
        void_try_() noexcept
            {
            return handler<void>();
            }
        namespace
        noexcept_detail
            {
            inline
            handler_base::
            ~handler_base() noexcept
                {
                }
            inline
            error *
            current_error_holder::
            set_handler( handler_base * h ) noexcept
                {
                if( e_.empty() )
                    return 0;
                else
                    {
                    h_=h;
                    return &e_;
                    }
                }
            inline
            void
            current_error_holder::
            unset_handler( error * caught, bool handled ) noexcept
                {
                h_=0;
                if( caught==&e_ )
                    {
                    if( handled )
                        e_.clear();
                    }
                else if( caught && !handled )
                    set(std::move(*caught));
                }
            }
        }
    }

#endif
