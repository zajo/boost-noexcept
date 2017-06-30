//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_5872130C482B11E7B84F4C607F4E887A
#define UUID_5872130C482B11E7B84F4C607F4E887A

#include <boost/noexcept/noexcept_detail/ceh.hpp>
#include <boost/noexcept/noexcept_detail/error.hpp>

namespace
boost
    {
    namespace
    noexcept_
        {
        template <class T> class result;
        ///////////////////////////////////
        template <class T> result<T> try_( T && ) noexcept;
        template <class T>
        class
        result
            {
            result( result const & )=delete;
            result & operator=( result const & )=delete;
            class
            pthrow_
                {
                pthrow_( pthrow_ const & )=delete;
                pthrow_ & operator=( pthrow_ const & )=delete;
                public:
                template <class R>
                operator R() noexcept
                    {
                    return throw_return<R>::value();
                    }
                };
            protected:
            typedef boost::noexcept_::noexcept_detail::error error;
            private:
            friend result<T> try_<T>( T && ) noexcept;
            union
                {
                T val_;
                mutable error err_;
                };
            enum
            what_type
                {
                wh_value,
                wh_unhandled_error,
                wh_error
                };
            what_type what_;
            protected:
            explicit
            result( T && val ) noexcept:
                val_(std::move(val)),
                what_(wh_value)
                {
                BOOST_NOEXCEPT_ASSERT(!has_current_error());
                }
            explicit
            result( noexcept_detail::current_error_holder & ceh ) noexcept:
                err_(ceh.extract()),
                what_(wh_unhandled_error)
                {
                }
            public:
            result( result && x ) noexcept:
                what_(x.what_)
                {
                if( x.has_error() )
                    {
                    (void) new (&err_) error(std::move(x.err_));
                    if( x.has_unhandled_error() )
                        x.what_=wh_error;
                    }
                else
                    {
                   BOOST_NOEXCEPT_ASSERT(!has_error());
                    (void) new (&val_) T(std::move(x.val_));
                    }
                }
            ~result() noexcept
                {
                if( has_error() )
                    {
                    if( has_unhandled_error() )
                        noexcept_detail::ceh().set(std::move(err_));
                    err_.~error();
                    }
                else
                    {
                    BOOST_NOEXCEPT_ASSERT(!has_error());
                    val_.~T();
                    }
                }
            explicit operator bool() const noexcept
                {
                return what_==wh_value;
                }
            bool
            has_error() const noexcept
                {
                return what_!=wh_value;
                }
            bool
            has_unhandled_error() const noexcept
                {
                return what_==wh_unhandled_error;
                }
            template <class E=std::exception>
            E *
            catch_() noexcept
                {
                if( has_error() )
                
                    if( E * e=err_.get<E>() )
                        {
                        what_=wh_error;
                        return e;
                        }
                return 0;
                }
            pthrow_ &
            throw_() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(has_error());
                noexcept_detail::ceh().set(std::move(err_));
                what_=wh_error;
                return *reinterpret_cast<pthrow_ *>(this);
                }
            BOOST_NOEXCEPT_NORETURN
            void
            throw_exception()
                {
                BOOST_NOEXCEPT_ASSERT(has_error());
                what_=wh_error;
                err_.throw_exception();
                }
            T const &
            get() const
                {
                if( has_error() )
                    throw_exception();
                else
                    return val_;
                }
            T &
            get()
                {
                if( has_error() )
                    throw_exception();
                else
                    return val_;
                }
            };
        template <class T>
        result<T>
        try_( T && x ) noexcept
            {
            noexcept_detail::current_error_holder & ceh=noexcept_detail::ceh();
            if( ceh.empty() )
                return result<T>(std::move(x));
            else
                return result<T>(ceh);
            }
        ///////////////////////////////////
        result<void> current_error() noexcept;
        template <>
        class
        result<void>:
            public result<bool>
            {
            result( result const & )=delete;
            result & operator=( result const & )=delete;
            friend result<void> current_error() noexcept;
            typedef result<bool> base;
            explicit
            result( bool x ):
                base(std::move(x))
                {
                }
            result( noexcept_detail::current_error_holder & ceh ):
                base(ceh)
                {
                }
            public:
            result( result && ) = default;
            };
        inline
        result<void>
        current_error() noexcept
            {
            noexcept_detail::current_error_holder & ceh=noexcept_detail::ceh();
            if( ceh.empty() )
                return result<void>(true);
            else
                return result<void>(ceh);
            }
        ///////////////////////////////////
        namespace
        noexcept_detail
            {
            inline
            error
            current_error_holder::
            extract() noexcept
                {
                return error(mover_,&storage_,px_);
                }
            inline
            void
            current_error_holder::
            set( error && e ) noexcept
                {
                ensure_empty();
                e.move_to(mover_,&storage_,px_);
                }
            }
        }
    }

#endif
