//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_362A73E84A4211E7935355C4AD730A1C
#define UUID_362A73E84A4211E7935355C4AD730A1C

namespace
boost
	{
	template <class>
	struct noexcept_result_traits;

	template <class T>
	struct
	noexcept_result_traits<T *>
		{
		typedef T * result_type;
		typedef T * value_type;
		static
		bool
		succeeded( result_type x ) noexcept
			{
			return bool(x);
			}
		static
		result_type
		error_result() noexcept
			{
			return 0;
			}
		static
		value_type const &
		success_value( result_type const & x ) noexcept
			{
			return x;
			}
		static
		value_type &
		success_value( result_type & x ) noexcept
			{
			return x;
			}
		};
	}

#endif
