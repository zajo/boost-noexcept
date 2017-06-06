//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_EBF884E84A3411E7AE414CB4AD730A1C
#define UUID_EBF884E84A3411E7AE414CB4AD730A1C

namespace
boost
	{
	namespace
	noexcept_
		{
		template <class T>
		struct result_traits;

		template <class T>
		bool
		noexcept_succeeded( T const & x ) noexcept
			{
			return result_traits<T>::succeeded(x);
			}
		template <class T>
		T
		noexcept_error_result() noexcept
			{
			return result_traits<T>::error_result();
			}
		template <class T>
		typename result_traits<T>::value_type const &
		noexcept_success_value( T const & x ) noexcept
			{
			BOOST_NOEXCEPT_ASSERT(noexcept_succeeded(x));
			return result_traits<T>::success_value(x);
			}
		template <class T>
		typename result_traits<T>::value_type &
		noexcept_success_value( T & x ) noexcept
			{
			BOOST_NOEXCEPT_ASSERT(noexcept_succeeded(x));
			return result_traits<T>::success_value(x);
			}
		}
	}

#endif
