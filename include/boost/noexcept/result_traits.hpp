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
		succeeded_( T const & x )
			{
			return result_traits<T>::succeeded(x);
			}
        }
    }

#endif
