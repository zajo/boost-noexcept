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
#include <system_error>
#include <iostream>
#include <stdlib.h>

#ifndef BENCHMARK_INLINE
#define BENCHMARK_INLINE BOOST_NOEXCEPT_INLINE_NOINLINE
#endif

namespace noexcept_ = boost::noexcept_;

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

template <class E>
BOOST_NOEXCEPT_INLINE_FORCEINLINE
E construct_error()
{
    return E();
}

template <>
BOOST_NOEXCEPT_INLINE_FORCEINLINE
std::error_code construct_error<std::error_code>()
{
    return std::error_code{42,std::system_category()};
}

template <class T,class Error>
BOOST_NOEXCEPT_INLINE_FORCEINLINE
T return_error( Error && e )
{
#ifdef BOOST_NO_EXCEPTIONS
    return noexcept_::throw_(e);
#else
    throw e;
#endif
}

/////////////////////////////////////////////

template <class ValueType, class ErrorType, int Depth>
struct benchmark
{
    static BENCHMARK_INLINE
    ValueType test_function( int success_percentage  )
    {
        return benchmark<ValueType,ErrorType,Depth-1>::test_function(success_percentage);
    }
};

template <class ValueType, class ErrorType>
struct benchmark<ValueType,ErrorType,0>
{
    static BENCHMARK_INLINE
    ValueType test_function( int success_percentage  )
    {
        if( (rand()%100) > success_percentage )
            return return_error<ValueType>(construct_error<ErrorType>());
        else
            return compute_value<ValueType>();
    }
};

/////////////////////////////////////////////

template <class ValueType, class ErrorType, int Depth>
void test_case( int success_percentage, int count )
{
    auto start = std::chrono::steady_clock::now();

#ifdef BOOST_NO_EXCEPTIONS
    for( int i=0; i!=count; ++i )
        if( auto r = noexcept_::try_(benchmark<ValueType,ErrorType,Depth>::test_function(success_percentage)) )
            ;
        else
            (void) r.template catch_<ErrorType>();
#else
    for( int i=0; i!=count; ++i )
        try
        {
            benchmark<ValueType,ErrorType,Depth>::test_function(success_percentage);
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

int main( int argc, char const * argv[ ] )
{
#ifdef BOOST_NO_EXCEPTIONS
    std::cout << "Using Noexcept" << std::endl;
#else
    std::cout << "Using C++ exception handling" << std::endl;
#endif

    std::cout << std::endl;
    srand(0); test_case<int,int,50>(10,100000);
    srand(0); test_case<int,std::error_code,50>(10,100000);
    srand(0); test_case<std::string,int,50>(10,100000);
    srand(0); test_case<std::string,std::error_code,50>(10,100000);

    std::cout << std::endl;
    srand(0); test_case<int,int,50>(90,100000);
    srand(0); test_case<int,std::error_code,50>(90,100000);
    srand(0); test_case<std::string,int,50>(90,100000);
    srand(0); test_case<std::string,std::error_code,50>(90,100000);

    std::cout << std::endl;
    srand(0); test_case<int,int,100>(10,100000);
    srand(0); test_case<int,std::error_code,100>(10,100000);
    srand(0); test_case<std::string,int,100>(10,100000);
    srand(0); test_case<std::string,std::error_code,100>(10,100000);

    std::cout << std::endl;
    srand(0); test_case<int,int,100>(90,100000);
    srand(0); test_case<int,std::error_code,100>(90,100000);
    srand(0); test_case<std::string,int,100>(90,100000);
    srand(0); test_case<std::string,std::error_code,100>(90,100000);

    return 0;
}
