//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_75B956744A2D11E7AAD921AAAD730A1C
#define UUID_75B956744A2D11E7AAD921AAAD730A1C

#include <boost/noexcept/noexcept_detail/current_exception.hpp>
#include <boost/noexcept/result_traits.hpp>

namespace
boost
    {
	namespace
	noexcept_
		{
		class
		throw_
			{
			throw_( throw_ const & )=delete;
			throw_ & operator=( throw_ const & )=delete;
			public:
			throw_() noexcept
				{
				}
			template <class T>
			throw_( T && e ) noexcept
				{
				noexcept_detail::current_exception().put(std::move(e));
				}
			template <class T>
			operator T() noexcept
				{
				BOOST_NOEXCEPT_ASSERT(!noexcept_detail::current_exception().get_exception().empty());
				return noexcept_error_result<T>();
				}
			};
		}
	}

#endif
