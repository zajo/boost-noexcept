//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_5872130C482B11E7B84F4C607F4E887A
#define UUID_5872130C482B11E7B84F4C607F4E887A

#include <boost/noexcept/noexcept_detail/current_exception.hpp>
#include <boost/noexcept/result_traits.hpp>

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class R>
        class
        handler:
            public noexcept_detail::current_exception_holder::handler_base
            {
            handler( handler const & )=delete;
            handler & operator=( handler const & )=delete;
            R val_;
            noexcept_detail::exception_holder internal_;
            noexcept_detail::exception_holder const * caught_;
            bool handled_;
            void
            store_internally( noexcept_detail::exception_holder && x ) noexcept
                {
                BOOST_NOEXCEPT_ASSERT(caught_==&noexcept_detail::current_exception().get_exception());
                BOOST_NOEXCEPT_ASSERT(internal_.empty());
                internal_ = std::move(x);
                caught_ = &internal_;
                }
            noexcept_detail::exception_holder const &
            caught() const noexcept
                {
                BOOST_NOEXCEPT_ASSERT(caught_!=0);
                BOOST_NOEXCEPT_ASSERT(!caught_->empty());
                return *caught_;
                }
            public:
            explicit
            handler( R && val ) noexcept:
                val_(std::move(val)),
                caught_(result_traits<R>::succeeded(val_)?0:&noexcept_detail::current_exception().get_exception()),
                handled_(false)
                {
                if( caught_ )
                    noexcept_detail::current_exception().set_handler(this);
                }
            handler( handler && x ) noexcept:
                val_(std::move(x.val_)),
                caught_(x.caught_),
                handled_(x.handled_)
                {
                x.caught_=0;
                x.handled_=0;
                if( caught_ )
                    {
                    BOOST_NOEXCEPT_ASSERT(x.caught_==&noexcept_detail::current_exception().get_exception());
                    noexcept_detail::current_exception().set_handler(this);
                    }
                }
            ~handler() noexcept
                {
                if( caught_ )
                    {
                    noexcept_detail::current_exception_holder & cf=noexcept_detail::current_exception();
                    if( caught_==&internal_ )
                        {
                        if( !handled_ )
                            {
                            BOOST_NOEXCEPT_ASSERT(!internal_.empty());
                            cf.set_exception(std::move(internal_));
                            }
                        }
                    else
                        {
                        BOOST_NOEXCEPT_ASSERT(caught_==&cf.get_exception());
                        if( handled_ )
                            cf.clear_exception();
                        cf.unset_handler(this);
                        }
                    }
                }
            explicit operator bool() const noexcept
                {
                return result_traits<R>::succeeded(val_);
                }
            typename result_traits<R>::value_type const &
            value() const
                {
                if( result_traits<R>::succeeded(val_) )
                    return result_traits<R>::success_value(val_);
                else
                    {
                    handled_=true;
                    caught_->call_observer();
                    abort();
                    }
                }
            typename result_traits<R>::value_type &
            value()
                {
                if( result_traits<R>::succeeded(val_) )
                    return result_traits<R>::success_value(val_);
                else
                    {
                    handled_=true;
                    caught_->call_observer();
                    abort();
                    }
                }
            template <class E=std::exception>
            E *
            catch_() noexcept
                {
                std::exception * f=caught().get();
                BOOST_NOEXCEPT_ASSERT(f!=0);
                if( E * e=dynamic_cast<E *>(f) )
                    {
                    handled_=true;
                    return e;
                    }
                return 0;
                }
            bool
            has_internal_error_() const noexcept
                {
                return caught_==&internal_;
                }
            };
        template <class R>
        handler<R>
        try_( R && x ) noexcept //Takes any type for which the result_traits template is specialized
            {
            return handler<R>(std::move(x));
            }
        namespace
        noexcept_detail
            {
            inline
            current_exception_holder::
            handler_base::
            ~handler_base() noexcept
                {
                }
            inline
            void
            current_exception_holder::
            set_handler( handler_base * h ) noexcept
                {
                BOOST_NOEXCEPT_ASSERT(!e_.empty());
                h_=h;
                }
            inline
            void
            current_exception_holder::
            unset_handler( handler_base * h ) noexcept
                {
                BOOST_NOEXCEPT_ASSERT(h_==0 || h_==h);
                h_=0;
                }
            }
        }
    }

#endif
