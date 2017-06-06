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
    noexcept_detail
        {
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
                return new T(std::move(obj));
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
            any_movable( any_movable const & )=delete;
            any_movable & operator=( any_movable const & )=delete;
            unsigned char static_storage_[MaxStaticSize];
            CommonBaseType * object_;
			void (*destroyer_)( void * );
            void (*static_mover_)( void *, void * );
            void (*observer_)( CommonBaseType * );
            void
            init( any_movable && x ) noexcept
                {
                if( x.object_ )
                    {
					destroyer_=x.destroyer_;
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
            public:

            any_movable() noexcept:
                object_(0),
				destroyer_(0),
                static_mover_(0),
                observer_(0)
                {
                BOOST_NOEXCEPT_ASSERT(empty());
                }
            any_movable( any_movable && x ) noexcept:
                object_(0),
				destroyer_(0),
                static_mover_(0),
                observer_(0)
                {
                init(std::move(x));
                }
            any_movable &
            operator=( any_movable && x ) noexcept
                {
                clear();
                init(std::move(x));
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
            void
            put( T && obj, void (*observer)(CommonBaseType *)=0 ) noexcept
                {
                clear();
                T * ob = putter<T,(sizeof(T)>MaxStaticSize)>::put(std::move(obj),static_storage_);
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

#endif
