//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_5872130C482B11E7B84F4C607F4E887A
#define UUID_5872130C482B11E7B84F4C607F4E887A

#include <boost/noexcept/noexcept_detail/current_exception.hpp>
#include <boost/noexcept/noexcept_result_traits.hpp>

namespace
boost
    {
    template <class T>
    class
    noexcept_handler:
        public noexcept_detail::current_exception_holder::handler
        {
        noexcept_handler( noexcept_handler const & )=delete;
        noexcept_handler & operator=( noexcept_handler const & )=delete;
        T val_;
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
        noexcept_handler( T && val ) noexcept:
            val_(std::move(val)),
            caught_(noexcept_succeeded(val_)?0:&noexcept_detail::current_exception().get_exception()),
            handled_(false)
            {
            if( caught_ )
				noexcept_detail::current_exception().set_handler(this);
            }
        noexcept_handler( noexcept_handler && x ) noexcept:
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
        ~noexcept_handler() noexcept
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
        template <class E>
        E *
        noexcept_catch() noexcept
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
        std::exception *
        noexcept_catch_all() noexcept
            {
            std::exception * e=caught().get();
            BOOST_NOEXCEPT_ASSERT(e!=0);
            handled_=true;
            return e;
            }
        typename noexcept_result_traits<T>::value_type const &
        value() const
            {
            if( noexcept_succeeded(val_) )
                return noexcept_success_value(val_);
            else
                {
                handled_=true;
                caught_->call_observer();
                abort();
                }
            }
        typename noexcept_result_traits<T>::value_type const &
        value()
            {
            if( noexcept_succeeded(val_) )
                return noexcept_success_value(val_);
            else
                {
                handled_=true;
                caught_->call_observer();
                abort();
                }
            }
        bool
        succeeded() const noexcept
            {
            return noexcept_succeeded(val_);
            }
        bool
        failed() const noexcept
            {
			return !noexcept_succeeded(val_);
            }
        explicit operator bool() const noexcept
            {
            return noexcept_succeeded(val_);
            }
        bool
        has_internal_error_() const noexcept
            {
            return caught_==&internal_;
            }
        template <class ErrorCodeType>
        ErrorCodeType const * noexcept_catch_error_code() noexcept;
        };
    template <class T>
    noexcept_handler<T>
    noexcept_try( T && x ) noexcept //Takes any type which has noexcept_result_traits defined.
        {
        return noexcept_handler<T>(std::move(x));
        }
    namespace
    noexcept_detail
        {
        inline
        current_exception_holder::
        handler::
        ~handler() noexcept
            {
            }
        inline
        void
        current_exception_holder::
        set_handler( handler * h ) noexcept
            {
            BOOST_NOEXCEPT_ASSERT(!x_.empty());
            h_=h;
            }
        inline
        void
        current_exception_holder::
        unset_handler( handler * h ) noexcept
            {
            BOOST_NOEXCEPT_ASSERT(h_==0 || h_==h);
            h_=0;
            }
        }
    }

#endif
