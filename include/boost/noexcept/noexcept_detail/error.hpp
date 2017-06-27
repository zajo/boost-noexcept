//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_4074489A481911E7BE231D4A7F4E887A
#define UUID_4074489A481911E7BE231D4A7F4E887A

#include <boost/noexcept/noexcept_config/assert.hpp>
#include <boost/noexcept/noexcept_config/rtti.hpp>
#include <boost/noexcept/noexcept_config/throw_exception.hpp>
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
namespace boost { namespace noexcept_ { class exception_info { }; } }
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
            typedef void (*type_id)();
            ///////////////////////////////
            class
            error_base
                {
                public:
                virtual ~error_base() noexcept { }
                virtual std::exception * get_std_exception() noexcept=0;
                virtual exception_info * get_exception_info() noexcept=0;
                virtual void * get_obj( void (*typeid_)() ) noexcept=0;
                BOOST_NOEXCEPT_NORETURN
                void
                throw_exception()
                    {
                    throw_exception_();
                    std::terminate();
                    }
                private:
                virtual void throw_exception_()=0;
                };
            ///////////////////////////////
            template <class E,
                bool DerivesFromStdException=std::is_base_of<std::exception,E>::value,
                bool DerivesFromExceptionInfo=std::is_base_of<exception_info,E>::value>
            struct class_dispatch;
            template <class E>
            struct
            class_dispatch<E,false,false>
                {
                class
                type:
                    public std::exception,
                    public exception_info,
                    public error_base,
                    public E
                    {
                    std::exception * get_std_exception() noexcept { return this; }
                    exception_info * get_exception_info() noexcept { return this; }
                    void * get_obj( void (*typeid_)() ) noexcept { return typeid_==&tid_<E const>?static_cast<E *>(this):0; }
                    void throw_exception_() { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
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
                    public std::exception,
                    public error_base,
                    public E
                    {
                    std::exception * get_std_exception() noexcept { return this; }
                    exception_info * get_exception_info() noexcept { return this; }
                    void * get_obj( void (*typeid_)() ) noexcept { return typeid_==&tid_<E const>?static_cast<E *>(this):0; }
                    void throw_exception_() { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
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
            class_dispatch<E,true,false>
                {
                class
                type:
                    public exception_info,
                    public error_base,
                    public E
                    {
                    std::exception * get_std_exception() noexcept { return this; }
                    exception_info * get_exception_info() noexcept { return this; }
                    void * get_obj( void (*typeid_)() ) noexcept { return typeid_==&tid_<E const>?static_cast<E *>(this):0; }
                    void throw_exception_() { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
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
                    std::exception * get_std_exception() noexcept { return this; }
                    exception_info * get_exception_info() noexcept { return this; }
                    void * get_obj( void (*typeid_)() ) noexcept { return typeid_==&tid_<E const>?static_cast<E *>(this):0; }
                    void throw_exception_() { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
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
            template <class E,bool IsClass=std::is_class<E>::value,bool ErrorTypeTooBig=(sizeof(E)>sizeof_max_error)> struct wrap;
            template <class E>
            struct
            wrap<E,false,false>
                {
                class
                type:
                    public std::exception,
                    public exception_info,
                    public error_base
                    {
                    E value_;
                    std::exception * get_std_exception() noexcept { return this; }
                    exception_info * get_exception_info() noexcept { return this; }
                    void * get_obj( void (*typeid_)() ) noexcept { return typeid_==&tid_<E const>?&value_:0; }
                    void
                    throw_exception_()
                        {
#ifdef BOOST_NOEXCEPT_NO_EXCEPTIONS
                        std::terminate();
#else
                        throw value_;
#endif
                        }
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
            wrap<E,true,false>
                {
                typedef typename class_dispatch<E>::type type;
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
                    src_px->~error_base();
                    src_px=0;
                    }
                else
                    dst_px=0;
                }
            ///////////////////////////////
            class
            error
                {
                error( error const & )=delete;
                error & operator=( error const & )=delete;
                error_storage storage_;
                error_base * px_;
                mover_t * mover_;
                template <class E>
                typename wrap<E>::type *
                init( E && e ) noexcept
                    {
                    typedef typename wrap<E>::type T;
                    T * w = new (&storage_) T(std::move(e));
                    px_ = w;
                    mover_ = &move_<T>;
                    return w;
                    }
                public:
                template <class E>
                explicit
                error( E && e ) noexcept
                    {
                    (void) init(std::move(e));
                    }
                template <class E>
                explicit
                error( E && e, char const * file, int line, char const * function ) noexcept
                    {
                    typename wrap<E>::type * w=init(std::move(e));
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                    (void) w;
#else
                    using namespace ::boost::exception_detail;
                    set_info(*w,throw_file(file));
                    set_info(*w,throw_line(line));
                    set_info(*w,throw_function(function));
#endif
                    }
                error( error && x ) noexcept
                    {
                    move_error(mover_,&storage_,px_,x.mover_,&x.storage_,x.px_);
                    BOOST_NOEXCEPT_ASSERT(x.px_==0);
                    }
                error( mover_t * src_mvr, void * src, error_base * & src_px ) noexcept
                    {
                    move_error(mover_,&storage_,px_,src_mvr,src,src_px);
                    }
                void
                move_to( mover_t * & dst_mvr, void * dst, error_base * & dst_px ) noexcept
                    {
                    move_error(dst_mvr,dst,dst_px,mover_,&storage_,px_);
                    BOOST_NOEXCEPT_ASSERT(px_==0);
                    }
                ~error() noexcept
                    {
                    if( px_ )
                        px_->~error_base();
                    }
                BOOST_NOEXCEPT_NORETURN
                void
                throw_exception()
                    {
                    BOOST_NOEXCEPT_ASSERT(px_!=0);
                    px_->throw_exception();
                    }
                template <class E=std::exception> E const * get() const noexcept;
                template <class E=std::exception> E * get() noexcept;
                };
            template <>
            std::exception const *
            error::
            get<std::exception>() const noexcept
                {
                return px_?px_->get_std_exception():0;
                }
            template <>
            std::exception const *
            error::
            get<std::exception const>() const noexcept
                {
                return px_?px_->get_std_exception():0;
                }
            template <>
            std::exception *
            error::
            get<std::exception>() noexcept
                {
                return px_?px_->get_std_exception():0;
                }
            template <>
            std::exception const *
            error::
            get<std::exception const>() noexcept
                {
                return px_?px_->get_std_exception():0;
                }
            template <>
            exception_info const *
            error::
            get<exception_info>() const noexcept
                {
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                return 0;
#else
                return px_?px_->get_exception_info():0;
#endif
                }
            template <>
            exception_info const *
            error::
            get<exception_info const>() const noexcept
                {
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                return 0;
#else
                return px_?px_->get_exception_info():0;
#endif
                }
            template <>
            exception_info *
            error::
            get<exception_info>() noexcept
                {
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                return 0;
#else
                return px_?px_->get_exception_info():0;
#endif
                }
            template <>
            exception_info const *
            error::
            get<exception_info const>() noexcept
                {
#ifdef BOOST_NOEXCEPT_NO_EXCEPTION_INFO
                return 0;
#else
                return px_?px_->get_exception_info():0;
#endif
                }
            template <class E,bool IsClass=std::is_class<E>::value> struct dynamic;
            template <class E>
            struct
            dynamic<E,true>
                {
#ifdef BOOST_NOEXCEPT_NO_RTTI
                static E * cast( error_base * ) noexcept { return 0; }
#else                    
                static E * cast( error_base * px ) noexcept { return dynamic_cast<E *>(px); }
#endif
                };
            template <class E>
            struct
            dynamic<E,false>
                {
                static E * cast( error_base * ) noexcept { return 0; }
                };
            template <class E>
            E const *
            error::
            get() const noexcept
                {
                if( !px_ )
                    return 0;
                else if( void const * e=px_->get_obj(&tid_<E const>) )
                    return reinterpret_cast<E const *>(e);
                else
                    return dynamic<E>::cast(px_);
                }
            template <class E>
            E *
            error::
            get() noexcept
                {
                if( !px_ )
                    return 0;
                if( void * e=px_->get_obj(&tid_<E const>) )
                    return reinterpret_cast<E *>(e);
                else
                    return dynamic<E>::cast(px_);
                }
            }
        }
    }

#endif
