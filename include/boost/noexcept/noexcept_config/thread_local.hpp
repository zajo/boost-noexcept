//Copyright (c) 2017-2018 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_EB80EE1449A411E7879E1EF67F4E887A
#define UUID_EB80EE1449A411E7879E1EF67F4E887A

#ifndef BOOST_NOEXCEPT_NO_THREADS
#   include <boost/config.hpp>
#   ifdef BOOST_NO_THREADS
#       define BOOST_NOEXCEPT_NO_THREADS
#   endif
#endif

#ifdef BOOST_NOEXCEPT_NO_THREADS
#define BOOST_NOEXCEPT_THREAD_LOCAL_
#else
#define BOOST_NOEXCEPT_THREAD_LOCAL_ thread_local
#endif

#ifndef BOOST_NOEXCEPT_THREAD_LOCAL
#define BOOST_NOEXCEPT_THREAD_LOCAL(type,object) static BOOST_NOEXCEPT_THREAD_LOCAL_ type object
#endif

#endif
