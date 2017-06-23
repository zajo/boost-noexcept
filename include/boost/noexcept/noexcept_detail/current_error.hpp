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
            new_nothrow_move( T && x )
                {
                return new (std::nothrow) T(std::move(x));
                }
            class
            handler_base
                {
                public:
                virtual void store_internally( error && ) noexcept=0;
                virtual void unhandle() noexcept=0;
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
                    if( h_ )
                        {
                        h_->store_internally(std::move(e_));
                        h_=0;
                        }
                    else
                        {
                        BOOST_NOEXCEPT_ASSERT(e_.empty() && "Unhandled error is present at the time a new error is being set()! Calling std::terminate()!");
                        if( !e_.empty() )
                            std::terminate();
                        }
                    BOOST_NOEXCEPT_ASSERT(e_.empty());
                    }
                public:
                current_error_holder() noexcept:
                    h_(0)
                    {
                    }
                ~current_error_holder() noexcept
                    {
                    BOOST_NOEXCEPT_ASSERT(e_.empty() && "The thread terminates with unhandled error! Calling std::terminate()!");
                    if( !e_.empty() )
                        std::terminate();
                    }
                template <class E>
                void
                put( E && e ) noexcept
                    {
                    ensure_empty();
                    e_.put(std::move(e));
                    }
                template <class E>
                void
                put_with_location( E && e, char const * file, int line, char const * function ) noexcept
                    {
                    ensure_empty();
                    e_.put_with_location(std::move(e),file,line,function);
                    }
                void
                set( error && e ) noexcept
                    {
                    ensure_empty();
                    e_=std::move(e);
                    }
                void
                throw_() noexcept
                    {
                    if( !has_error() )
                        {
                        BOOST_NOEXCEPT_ASSERT(h_!=0 && "throw_() called when !has_current_error()!");
                        h_->unhandle();
                        }
                    }
                error
                extract() noexcept
                    {
                    BOOST_NOEXCEPT_ASSERT(has_error());
                    BOOST_NOEXCEPT_ASSERT(!h_);
                    return error(std::move(e_));
                    }
                bool
                has_error() const noexcept
                    {
                    return  !e_.empty() && !h_;
                    }
                error * set_handler( handler_base * ) noexcept;
                void unset_handler( error *, bool ) noexcept;
                private:
                error e_;
                handler_base * h_;
                };
            current_error_holder &
            current_error() noexcept
                {
                return get_tl_object<current_error_holder>();
                }
            current_error_holder *
            get_current_error() noexcept
                {
                current_error_holder & eh=current_error();
                return eh.has_error()?&eh:0;
                }
            }
        inline
        bool
        has_current_error() noexcept
            {
            return noexcept_detail::current_error().has_error();
            }
        }
    }

#endif
