//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_75B956744A2D11E7AAD921AAAD730A1C
#define UUID_75B956744A2D11E7AAD921AAAD730A1C

#include <boost/noexcept/noexcept_detail/current_error.hpp>
#include <boost/current_function.hpp>
#include <type_traits>
#include <exception>

#define BOOST_NOEXCEPT_CHECK { if( ::boost::noexcept_::has_current_error() ) return ::boost::noexcept_::throw_(); }
#define BOOST_NOEXCEPT_CHECK_VOID { if( ::boost::noexcept_::has_current_error() ) return; }
#define THROW_(x) ::boost::noexcept_::throw_((x),__FILE__,__LINE__,BOOST_CURRENT_FUNCTION)

namespace
boost
    {
    namespace
    noexcept_
        {
        namespace
        noexcept_detail
            {
            template <class R,bool IsIntegral=std::is_integral<R>::value> struct default_throw_return;
            template <class R>
            struct
            default_throw_return<R,true>
                {
                static R value() noexcept { return static_cast<R>(-1); }
                };
            template <class R>
            struct
            default_throw_return<R,false>
                {
                static R value() noexcept { return R(); }
                };
            }
        template <class R>
        struct
        throw_return: noexcept_detail::default_throw_return<R>
            {
            };
        template <>
        struct
        throw_return<bool>
            {
            static bool value() noexcept { return false; }
            };
        class
        throw_
            {
            throw_( throw_ const & )=delete;
            throw_ & operator=( throw_ const & )=delete;
            public:
            throw_() noexcept
                {
                noexcept_detail::current_error().throw_();
                }
            template <class E>
            explicit
            throw_( E && e ) noexcept
                {
                noexcept_detail::current_error().put(std::move(e));
                }
            template <class E>
            explicit
            throw_( E && e, char const * file, int line, char const * function ) noexcept
                {
                noexcept_detail::current_error().put_with_location(std::move(e),file,line,function);
                }
            template <class R>
            operator R() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(has_current_error());
                return throw_return<R>::value();
                }
            };
        }
    }

#endif
