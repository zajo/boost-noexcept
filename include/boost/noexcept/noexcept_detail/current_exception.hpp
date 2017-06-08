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
			typedef any_movable<128,std::exception> exception_holder;
			class
			current_exception_holder
				{
				template <class T>
				static
				void
				throw_exception_( std::exception * x )
					{
					BOOST_NOEXCEPT_ASSERT(x!=0);
					BOOST_THROW_EXCEPTION(*static_cast<T *>(x));
					abort();
					}
				public:
				class
				handler_base
					{
					public:
					virtual void store_internally( exception_holder && ) noexcept=0;
					protected:
					~handler_base() noexcept;
					};
				~current_exception_holder() noexcept
					{
					BOOST_NOEXCEPT_ASSERT(x_.empty() && "The thread terminates with unhandled error! Calling abort()! (Did you forget to use try_?)");
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
					BOOST_NOEXCEPT_ASSERT(x_.empty() && "Unhandled error is present at the time a new error is passed to throw_()! (Did you forget to use try_?)");
					x_.put(std::move(obj),&throw_exception_<T>);
					}
				exception_holder const &
				get_exception() noexcept
					{
					return x_;
					}
				void
				set_exception( exception_holder && x ) noexcept
					{
					BOOST_NOEXCEPT_ASSERT(x_.empty() && "Unhandled error is present at the time a new error is passed to throw_()! (Did you forget to use try_?)");
					x_=std::move(x);
					}
				void
				clear_exception() noexcept
					{
					x_.clear();
					}
				void set_handler( handler_base * ) noexcept;
				void unset_handler( handler_base * ) noexcept;
				private:
				exception_holder x_;
				handler_base * h_;
				};
			current_exception_holder &
			current_exception() noexcept
				{
				return get_tl_object<current_exception_holder>();
				}
			}
		}
	}

#endif
