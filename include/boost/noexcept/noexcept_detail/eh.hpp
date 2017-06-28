//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_B77EFEB45BBD11E7B59A8BBA7FA7C656
#define UUID_B77EFEB45BBD11E7B59A8BBA7FA7C656

#include <boost/noexcept/noexcept_config/assert.hpp>
#include <boost/noexcept/noexcept_config/rtti.hpp>
#include <boost/noexcept/noexcept_config/throw_exception.hpp>
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
namespace boost { namespace noexcept_ { class exception_info; } }
#else
#include <boost/exception/exception.hpp>
namespace boost { namespace noexcept_ { typedef boost::exception exception_info; } }
#endif
#include <type_traits>
#include <exception>
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
            enum { sizeof_max_error=128 };
            typedef std::aligned_storage<sizeof_max_error>::type error_storage;
            template <class> void tid_() { }
            ///////////////////////////////
            class
            error_base
                {
                virtual void throw_exception_() { };
                public:
                BOOST_NOEXCEPT_NORETURN
                void
                throw_exception()
                    {
                    throw_exception_();
                    std::terminate();
                    }
                virtual exception_info * get_exception_info() noexcept { return 0; }
                virtual std::exception * get_std_exception() noexcept=0;
                virtual void * get_obj( void (*typeid_)() ) noexcept=0;
                virtual ~error_base() noexcept { }
                };
            ///////////////////////////////
            template <class E,
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                bool ExceptionInfoDisabled=true,
#else
                bool DerivesFromExceptionInfo=std::is_base_of<exception_info,E>::value,
#endif
                bool DerivesFromStdException=std::is_base_of<std::exception,E>::value>
            struct class_dispatch;
            ///////////////////////////////
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
            template <class E>
            struct
            class_dispatch<E,false,false>
                {
                class
                type:
                    public exception_info,
                    public std::exception,
                    public error_base,
                    public E
                    {
#ifndef BOOST_NOEXCEPT_NO_EXCEPTIONS
                    void throw_exception_() { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
#endif
                    exception_info * get_exception_info() noexcept { return this; }
                    std::exception * get_std_exception() noexcept { return this; }
                    void * get_obj( void (*typeid_)() ) noexcept { return typeid_==&tid_<E const>?static_cast<E *>(this):0; }
                    public:
                    explicit
                    type( E && e ) noexcept:
                        E(std::move(e))
                        {
                        }
                    type( type const & ) = default;
                    type( type && ) = default;
                    };
                };
            template <class E>
            struct
            class_dispatch<E,false,true>
                {
                class
                type:
                    public exception_info,
                    public error_base,
                    public E
                    {
#ifndef BOOST_NOEXCEPT_NO_EXCEPTIONS
                    void throw_exception_() { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
#endif
                    exception_info * get_exception_info() noexcept { return this; }
                    std::exception * get_std_exception() noexcept { return this; }
                    void * get_obj( void (*typeid_)() ) noexcept { return typeid_==&tid_<E const>?static_cast<E *>(this):0; }
                    public:
                    explicit
                    type( E && e ) noexcept:
                        E(std::move(e))
                        {
                        }
                    type( type const & ) = default;
                    type( type && ) = default;
                    };
                };
#endif
            ///////////////////////////////
            template <class E>
            struct
            class_dispatch<E,true,false>
                {
                class
                type:
                    public std::exception,
                    public error_base,
                    public E
                    {
#ifndef BOOST_NOEXCEPT_NO_EXCEPTIONS
                    void throw_exception_() { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
#endif
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                    exception_info * get_exception_info() noexcept { return this; }
#endif
                    std::exception * get_std_exception() noexcept { return this; }
                    void * get_obj( void (*typeid_)() ) noexcept { return typeid_==&tid_<E const>?static_cast<E *>(this):0; }
                    public:
                    explicit
                    type( E && e ) noexcept:
                        E(std::move(e))
                        {
                        }
                    type( type const & ) = default;
                    type( type && ) = default;
                    };
                };
            template <class E>
            struct
            class_dispatch<E,true,true>
                {
                class
                type:
                    public error_base,
                    public E
                    {
#ifndef BOOST_NOEXCEPT_NO_EXCEPTIONS
                    void throw_exception_() { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
#endif
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                    exception_info * get_exception_info() noexcept { return this; }
#endif
                    std::exception * get_std_exception() noexcept { return this; }
                    void * get_obj( void (*typeid_)() ) noexcept { return typeid_==&tid_<E const>?static_cast<E *>(this):0; }
                    public:
                    explicit
                    type( E && e ) noexcept:
                        E(std::move(e))
                        {
                        }
                    type( type const & ) = default;
                    type( type && ) = default;
                    };
                };
            ///////////////////////////////
            template <class E,bool IsClass=std::is_class<E>::value> struct wrap;
            template <class E>
            struct
            wrap<E,false>
                {
                class
                type:
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                    public exception_info,
#endif
                    public std::exception,
                    public error_base
                    {
                    E value_;
#ifndef BOOST_NOEXCEPT_NO_EXCEPTIONS
                    void throw_exception_() { throw value_; }
#endif
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                    exception_info * get_exception_info() noexcept { return this; }
#endif
                    std::exception * get_std_exception() noexcept { return this; }
                    void * get_obj( void (*typeid_)() ) noexcept { return typeid_==&tid_<E const>?&value_:0; }
                    public:
                    explicit
                    type( E && e ) noexcept:
                        value_(std::move(e))
                        {
                        }
                    type( type const & ) = default;
                    type( type && ) = default;
                    };
                };
            template <class E>
            struct
            wrap<E,true>
                {
                typedef typename class_dispatch<E>::type type;
                };
            template <class E,bool ErrorTypeTooBig=(sizeof(typename wrap<E>::type)>sizeof_max_error)> struct final_type;
            template <class E>
            struct
            final_type<E,false>
                {
                typedef typename wrap<E>::type type;
                };
            ///////////////////////////////
            template <class T>
            void
            move_( void * dst, void * src ) noexcept
                {
                (void) new (dst) T(std::move(*reinterpret_cast<T *>(src)));
                }
            typedef void (mover_t)( void *, void *);
            void
            move_error( mover_t * & dst_mvr, void * dst, error_base * & dst_px, mover_t * src_mvr, void * src, error_base * & src_px ) noexcept
                {
                if( src_px )
                    {
                    dst_mvr=src_mvr;
                    src_mvr(dst,src);
                    dst_px = reinterpret_cast<error_base *>(reinterpret_cast<unsigned char *>(dst) + (reinterpret_cast<unsigned char const *>(src_px) - reinterpret_cast<unsigned char *>(src)));
#ifndef BOOST_NOEXCEPT_NO_RTTI
                    BOOST_NOEXCEPT_ASSERT(typeid(*dst_px)==typeid(*src_px));
#endif
                    src_px->~error_base();
                    src_px=0;
                    }
                else
                    dst_px=0;
                }
            template <class E>
            typename final_type<E>::type *
            init_error( E && e, mover_t * & mvr, void * storage ) noexcept
                {
                typedef typename final_type<E>::type T;
                T * w = new (storage) T(std::move(e));
                mvr = &move_<T>;
                return w;
                }
            ///////////////////////////////
            }
        }
    }

#endif
