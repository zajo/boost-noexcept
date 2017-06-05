//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_4074489A481911E7BE231D4A7F4E887A
#define UUID_4074489A481911E7BE231D4A7F4E887A

#include <boost/noexcept/noexcept_config/assert.hpp>
#include <boost/noexcept/noexcept_config/throw_exception.hpp>
#include <new>
#include <utility>
#include <memory>
#include <exception>

namespace
boost
    {
    namespace
    noexcept_detail
        {
        static constexpr int max_static_size=256;

        template <class T,bool requires_dynamic_allocation=(sizeof(T)>max_static_size)>
        struct putter;

        template <class T>
        struct
        putter<T,false>
            {
            static
            T *
            put( T && obj, void * where ) noexcept
                {
                BOOST_NOEXCEPT_ASSERT(where!=0);
                return new (where) T(std::move(obj));
                }
            };

        template <class T>
        struct
        putter<T,true>
            {
            static
            T *
            put( T && obj, void * ) noexcept
                {
                return new T(std::move(obj));
                }
            };

        template <class T>
        static
        void
        static_move_( unsigned char (&dst)[max_static_size], unsigned char (&src)[max_static_size] ) noexcept
            {
            (void) new (&dst) T(std::move(*reinterpret_cast<T *>(src)));
            }

        template <class T>
        static
        void
        throw_( std::exception * e )
            {
            T * x = static_cast<T *>(e);
            BOOST_NOEXCEPT_THROW_EXCEPTION(*x);
            }

        class
        exception_holder
            {
            exception_holder( exception_holder const & )=delete;
            exception_holder & operator=( exception_holder const & )=delete;
            unsigned char static_storage_[max_static_size];
            std::exception * static_;
            std::unique_ptr<std::exception> dynamic_;
            void (*static_mover_)( unsigned char (&)[max_static_size], unsigned char (&)[max_static_size] );
            void (*thrower_)( std::exception * );

            void
            init( exception_holder && x ) noexcept
                {
                if( x.thrower_ )
                    {
                    thrower_=x.thrower_;
                    x.thrower_=0;
                    if( !dynamic_ )
                        {
                        BOOST_NOEXCEPT_ASSERT(x.static_mover_!=0);
                        x.static_mover_(static_storage_,x.static_storage_);
                        static_ = reinterpret_cast<std::exception *>(static_storage_ + (reinterpret_cast<unsigned char const *>(x.static_) - x.static_storage_));
                        static_mover_=x.static_mover_;
                        }
                    BOOST_NOEXCEPT_ASSERT((static_mover_!=0)  == !dynamic_);
                    BOOST_NOEXCEPT_ASSERT(!empty());
                    }
                else
                    BOOST_NOEXCEPT_ASSERT(empty());
                BOOST_NOEXCEPT_ASSERT(x.empty());
                }

            public:

            exception_holder() noexcept:
                static_(0),
                static_mover_(0),
                thrower_(0)
                {
                BOOST_NOEXCEPT_ASSERT(empty());
                }
            exception_holder( exception_holder && x ) noexcept:
                static_(0),
                dynamic_(std::move(x.dynamic_)),
                static_mover_(0),
                thrower_(0)
                {
                init(std::move(x));
                }
            exception_holder &
            operator=( exception_holder && x ) noexcept
                {
                clear();
                dynamic_=std::move(x.dynamic_);
                init(std::move(x));
                return *this;
                }
            ~exception_holder() noexcept
                {
                clear();
                }
            bool
            empty() const noexcept
                {
                BOOST_NOEXCEPT_ASSERT(thrower_==0 || static_mover_!=0 || dynamic_);
                BOOST_NOEXCEPT_ASSERT(thrower_!=0 || !dynamic_);
                return thrower_==0;
                }
            bool
            holds_static() const noexcept
                {
                BOOST_NOEXCEPT_ASSERT(thrower_==0 || static_mover_!=0 || dynamic_);
                BOOST_NOEXCEPT_ASSERT(thrower_!=0 || !dynamic_);
                return static_mover_!=0;
                }
            bool
            holds_dynamic() const noexcept
                {
                BOOST_NOEXCEPT_ASSERT(thrower_==0 || static_mover_!=0 || dynamic_);
                BOOST_NOEXCEPT_ASSERT(thrower_!=0 || !dynamic_);
                return bool(dynamic_);
                }
            void
            clear() noexcept
                {
                if( holds_static() )
                    {
                    BOOST_NOEXCEPT_ASSERT(!holds_dynamic());
                    static_->~exception();
                    static_=0;
                    static_mover_=0;
                    }
                else if( holds_dynamic() )
                    dynamic_.reset();
                thrower_=0;
                BOOST_NOEXCEPT_ASSERT(empty());
                }
            template <class T>
            void
            put( T && obj ) noexcept
                {
                clear();
                T * p = putter<T>::put(std::move(obj),static_storage_);
                if( reinterpret_cast<unsigned char const *>(p) == static_storage_ )
                    {
                    static_mover_ = &static_move_<T>;
                    static_ = p;
                    }
                else
                    {
                    BOOST_NOEXCEPT_ASSERT(p!=0);
                    dynamic_.reset(p);
                    }
                thrower_ = &throw_<T>;
                }
            std::exception *
            get() const noexcept
                {
                if( empty() )
                    return 0;
                else
                    return holds_static()?static_:dynamic_.get();
                }
            char const *
            what() const noexcept
                {
                BOOST_NOEXCEPT_ASSERT(!empty());
                return get()->what();
                }
            void
            throw_exception() const
                {
                BOOST_NOEXCEPT_ASSERT(!empty());
                thrower_(get());
                }
            };
        }
    }

#endif
