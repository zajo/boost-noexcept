//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_3599B7FE53DE11E7ACF42CD73E672F2F
#define UUID_3599B7FE53DE11E7ACF42CD73E672F2F

#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/try.hpp>

namespace
boost
    {
    namespace
    noexcept_
        {
        namespace
        noexcept_detail
            {
            template <int A, int B,bool AorB=(A>B)> struct mx;
            template <int A, int B> struct mx<A,B,true> { enum enum_ { value=A }; };
            template <int A, int B> struct mx<A,B,false> { enum enum_ { value=B }; };
            }
        template <class> class result;
        template <class T> result<T> make_result( T && ) noexcept;
        template <class T>
        class
        result
            {
            protected:
            typedef boost::noexcept_::noexcept_detail::error error;
            private:
            result( result const & )=delete;
            result & operator=( result const & )=delete;
            friend result<T> make_result<T>( T && ) noexcept;
            typename std::aligned_storage<
                noexcept_detail::mx<sizeof(T),sizeof(error)>::value,
                noexcept_detail::mx<alignof(T),alignof(error)>::value>::type buf_;
            enum
            state_type
                {
                st_value,
                st_unhandled_error,
                st_error
                };
            mutable state_type state_;
            T &
            as_value() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(state_==st_value);
                return *reinterpret_cast<T *>(&buf_);
                }
            error &
            as_error() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(state_!=st_value);
                return *reinterpret_cast<error *>(&buf_);
                }
            protected:
            result( T && v ) noexcept:
                state_(st_value)
                {
                (void) new (&buf_) T(std::move(v));
                }
            result( error && e ) noexcept:
                state_(st_unhandled_error)
                {
                (void) new (&buf_) error(std::move(e));
                }
            public:
            result( result && r ) noexcept:
                state_(r.state_)
                {
                if( state_==st_value )
                    (void) new (&buf_) T(std::move(r.as_value()));
                else
                    {
                    (void) new (&buf_) error(std::move(r.as_error()));
                    r.state_=st_error;
                    }
                }
            ~result() noexcept
                {
                if( state_==st_value )
                    as_value().~T();
                else
                    {
                    as_error().~error();
                    BOOST_NOEXCEPT_ASSERT(state_!=st_unhandled_error && "Destroying a result<> object which contains an unhandled error! Calling std::terminate()!");
                    if( state_==st_unhandled_error )
                        std::terminate();
                    }
                }
            T
            check() noexcept
                {
                if( state_==st_value )
                    return std::move(as_value());
                else
                    {
                    noexcept_detail::current_error().set(std::move(as_error()));
                    state_=st_error;
                    return throw_return<T>::value();
                    }
                }
            };
        result<void> make_void_result() noexcept;
        result<void> make_result( throw_ && ) noexcept;
        template <>
        class
        result<void>:
            result<bool>
            {
            typedef result<bool> base;
            friend result<void> make_void_result() noexcept;
            friend result<void> make_result( throw_ && ) noexcept;
            result() noexcept:
                base(true)
                {
                }
            result( error && e ) noexcept:
                base(std::move(e))
                {
                }
            public:
            result( result && x ) noexcept:
                base(std::move(x))
                {
                }
            using base::check;
            };
        template <class T>
        result<T>
        make_result( T && x ) noexcept
            {
            if( auto err=noexcept_detail::get_current_error() )
                return result<T>(err->extract());
            else
                return result<T>(std::move(x));
            }
        inline
        result<void>
        make_result( throw_ && ) noexcept
            {
            assert(has_current_error());
            return result<void>(noexcept_detail::get_current_error()->extract());
            }
        inline
        result<void>
        make_void_result() noexcept
            {
            if( auto err=noexcept_detail::get_current_error() )
                return result<void>(err->extract());
            else
                return result<void>();
            }
        template <class T>
        handler<T>
        try_( result<T> && x ) noexcept
            {
            return try_(std::move(x.check()));
            }
        template <>
        handler<void>
        try_<void>( result<void> && x ) noexcept
            {
            (void) x.check();
            return void_try_();
            }
        }
    }

#endif
