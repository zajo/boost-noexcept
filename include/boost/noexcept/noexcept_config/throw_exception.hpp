//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_FB56599248D611E78192CFCF7E4E887A
#define UUID_FB56599248D611E78192CFCF7E4E887A

#ifndef BOOST_NOEXCEPT_THROW_EXCEPTION
#include <boost/throw_exception.hpp>
#define BOOST_NOEXCEPT_THROW_EXCEPTION ::boost::throw_exception
#endif

#if !defined(BOOST_NOEXCEPT_NORETURN)
#  if defined(_MSC_VER)
#    define BOOST_NOEXCEPT_NORETURN __declspec(noreturn)
#  elif defined(__GNUC__)
#    define BOOST_NOEXCEPT_NORETURN __attribute__ ((__noreturn__))
#  elif defined(__has_attribute) && defined(__SUNPRO_CC)
#    if __has_attribute(noreturn)
#      define BOOST_NOEXCEPT_NORETURN [[noreturn]]
#    endif
#  elif defined(__has_cpp_attribute) 
#    if __has_cpp_attribute(noreturn)
#      define BOOST_NOEXCEPT_NORETURN [[noreturn]]
#    endif
#  endif
#endif

#if !defined(BOOST_NOEXCEPT_NORETURN)
#  define BOOST_NOEXCEPT_NORETURN
#endif

#endif
