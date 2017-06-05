//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_5872130C482B11E7B84F4C607F4E887A
#define UUID_5872130C482B11E7B84F4C607F4E887A

#include <boost/noexcept/fallible.hpp>

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
		noexcept_detail::optional<T> opt_;
		noexcept_detail::exception_holder internal_;
		noexcept_detail::exception_holder * caught_;
		bool handled_;
		void
		store_internally() noexcept
			{
			BOOST_NOEXCEPT_ASSERT(caught_==&noexcept_detail::current_exception());
			BOOST_NOEXCEPT_ASSERT(internal_.empty());
			internal_ = std::move(*caught_);
			caught_ = &internal_;
			}
		noexcept_detail::exception_holder &
		caught() const noexcept
			{
			BOOST_NOEXCEPT_ASSERT(caught_!=0);
			BOOST_NOEXCEPT_ASSERT(!caught_->empty());
			return *caught_;
			}
		public:
		explicit
		noexcept_handler( noexcept_detail::optional<T> && opt ) noexcept:
			opt_(std::move(opt)),
			caught_(opt?0:&noexcept_detail::current_exception()),
			handled_(false)
			{
			if( caught_ )
				static_cast<noexcept_detail::current_exception_holder *>(caught_)->set_handler(this);
			}
		noexcept_handler( noexcept_handler && x ) noexcept:
			opt_(std::move(x.opt_)),
			caught_(x.caught_),
			handled_(x.handled_)
			{
			x.caught_=0;
			x.handled_=0;
			if( caught_ )
				{
				BOOST_NOEXCEPT_ASSERT(x.caught_==&noexcept_detail::current_exception());
				static_cast<noexcept_detail::current_exception_holder *>(caught_)->set_handler(this);
				}
			}
		~noexcept_handler() noexcept
			{
			if( caught_ )
				{
				if( handled_ )
					caught_->clear();
				noexcept_detail::current_exception_holder & cf=noexcept_detail::current_exception();
				if( caught_==&internal_ )
					{
					if( !handled_ )
						{
						BOOST_NOEXCEPT_ASSERT(cf.empty());
						BOOST_NOEXCEPT_ASSERT(!internal_.empty());
						static_cast<noexcept_detail::exception_holder &>(cf) = std::move(internal_);
						}
					}
				else
					{
					BOOST_NOEXCEPT_ASSERT(caught_==&cf);
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
		T const &
		value() const
			{
			if( succeeded() )
				return opt_.value();
			else
				{
				handled_=true;
				caught_->throw_exception();
				abort();
				}
			}
		T &
		value()
			{
			if( succeeded() )
				return opt_.value();
			else
				{
				handled_=true;
				caught_->throw_exception();
				abort();
				}
			}
		bool
		succeeded() const noexcept
			{
			return bool(opt_);
			}
		bool
		failed() const noexcept
			{
			return !opt_;
			}
		explicit operator bool() const noexcept
			{
			return bool(opt_);
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
	noexcept_try( fallible<T> && x ) noexcept
		{
		return noexcept_handler<T>(std::move(x.opt_));
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
			BOOST_NOEXCEPT_ASSERT(!empty());
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
