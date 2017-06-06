//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_C95230D44A3311E781E9B0B2AD730A1C
#define UUID_C95230D44A3311E781E9B0B2AD730A1C

#include <boost/noexcept/noexcept_detail/exception_holder.hpp>
#include <boost/noexcept/noexcept_config/thread_local.hpp>

namespace
boost
    {
    namespace
    noexcept_detail
        {
        class
        current_exception_holder
            {
            public:
            class
            handler
                {
                public:
                virtual void store_internally( exception_holder && ) noexcept=0;
                protected:
                ~handler() noexcept;
                };
            ~current_exception_holder() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(x_.empty() && "The thread terminates with unhandled error! Calling abort()! (Did you forget to use noexcept_try?)");
                if( !x_.empty() )
                    abort();
                }
            template <class T>
            void
            put( T && obj ) noexcept
                {
                if( h_ )
                    {
                    h_->store_internally(std::move(x_));
                    h_=0;
                    }
                BOOST_NOEXCEPT_ASSERT(x_.empty() && "Unhandled error is present at the time a new error is passed to propagate()! (Did you forget to use noexcept_try?)");
                x_.put(std::move(obj));
                }
			exception_holder const &
			get_exception() noexcept
				{
				return x_;
				}
			void
			set_exception( exception_holder && x ) noexcept
				{
                BOOST_NOEXCEPT_ASSERT(x_.empty() && "Unhandled error is present at the time a new error is passed to propagate()! (Did you forget to use noexcept_try?)");
				x_=std::move(x);
				}
			void
			clear_exception() noexcept
				{
				x_.clear();
				}
            void set_handler( handler * ) noexcept;
            void unset_handler( handler * ) noexcept;
            private:
			exception_holder x_;
            handler * h_;
            };
        current_exception_holder &
        current_exception() noexcept
            {
            return get_tl_object<current_exception_holder>();
            }
        }
	}

#endif
