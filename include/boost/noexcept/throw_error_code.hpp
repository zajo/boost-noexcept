//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_394C40FA48D611E783AC84CE7E4E887A
#define UUID_394C40FA48D611E783AC84CE7E4E887A

#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/try.hpp>

namespace
boost
    {
	namespace
	noexcept_
		{
		template <class Domain>
		class
		throw_error_code:
			public throw_
			{
			throw_error_code( throw_error_code const & )=delete;
			throw_error_code & operator=( throw_error_code const & )=delete;
			public:
			typedef typename Domain::error_code_type error_code_type;
			class
			wrapper:
				public std::exception
				{
				public:
				error_code_type const err;
				explicit
				wrapper( error_code_type err ):
					err(err)
					{
					}
				};
			throw_error_code( error_code_type err )
				{
				BOOST_NOEXCEPT_ASSERT(noexcept_detail::current_exception().get_exception().empty());
				noexcept_detail::current_exception().put(wrapper(std::move(err)));
				}
			};
		template <class Domain,class T>
		typename Domain::error_code_type const *
		catch_error_code( handler<T> & tr ) noexcept
			{
			if( auto * x=tr.template catch_<typename throw_error_code<Domain>::wrapper>() )
				return &x->err;
			else
				return 0;
			}
		}
	}

#endif
