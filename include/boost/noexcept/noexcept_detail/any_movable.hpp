//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_4074489A481911E7BE231D4A7F4E887A
#define UUID_4074489A481911E7BE231D4A7F4E887A

#include <boost/noexcept/noexcept_config/assert.hpp>
#include <new>

namespace
boost
    {
    namespace
    noexcept_
        {
        namespace
        noexcept_detail
            {
            template <class T> T * new_nothrow_move( T && );
            template <class T> T * new_nothrow_copy( T const & );
            template <class T,bool requires_dynamic_allocation>
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
                    return new_nothrow_move(std::move(obj));
                    }
                };
            template <class T,bool requires_dynamic_allocation>
            struct copier;
            template <class T>
            struct
            copier<T,false>
                {
                static
                void *
                copy( void const * obj, void * where ) noexcept
                    {
                    return obj==0? 0 : new (where) T(*static_cast<T const *>(obj));
                    }
                };
            template <class T>
            struct
            copier<T,true>
                {
                static
                void *
                copy( void const * obj, void * ) noexcept
                    {
                    return obj==0? 0 : new_nothrow_copy(*static_cast<T const *>(obj));
                    }
                };
            template <class T>
            void
            destruct_( void * obj )
                {
                assert(obj!=0);
                reinterpret_cast<T *>(obj)->~T();
                }
            template <class T>
            void
            delete_( void * obj )
                {
                assert(obj!=0);
                delete reinterpret_cast<T *>(obj);
                }
            template <class T>
            void
            static_move_( void * dst, void * src ) noexcept
                {
                (void) new (dst) T(std::move(*reinterpret_cast<T *>(src)));
                }
            template <int MaxStaticSize,class CommonBaseType=void>
            class
            any_movable
                {
                unsigned char static_storage_[MaxStaticSize];
                void (*destroyer_)( void * );
                void * (*copier_)( void const *, void * );
                void (*static_mover_)( void *, void * );
                void (*observer_)( CommonBaseType * );
                CommonBaseType * object_;
                void
                init( any_movable && x ) noexcept
                    {
                    if( x.object_ )
                        {
                        destroyer_=x.destroyer_;
                        copier_=x.copier_;
                        observer_=x.observer_;
                        if( x.static_mover_ )
                            {
                            BOOST_NOEXCEPT_ASSERT(reinterpret_cast<unsigned char *>(x.object_)>=x.static_storage_);
                            BOOST_NOEXCEPT_ASSERT(reinterpret_cast<unsigned char *>(x.object_)<x.static_storage_+MaxStaticSize);
                            static_mover_=x.static_mover_;
                            static_mover_(static_storage_,x.static_storage_);
                            object_ = reinterpret_cast<CommonBaseType *>(static_storage_ + (reinterpret_cast<unsigned char const *>(x.object_) - x.static_storage_));
                            destroyer_(x.object_);
                            }
                        else
                            object_=x.object_;
                        x.object_=0;
                        BOOST_NOEXCEPT_ASSERT(!empty());
                        }
                    else
                        BOOST_NOEXCEPT_ASSERT(empty());
                    BOOST_NOEXCEPT_ASSERT(x.empty());
                    }
                void
                init( any_movable const & x ) noexcept
                    {
                    if( x.object_ )
                        {
                        destroyer_=x.destroyer_;
                        copier_=x.copier_;
                        static_mover_=x.static_mover_;
                        observer_=x.observer_;
                        object_ = static_cast<CommonBaseType *>(copier_(x.object_,static_storage_));
                        }
                    else
                        BOOST_NOEXCEPT_ASSERT(empty());
                    }
                public:
                enum enum_ { max_static_size=MaxStaticSize };
                any_movable() noexcept:
                    destroyer_(0),
                    copier_(0),
                    static_mover_(0),
                    observer_(0),
                    object_(0)
                    {
                    BOOST_NOEXCEPT_ASSERT(empty());
                    }
                any_movable( any_movable && x ) noexcept:
                    destroyer_(0),
                    copier_(0),
                    static_mover_(0),
                    observer_(0),
                    object_(0)
                    {
                    init(std::move(x));
                    }
                any_movable( any_movable const & x ) noexcept:
                    destroyer_(x.destroyer_),
                    copier_(x.copier_),
                    static_mover_(x.static_mover_),
                    observer_(x.observer_),
                    object_(static_cast<CommonBaseType *>(copier_(x.object_,static_storage_)))
                    {
                    }
                any_movable &
                operator=( any_movable && x ) noexcept
                    {
                    clear();
                    init(std::move(x));
                    return *this;
                    }
                any_movable &
                operator=( any_movable const & x ) noexcept
                    {
                    clear();
                    destroyer_=x.destroyer_;
                    copier_=x.copier_;
                    static_mover_=x.static_mover_;
                    observer_=x.observer_;
                    object_=static_cast<CommonBaseType *>(copier_(x.object_,static_storage_));
                    return *this;
                    }
                ~any_movable() noexcept
                    {
                    clear();
                    }
                bool
                empty() const noexcept
                    {
                    return object_==0;
                    }
                bool
                holds_static() const noexcept
                    {
                    return !empty() && static_mover_!=0;
                    }
                bool
                holds_dynamic() const noexcept
                    {
                    return !empty()!=0 && static_mover_==0;
                    }
                void
                clear() noexcept
                    {
                    if( !empty() )
                        {
                        destroyer_(object_);
                        object_=0;
                        }
                    BOOST_NOEXCEPT_ASSERT(empty());
                    }
                template <class T>
                T *
                put( T && obj, void (*observer)(CommonBaseType *)=0 ) noexcept
                    {
                    clear();
                    T * ob = putter<T,(sizeof(T)>MaxStaticSize)>::put(std::move(obj),static_storage_);
                    if( !ob )
                        return 0;
                    copier_=&copier<T,(sizeof(T)>MaxStaticSize)>::copy;
                    object_=ob; //pointer adjustment in case of multiple inheritance
                    if( reinterpret_cast<unsigned char const *>(ob) == static_storage_ )
                        {
                        static_mover_ = &static_move_<T>;
                        destroyer_ = &destruct_<T>;
                        }
                    else
                        {
                        BOOST_NOEXCEPT_ASSERT(object_!=0);
                        static_mover_=0;
                        destroyer_ = &delete_<T>;
                        }
                    observer_ = observer;
                    return ob;
                    }
                CommonBaseType *
                get() const noexcept
                    {
                    return object_;
                    }
                void
                call_observer() const
                    {
                    BOOST_NOEXCEPT_ASSERT(observer_!=0);
                    observer_(object_);
                    }
                };
            }
        }
    }

#endif
