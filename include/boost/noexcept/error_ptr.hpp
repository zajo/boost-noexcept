//Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_8D724FC250CD11E7B452FEE13E672F2F
#define UUID_8D724FC250CD11E7B452FEE13E672F2F

#include <boost/noexcept/try.hpp>

namespace
boost
    {
    namespace
    noexcept_
        {
        typedef std::shared_ptr<noexcept_detail::error_holder const> error_ptr;
        inline
        error_ptr
        error_handler::
        make_error_ptr() const noexcept
            {
            if( has_error() )
                return std::make_shared<noexcept_detail::error_holder>(*caught_);
            else
                return std::shared_ptr<noexcept_detail::error_holder const>();
            }
        namespace
        noexcept_detail
            {
            inline
            void
            current_error_holder::
            set( error_holder const & e ) noexcept
                {
                if( h_ )
                    {
                    h_->store_internally(std::move(e_));
                    h_=0;
                    }
                BOOST_NOEXCEPT_ASSERT(e_.empty() && "Unhandled error is present at the time a new error is passed to throw_()! (Did you forget to use try_?)");
                e_=e;
                }
            }
        }
    }

#endif
