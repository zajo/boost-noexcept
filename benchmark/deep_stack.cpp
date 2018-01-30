//Copyright (c) 2017-2018 Emil Dotchevski and BOOST_NOEXCEPT Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//This benchmark program evaluates the performance of Noexcept depending on
//the number of stack frames error objects need to be propagated across.

//You can #define BENCHMARK_INLINE as BOOST_NOEXCEPT_INLINE_FORCEINLINE
//to enable inlining, which woulld give you benchmark in the case when all functions are
//inlined (no stack frames, no stack unwinding).

//Note that to use Noexcept this program should be compiled with exceptions handling
//disabled; if it is enabled, the program propagates errors by throwing exceptions.

//Below are some example command lines for g++ (assuming cwd=noexcept/benchmark).

//Use Noexcept, inlining disabled:
//g++ -O3 -std=c++11 -I../include -I ../../.. deep_stack.cpp -fno-exceptions

//Use Noexcept, forced inlining:
//g++ -O3 -std=c++11 -I../include -I ../../.. deep_stack.cpp -fno-exceptions -DBENCHMARK_INLINE=BOOST_NOEXCEPT_INLINE_FORCEINLINE

//Use c++ exceptions, inlining disabled:
//g++ -O3 -std=c++11 -I../include -I ../../.. deep_stack.cpp

//Use C++ exceptions, forced inlining:
//g++ -O3 -std=c++11 -I../include -I ../../.. deep_stack.cpp -DBENCHMARK_INLINE=BOOST_NOEXCEPT_INLINE_FORCEINLINE

#define BOOST_NOEXCEPT_NO_EXCEPTION_INFO

#include <boost/noexcept/try.hpp>
#include <boost/noexcept/throw.hpp>
#include <boost/noexcept/noexcept_config/inline.hpp>
#include <boost/config.hpp>
#include <chrono>
#include <string>
#include <iostream>
#include <stdlib.h>

#ifndef BENCHMARK_INLINE
#define BENCHMARK_INLINE BOOST_NOEXCEPT_INLINE_NOINLINE
#endif

namespace noexcept_ = boost::noexcept_;

struct my_error: std::exception { };

/////////////////////////////////////////////

template <class T>
BOOST_NOEXCEPT_INLINE_FORCEINLINE
T compute_value()
{
    return T(rand());
}

template <>
BOOST_NOEXCEPT_INLINE_FORCEINLINE
std::string compute_value<std::string>()
{
    return rand()>RAND_MAX/2 ? "foo" : "bar";
}

/////////////////////////////////////////////

template <int Depth,class ErrorType, class ValueType>
struct benchmark
{
    static BENCHMARK_INLINE
    ValueType test_function( int success_percentage  )
    {
        return benchmark<Depth-1,ErrorType,ValueType>::test_function(success_percentage);
    }
};

template <class ErrorType, class ValueType>
struct benchmark<0,ErrorType,ValueType>
{
    static BENCHMARK_INLINE
    ValueType test_function( int success_percentage  )
    {
        if( (rand()%100) > success_percentage )
#ifdef BOOST_NO_EXCEPTIONS
            return noexcept_::throw_(ErrorType());
#else
            throw ErrorType();
#endif
        else
            return compute_value<ValueType>();
    }
};

/////////////////////////////////////////////

template <int Depth,class ErrorType, class ValueType>
void test_case( int success_percentage, int count )
{
    auto start = std::chrono::steady_clock::now();

#ifdef BOOST_NO_EXCEPTIONS
    for( int i=0; i!=count; ++i )
        if( auto r = noexcept_::try_(benchmark<Depth,ErrorType,ValueType>::test_function(success_percentage)) )
            ;
        else
            (void) r.template catch_<ErrorType>();
#else
    for( int i=0; i!=count; ++i )
        try
        {
            benchmark<Depth,ErrorType,ValueType>::test_function(success_percentage);
        }
        catch( ErrorType & )
        {
        }
#endif

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout <<
        BOOST_CURRENT_FUNCTION << ", "
        "count=" << count << ", "
        "success %=" << success_percentage << ": " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << "ms" <<
        std::endl;
}

/////////////////////////////////////////////

#ifdef BOOST_NO_EXCEPTIONS
namespace boost
{
    void throw_exception( std::exception const & )
    {
        std::abort();
    }
}
#endif

int main( int argc, char const * argv[ ] )
{
#ifdef BOOST_NO_EXCEPTIONS
    std::cout << "Using Noexcept" << std::endl;
#else
    std::cout << "Using C++ exception handling" << std::endl;
#endif

    std::cout << std::endl;
    srand(0); test_case<50,my_error,int>(10,100000);
    srand(0); test_case<50,my_error,std::string>(10,100000);

    std::cout << std::endl;
    srand(0); test_case<50,my_error,int>(90,100000);
    srand(0); test_case<50,my_error,std::string>(90,100000);

    std::cout << std::endl;
    srand(0); test_case<100,my_error,int>(10,100000);
    srand(0); test_case<100,my_error,std::string>(10,100000);

    std::cout << std::endl;
    srand(0); test_case<100,my_error,int>(90,100000);
    srand(0); test_case<100,my_error,std::string>(90,100000);

    return 0;
}
