//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_B3D6DCC24E6C11E78C206EE3AD730A1C
#define UUID_B3D6DCC24E6C11E78C206EE3AD730A1C

#include <boost/noexcept/noexcept_detail/current_error.hpp>

namespace
boost
    {
    namespace
    noexcept_
        {
        class
        error_handler:
            public noexcept_detail::current_error_holder::handler_base
            {
            error_handler( error_handler const & )=delete;
            error_handler & operator=( error_handler const & )=delete;
            noexcept_detail::exception_holder internal_;
            noexcept_detail::exception_holder const * caught_;
            bool handled_;
            static
            noexcept_detail::exception_holder const *
            init_caught() noexcept
                {
                noexcept_detail::current_error_holder & err=noexcept_detail::current_error();
                return err.has_current_error()?&err.get_exception():0;
                }
            void
            store_internally( noexcept_detail::exception_holder && x ) noexcept
                {
                BOOST_NOEXCEPT_ASSERT(caught_==&noexcept_detail::current_error().get_exception());
                BOOST_NOEXCEPT_ASSERT(internal_.empty());
                internal_ = std::move(x);
                caught_ = &internal_;
                }
            protected:
            error_handler( error_handler && x ) noexcept:
                caught_(x.caught_),
                handled_(x.handled_)
                {
                x.caught_=0;
                x.handled_=0;
                if( caught_ )
                    {
                    BOOST_NOEXCEPT_ASSERT(x.caught_==&noexcept_detail::current_error().get_exception());
                    noexcept_detail::current_error().set_handler(this);
                    }
                }
            public:
            error_handler() noexcept:
                caught_(init_caught()),
                handled_(false)
                {
                if( caught_ )
                    noexcept_detail::current_error().set_handler(this);
                }
            ~error_handler() noexcept
                {
                if( caught_ )
                    {
                    noexcept_detail::current_error_holder & cf=noexcept_detail::current_error();
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
                    {
                    std::exception  * f=caught_->get();
                    BOOST_NOEXCEPT_ASSERT(f!=0);
                    if( E * e=dynamic_cast<E *>(f)  )
                        {
                        handled_=true;
                        return e;
                        }
                    }
                return 0;
                }
            void
            throw_exception()
                {
                if( has_error() )
                    {
                    handled_=true;
                    caught_->call_observer();
                    std::terminate();
                    }
                }
            };
        namespace
        noexcept_detail
            {
            inline
            current_error_holder::
            handler_base::
            ~handler_base() noexcept
                {
                }
            inline
            void
            current_error_holder::
            set_handler( handler_base * h ) noexcept
                {
                BOOST_NOEXCEPT_ASSERT(!e_.empty());
                h_=h;
                }
            inline
            void
            current_error_holder::
            unset_handler( handler_base * h ) noexcept
                {
                BOOST_NOEXCEPT_ASSERT(h_==0 || h_==h);
                h_=0;
                }
            }
        }
    }

#endif
