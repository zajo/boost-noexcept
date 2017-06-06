//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_75B956744A2D11E7AAD921AAAD730A1C
#define UUID_75B956744A2D11E7AAD921AAAD730A1C

#include <boost/noexcept/noexcept_detail/current_exception.hpp>
#include <boost/noexcept/noexcept_result_traits.hpp>

namespace
boost
    {
    class
    propagate
        {
        propagate( propagate const & )=delete;
        propagate & operator=( propagate const & )=delete;
        public:
        propagate() noexcept
            {
            }
        template <class T>
        propagate( T && e ) noexcept
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

#endif
