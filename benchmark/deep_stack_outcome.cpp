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

#include <boost/outcome/result.hpp>
#include <boost/config.hpp>
#include <chrono>
#include <string>
#include <iostream>
#include <stdlib.h>

#ifndef BOOST_NO_EXCEPTIONS
#error Disable exception handling for correct benchmark results
#endif

#ifndef BOOST_NOEXCEPT_INLINE_FORCEINLINE
#   if defined(_MSC_VER)
#       define BOOST_NOEXCEPT_INLINE_FORCEINLINE __forceinline
#   elif (defined(__GNUC__) && __GNUC__>3) || defined(__SNC__)
#       define BOOST_NOEXCEPT_INLINE_FORCEINLINE inline __attribute__ ((always_inline))
#   else
#       define BOOST_NOEXCEPT_INLINE_FORCEINLINE inline
#   endif
#endif

#ifndef BOOST_NOEXCEPT_INLINE_NOINLINE
#   if defined(_MSC_VER)
#       define BOOST_NOEXCEPT_INLINE_NOINLINE __declspec(noinline)
#   elif (defined(__GNUC__) && __GNUC__>3) || defined(__SNC__)
#       define BOOST_NOEXCEPT_INLINE_NOINLINE inline __attribute__ ((noinline))
#   else
#       define BOOST_NOEXCEPT_INLINE_NOINLINE inline
#   endif
#endif

#ifndef BOOST_NOEXCEPT_INLINE
#define BOOST_NOEXCEPT_INLINE inline
#endif

#ifndef BOOST_NOEXCEPT_INLINE_TRIVIAL
#define BOOST_NOEXCEPT_INLINE_TRIVIAL BOOST_NOEXCEPT_FORCEINLINE
#endif

#ifndef BOOST_NOEXCEPT_INLINE_CRITICAL
#define BOOST_NOEXCEPT_INLINE_CRITICAL BOOST_NOEXCEPT_FORCEINLINE
#endif

#ifndef BOOST_NOEXCEPT_INLINE_OPERATIONS
#define BOOST_NOEXCEPT_INLINE_OPERATIONS BOOST_NOEXCEPT_INLINE
#endif

#ifndef BOOST_NOEXCEPT_INLINE_RECURSION
#define BOOST_NOEXCEPT_INLINE_RECURSION BOOST_NOEXCEPT_INLINE_OPERATIONS
#endif

#ifndef BENCHMARK_INLINE
#define BENCHMARK_INLINE BOOST_NOEXCEPT_INLINE_NOINLINE
#endif

namespace outcome = BOOST_OUTCOME_V2_NAMESPACE;

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
    outcome::result<ValueType,ErrorType> test_function( int success_percentage  )
    {
        return benchmark<Depth-1,ErrorType,ValueType>::test_function(success_percentage);
    }
};

template <class ErrorType, class ValueType>
struct benchmark<0,ErrorType,ValueType>
{
    static BENCHMARK_INLINE
    outcome::result<ValueType,ErrorType> test_function( int success_percentage  )
    {
        if( (rand()%100) > success_percentage )
            return ErrorType();
        else
            return compute_value<ValueType>();
    }
};

/////////////////////////////////////////////

template <int Depth,class ErrorType, class ValueType>
void test_case( int success_percentage, int count )
{
    auto start = std::chrono::steady_clock::now();

    for( int i=0; i!=count; ++i )
        if( auto r = benchmark<Depth,ErrorType,ValueType>::test_function(success_percentage) )
            ;
        else
            (void) r.error();

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
    std::cout << "Using Outcome" << std::endl;

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
