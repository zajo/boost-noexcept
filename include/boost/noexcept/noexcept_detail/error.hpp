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
            template <class T> T * new_nothrow_move( T && ) noexcept;
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
                throw_exception() const
                    {
                    throw_exception_();
                    std::terminate();
                    }
                private:
                virtual void throw_exception_() const=0;
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
                    void throw_exception_() const { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
                    public:
                    explicit
                    type( E && e ) noexcept:
                        E(std::move(e))
                        {
                        }
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
                    void throw_exception_() const { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
                    public:
                    explicit
                    type( E && e ) noexcept:
                        E(std::move(e))
                        {
                        }
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
                    void throw_exception_() const { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
                    public:
                    explicit
                    type( E && e ) noexcept:
                        E(std::move(e))
                        {
                        }
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
                    void throw_exception_() const { BOOST_NOEXCEPT_THROW_EXCEPTION(*this); }
                    public:
                    explicit
                    type( E && e ) noexcept:
                        E(std::move(e))
                        {
                        }
                    };
                };
            template <class E,bool IsClass=std::is_class<E>::value> struct wrap;
            template <class E>
            struct
            wrap<E,false>
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
                    void throw_exception_() const { throw value_; }
                    public:
                    explicit
                    type( E && e ) noexcept:
                        value_(std::move(e))
                        {
                        }
                    };
                };
            template <class E>
            struct
            wrap<E,true>
                {
                typedef typename class_dispatch<E>::type type;
                };
            ///////////////////////////////
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
                    return new_nothrow_move<T>(std::move(obj));
                    }
                };
            ///////////////////////////////
            template <class T>
            void
            static_move_( void * dst, void * src ) noexcept
                {
                (void) new (dst) T(std::move(*reinterpret_cast<T *>(src)));
                }
            ///////////////////////////////
            class
            error
                {
                public:
                enum enum_ { max_static_size=128 };
                private:
                typedef error_base error_base;
                std::aligned_storage<max_static_size,16>::type static_storage_;
                void (*static_mover_)( void *, void * ) noexcept;
                error_base * px_;
                void
                init( error && x ) noexcept
                    {
                    if( x.px_ )
                        {
                        if( x.static_mover_ )
                            {
                            BOOST_NOEXCEPT_ASSERT(reinterpret_cast<unsigned char *>(x.px_)>=reinterpret_cast<unsigned char *>(&x.static_storage_));
                            BOOST_NOEXCEPT_ASSERT(reinterpret_cast<unsigned char *>(x.px_)<reinterpret_cast<unsigned char *>(&x.static_storage_+max_static_size));
                            static_mover_=x.static_mover_;
                            static_mover_(&static_storage_,&x.static_storage_);
                            px_ = reinterpret_cast<error_base *>(reinterpret_cast<unsigned char *>(&static_storage_) + (reinterpret_cast<unsigned char const *>(x.px_) - reinterpret_cast<unsigned char *>(&x.static_storage_)));
                            x.px_->~error_base();
                            }
                        else
                            px_=x.px_;
                        x.px_=0;
                        BOOST_NOEXCEPT_ASSERT(!empty());
                        }
                    else
                        BOOST_NOEXCEPT_ASSERT(empty());
                    BOOST_NOEXCEPT_ASSERT(x.empty());
                    }
                template <class T>
                T *
                put_( T && obj ) noexcept
                    {
                    clear();
                    T * ob = putter<T,(sizeof(T)>max_static_size)>::put(std::move(obj),&static_storage_);
                    if( !ob )
                        {
                        BOOST_NOEXCEPT_ASSERT(sizeof(T)>max_static_size);
                        return 0;
                        }
                    if( reinterpret_cast<unsigned char const *>(ob) == reinterpret_cast<unsigned char const *>(&static_storage_) )
                        static_mover_ = &static_move_<T>;
                    else
                        static_mover_=0;
                    px_=ob;
                    return ob;
                    }
                public:
                error() noexcept:
                    static_mover_(0),
                    px_(0)
                    {
                    BOOST_NOEXCEPT_ASSERT(empty());
                    }
                error( error && x ) noexcept:
                    static_mover_(0),
                    px_(0)
                    {
                    init(std::move(x));
                    }
                error &
                operator=( error && x ) noexcept
                    {
                    clear();
                    init(std::move(x));
                    return *this;
                    }
                ~error() noexcept
                    {
                    clear();
                    }
                bool
                empty() const noexcept
                    {
                    return px_==0;
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
                        if( holds_static() )
                            px_->~error_base();
                        else
                            delete px_;
                        px_=0;
                        }
                    BOOST_NOEXCEPT_ASSERT(empty());
                    }
                template <class E>
                exception_info *
                put( E && e ) noexcept
                    {
                    if( auto p=put_(typename wrap<E>::type(std::move(e))) )
                        return p;
                    else
                        {
                        BOOST_NOEXCEPT_ASSERT(empty());
                        return put_(typename wrap<std::bad_alloc>::type(std::bad_alloc()));
                        }
                    }
                template <class E>
                void
                put_with_location( E && e, char const * file, int line, char const * function ) noexcept
                    {
                    BOOST_NOEXCEPT_ASSERT(file&&*file);
                    BOOST_NOEXCEPT_ASSERT(line>0);
                    BOOST_NOEXCEPT_ASSERT(function&&*function);
                    exception_info & xi=*put(std::move(e));
#ifndef BOOST_NOEXCEPT_NO_EXCEPTION_INFO                
                    using namespace ::boost::exception_detail;
                    set_info(xi,throw_file(file));
                    set_info(xi,throw_line(line));
                    set_info(xi,throw_function(function));
#endif
                    }
                BOOST_NOEXCEPT_NORETURN
                void
                throw_exception() const
                    {
                    BOOST_NOEXCEPT_ASSERT(!empty());
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
