//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_3E0F79DC4A2E11E7B4B6E8AAAD730A1C
#define UUID_3E0F79DC4A2E11E7B4B6E8AAAD730A1C

#include <boost/noexcept/noexcept_config/optional.hpp>

namespace
boost
	{
	template <class>
	struct noexcept_result_traits;

	template <class T>
	struct
	noexcept_result_traits<noexcept_config::optional<T> > //boost::optional or std::optional based on BOOST_NOEXCEPT_USE_STD_OPTIONAL
		{
		typedef noexcept_config::optional<T> result_type;
		typedef T value_type;
		static
		bool
		succeeded( result_type const & x ) noexcept
			{
			return bool(x);
			}
		static
		result_type
		error_result() noexcept
			{
			return result_type();
			}
		static
		value_type const &
		success_value( result_type const & x ) noexcept
			{
			return x.value();
			}
		static
		value_type &
		success_value( result_type & x ) noexcept
			{
			return x.value();
			}
		};
	}

#endif
