//Copyright (c) 2017-2018 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_75B956744A2D11E7AAD921AAAD730A1C
#define UUID_75B956744A2D11E7AAD921AAAD730A1C

#include <boost/noexcept/noexcept_detail/ceh.hpp>
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
        class
        throw_
            {
            throw_( throw_ const & )=delete;
            throw_ & operator=( throw_ const & )=delete;
            public:
            template <class E>
            explicit
            throw_( E && e ) noexcept
                {
                noexcept_detail::ceh().put(std::move(e));
                }
            template <class E>
            explicit
            throw_( E && e, char const * file, int line, char const * function ) noexcept
                {
                noexcept_detail::ceh().put_with_location(std::move(e),file,line,function);
                }
            throw_() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(has_current_error());
                }
            template <class R>
            operator R() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(has_current_error());
                return throw_return<R>::value();
                }
            };
        namespace
        noexcept_detail
            {
            template <class E>
            void
            current_error_holder::
            put( E && e ) noexcept
                {
                ensure_empty();
                px_ = init_error(std::move(e),mover_,&storage_);
                }
            template <class E>
            void
            current_error_holder::
            put_with_location( E && e, char const * file, int line, char const * function ) noexcept
                {
                ensure_empty();
                auto w=init_error(std::move(e),mover_,&storage_);
                px_=w;
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                using namespace ::boost::exception_detail;
                set_info(*w,throw_file(file));
                set_info(*w,throw_line(line));
                set_info(*w,throw_function(function));
#endif
                }
            }
        }
    }

#endif
