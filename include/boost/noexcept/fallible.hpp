//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_4393573848E011E794F821DB7E4E887A
#define UUID_4393573848E011E794F821DB7E4E887A

#include <boost/noexcept/noexcept_detail/exception_holder.hpp>
#include <boost/noexcept/noexcept_config/optional.hpp>
#include <boost/noexcept/noexcept_config/thread_local.hpp>

namespace
boost
    {
    namespace
    noexcept_detail
        {
        class
        current_exception_holder:
            public exception_holder
            {
            public:
            class
            handler
                {
                public:
                virtual void store_internally() noexcept=0;
                protected:
                ~handler() noexcept;
                };
            ~current_exception_holder() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(empty()); //The thread terminates with unhandled error
                if( !empty() )
                    abort();
                }
            template <class T>
            void
            put( T && obj ) noexcept
                {
                if( h_ )
                    {
                    h_->store_internally();
                    h_=0;
                    }
                BOOST_NOEXCEPT_ASSERT(empty());
                exception_holder::put(std::move(obj));
                }
            void set_handler( handler * ) noexcept;
            void unset_handler( handler * ) noexcept;
            private:
            handler * h_;
            };
        current_exception_holder &
        current_exception() noexcept
            {
            return get_tl_object<current_exception_holder>();
            }
        }
    class
    noexcept_propagate
        {
        noexcept_propagate( noexcept_propagate const & )=delete;
        noexcept_propagate & operator=( noexcept_propagate const & )=delete;
        public:
        noexcept_propagate() noexcept
            {
            }
        template <class T>
        noexcept_propagate( T && e ) noexcept
            {
            noexcept_detail::current_exception().put(std::move(e));
            }
        };
    template <class T> class fallible;
    template <class T> class noexcept_handler;
    template <class T> noexcept_handler<T> noexcept_try( fallible<T> && ) noexcept;
    template <class T>
    class
    fallible
        {
        friend noexcept_handler<T> noexcept_try<T>( fallible<T> && ) noexcept;
        fallible( fallible const & )=delete;
        fallible & operator=( fallible const & )=delete;
        noexcept_detail::optional<T> opt_;
        public:
        fallible( noexcept_propagate const & ) noexcept
            {
            BOOST_NOEXCEPT_ASSERT(!noexcept_detail::current_exception().empty());
            }
        fallible( T const & v ) noexcept:
            opt_(v)
            {
            BOOST_NOEXCEPT_ASSERT(noexcept_detail::current_exception().empty());
            }
        fallible( T && v ) noexcept:
            opt_(std::move(v))
            {
            BOOST_NOEXCEPT_ASSERT(noexcept_detail::current_exception().empty());
            }
        fallible( fallible && x ) noexcept:
            opt_(std::move(x.opt_))
            {
            BOOST_NOEXCEPT_ASSERT(succeeded()==!noexcept_detail::current_exception().empty());
            }
        T const &
        value() const noexcept
            {
            BOOST_NOEXCEPT_ASSERT(succeeded());
            return opt_.value();
            }
        T &
        value() noexcept
            {
            BOOST_NOEXCEPT_ASSERT(succeeded());
            return opt_.value();
            }
        bool
        succeeded() const noexcept
            {
            return bool(opt_);
            }
        bool
        failed() const noexcept
            {
            return !opt_;
            }
        explicit operator bool() const noexcept
            {
            return bool(opt_);
            }
        };
    }

#endif
