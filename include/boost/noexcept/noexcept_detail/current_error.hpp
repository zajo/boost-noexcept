//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_C95230D44A3311E781E9B0B2AD730A1C
#define UUID_C95230D44A3311E781E9B0B2AD730A1C

#include <boost/noexcept/noexcept_detail/any_movable.hpp>
#include <boost/noexcept/noexcept_config/throw_exception.hpp>
#include <boost/noexcept/noexcept_config/thread_local.hpp>
#include <exception>

namespace
boost
    {
    namespace
    noexcept_
        {
        namespace
        noexcept_detail
            {
            template <class E>
            void
            throw_exception_( std::exception * e )
                {
                BOOST_NOEXCEPT_ASSERT(e!=0);
                BOOST_THROW_EXCEPTION(*static_cast<E *>(e));
                std::terminate();
                }
            typedef any_movable<128,std::exception> exception_holder;
            class
            current_error_holder
                {
                public:
                class
                handler_base
                    {
                    public:
                    virtual void store_internally( exception_holder && ) noexcept=0;
                    virtual void unhandle() noexcept=0;
                    protected:
                    ~handler_base() noexcept;
                    };
                ~current_error_holder() noexcept
                    {
                    BOOST_NOEXCEPT_ASSERT(e_.empty() && "The thread terminates with unhandled error! Calling std::terminate()! (Did you forget to use try_?)");
                    if( !e_.empty() )
                        std::terminate();
                    }
                template <class E>
                void
                put( E && e ) noexcept
                    {
                    if( h_ )
                        {
                        h_->store_internally(std::move(e_));
                        h_=0;
                        }
                    BOOST_NOEXCEPT_ASSERT(e_.empty() && "Unhandled error is present at the time a new error is passed to throw_()! (Did you forget to use try_?)");
                    e_.put(std::move(e),&throw_exception_<E>);
                    }
                void
                rethrow() noexcept
                    {
                    if( !has_current_error() )
                        {
                        BOOST_NOEXCEPT_ASSERT(h_!=0);
                        h_->unhandle();
                        }
                    }
                exception_holder const &
                get_exception() noexcept
                    {
                    return e_;
                    }
                void
                set_exception( exception_holder && e ) noexcept
                    {
                    BOOST_NOEXCEPT_ASSERT(e_.empty() && "Unhandled error is present at the time a new error is passed to throw_()! (Did you forget to use try_?)");
                    e_=std::move(e);
                    }
                void
                clear_exception() noexcept
                    {
                    e_.clear();
                    }
                bool
                has_current_error() const noexcept
                    {
                    return  !e_.empty() && !h_;
                    }
                void set_handler( handler_base * ) noexcept;
                void unset_handler( handler_base * ) noexcept;
                private:
                exception_holder e_;
                handler_base * h_;
                };
            current_error_holder &
            current_error() noexcept
                {
                return get_tl_object<current_error_holder>();
                }
            }
        }
    }

#endif
