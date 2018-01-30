//Copyright (c) 2017-2018 Emil Dotchevski and BOOST_NOEXCEPT Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/noexcept_config/inline.hpp>
#include <chrono>
#include <iostream>
#include <stdlib.h>

#define BENCHMARK_INLINE BOOST_NOEXCEPT_INLINE_FORCEINLINE

namespace noexcept_ = boost::noexcept_;

template <class T>
T
compute_value()
    {
    return T(rand());
    }

template <>
std::string
compute_value<std::string>()
    {
    return rand()>RAND_MAX/2 ? "foo" : "bar";
    }

template <class ValueType, class ErrorType, int Depth>
struct
benchmark
    {
    static
    BENCHMARK_INLINE
    ValueType
    test_function( int success_percentage  )
        {
        return benchmark<ValueType,ErrorType,Depth-1>::test_function(success_percentage);
        }
    };

template <class ValueType, class ErrorType>
struct
benchmark<ValueType,ErrorType,0>
    {
    static
    BENCHMARK_INLINE
    ValueType
    test_function( int success_percentage  )
        {
        if( (rand()%100) > success_percentage )
            return noexcept_::throw_(ErrorType());
        else
            return compute_value<ValueType>();
        }
    };

template <class ValueType, class ErrorType, int Depth>
void
test_case( int success_percentage, int count )
    {
    auto start = std::chrono::steady_clock::now();
    for( int i=0; i!=count; ++i )
        if( auto r = noexcept_::try_(benchmark<ValueType,ErrorType,Depth>::test_function(success_percentage)) )
            ;
        else
            (void) r.template catch_<ErrorType>();
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout<<BOOST_CURRENT_FUNCTION<<", count="<<count<<", success_percentage="<<success_percentage<<": "<< std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()<<"ms"<<std::endl;
    }

int
main( int argc, char const * argv[ ] )
    {
    test_case<int,int,100>(50,100000);
    test_case<int,int,1000>(50,100000);
    return 0;
    }
