//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_EB80EE1449A411E7879E1EF67F4E887A
#define UUID_EB80EE1449A411E7879E1EF67F4E887A

#ifdef BOOST_NOEXCEPT_USE_BOOST_TSS
#   include <boost/config.hpp>
#   ifdef BOOST_NO_THREADS
#       define BOOST_NOEXCEPT_NO_THREADS
#   else
#       include <boost/thread/tss.hpp>
#   endif
#endif

namespace
boost
    {
    namespace
    noexcept_
        {
        namespace
        noexcept_detail
            {
            template <class T>
            T &
            get_tl_object()
                {
#if defined(BOOST_NOEXCEPT_NO_THREADS)
                static T x;
                return x;
#elif defined(BOOST_NOEXCEPT_USE_BOOST_TSS)
                static boost::thread_specific_ptr<T> x;
                if( T * p=x.get() )
                    return *p;
                else
                    {
                    x.reset(new T());
                    return *x;;
                    }
#else
                static thread_local T x;
                return x;
#endif
                }
            }
        }
    }

#endif
