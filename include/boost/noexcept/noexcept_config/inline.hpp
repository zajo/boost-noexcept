//Copyright (c) 2017-2018 Emil Dotchevski and BOOST_NOEXCEPT Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NOEXCEPT_INLINE_FORCEINLINE
#	if defined(_MSC_VER)
#		define BOOST_NOEXCEPT_INLINE_FORCEINLINE __forceinline
#	elif (defined(__GNUC__) && __GNUC__>3) || defined(__SNC__)
#		define BOOST_NOEXCEPT_INLINE_FORCEINLINE inline __attribute__ ((always_inline))
#	else
#		define BOOST_NOEXCEPT_INLINE_FORCEINLINE inline
#	endif
#endif

#ifndef BOOST_NOEXCEPT_INLINE_NOINLINE
#	if defined(_MSC_VER)
#		define BOOST_NOEXCEPT_INLINE_NOINLINE __declspec(noinline)
#	elif (defined(__GNUC__) && __GNUC__>3) || defined(__SNC__)
#		define BOOST_NOEXCEPT_INLINE_NOINLINE inline __attribute__ ((noinline))
#	else
#		define BOOST_NOEXCEPT_INLINE_NOINLINE inline
#	endif
#endif

#ifndef BOOST_NOEXCEPT_INLINE
#define BOOST_NOEXCEPT_INLINE inline
#endif

#ifndef BOOST_NOEXCEPT_INLINE_TRIVIAL
#define BOOST_NOEXCEPT_INLINE_TRIVIAL BOOST_NOEXCEPT_FORCEINLINE
#endif

#ifndef BOOST_NOEXCEPT_INLINE_CRITICAL
#define BOOST_NOEXCEPT_INLINE_CRITICAL BOOST_NOEXCEPT_FORCEINLINE
#endif

#ifndef BOOST_NOEXCEPT_INLINE_OPERATIONS
#define BOOST_NOEXCEPT_INLINE_OPERATIONS BOOST_NOEXCEPT_INLINE
#endif

#ifndef BOOST_NOEXCEPT_INLINE_RECURSION
#define BOOST_NOEXCEPT_INLINE_RECURSION BOOST_NOEXCEPT_INLINE_OPERATIONS
#endif
