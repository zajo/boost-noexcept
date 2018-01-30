//Copyright (c) 2017-2018 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/noexcept.hpp>
#include <boost/core/lightweight_test.hpp>
#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace boost::noexcept_;

struct compute_error { };

int
compute() noexcept
    {
    if( rand()%2 )
        return 42;
    else
        return throw_(compute_error());
    }

int
main()
    {
    std::vector<std::future<result<int> > > fut;
    std::generate_n( std::inserter(fut,fut.end()), 100, [ ]
        {
        std::packaged_task<result<int>()> task( [ ] { return try_(compute()); } );
        auto f=task.get_future();
        std::thread(std::move(task)).detach();
        return f;
        } );
    std::cout << "Results:\n";
    for( auto & f:fut )
        {
        f.wait();
        if( auto r=f.get() )
            std::cout << "Success! Answer=" << r.get() << '\n';
        else if( auto err=r.catch_<compute_error>() )
            std::cout << "Failure!\n";
        }
    return boost::report_errors();
    }
