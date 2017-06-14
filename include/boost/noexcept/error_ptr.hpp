//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_8D724FC250CD11E7B452FEE13E672F2F
#define UUID_8D724FC250CD11E7B452FEE13E672F2F

#include <boost/noexcept/noexcept_detail/current_error.hpp>
#include <boost/noexcept/throw.hpp>

namespace
boost
    {
    namespace
    noexcept_
        {
        inline
        error_ptr
        make_error_ptr() noexcept
            {
            if( has_current_error() )
                return std::make_shared<noexcept_detail::error_holder>(noexcept_detail::current_error().move_out());
            else
                return error_ptr();
            }
        inline
        throw_::
        throw_( error_ptr const & p )
            {
            if( p )
                noexcept_detail::current_error().move_in(std::move(*p));
            }
        namespace
        noexcept_detail
            {
            inline
            error_holder
            current_error_holder::
            move_out() noexcept
                {
                BOOST_NOEXCEPT_ASSERT(has_current_error());
                BOOST_NOEXCEPT_ASSERT(h_==0);
                return std::move(e_);
                }
            inline
            void
            current_error_holder::
            move_in( error_holder && e ) noexcept
                {
                if( h_ )
                    {
                    h_->store_internally(std::move(e_));
                    h_=0;
                    }
                BOOST_NOEXCEPT_ASSERT(e_.empty() && "Unhandled error is present at the time a new error is passed to throw_()! (Did you forget to use try_?)");
                e_=std::move(e);
                }
            }
        }
    }

#endif
