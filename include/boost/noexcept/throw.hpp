//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_75B956744A2D11E7AAD921AAAD730A1C
#define UUID_75B956744A2D11E7AAD921AAAD730A1C

#include <boost/noexcept/noexcept_detail/current_exception.hpp>
#include <boost/noexcept/result_traits.hpp>
#include <type_traits>
#include <exception>

namespace
boost
    {
    namespace
    noexcept_
        {
        namespace
        noexcept_detail
            {
            template <class E,bool DerivesFromStdException=std::is_base_of<std::exception,E>::value> struct put_dispatch;
            template <class E>
            struct
            put_dispatch<E,true>
                {
                static
                void
                put_( E && e ) noexcept
                    {
                    noexcept_detail::current_exception().put(std::move(e));
                    }
                };
            template <class E>
            struct
            put_dispatch<E,false>
                {
                struct
                injector:
                    E,
                    std::exception
                    {
                    explicit
                    injector( E && x ) noexcept:
                        E(std::move(x))
                        {
                        }
                    ~injector() noexcept
                        {
                        }
                    };
                static
                void
                put_( E && e ) noexcept
                    {
                    noexcept_detail::current_exception().put(injector(std::move(e)));
                    }
                };
            }
        class
        throw_
            {
            throw_( throw_ const & )=delete;
            throw_ & operator=( throw_ const & )=delete;
            public:
            throw_() noexcept
                {
                }
            template <class E>
            throw_( E && e ) noexcept
                {
                noexcept_detail::put_dispatch<E>::put_(std::move(e));
                }
            template <class R>
            operator R() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(!noexcept_detail::current_exception().get_exception().empty());
                return result_traits<R>::error_result();
                }
            };
        }
    }

#endif
