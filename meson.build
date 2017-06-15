# Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

project('noexcept','cpp',default_options : ['b_pch=false'])
compiler = meson.get_compiler('cpp')
compiler_id = compiler.get_id()

if not meson.is_subproject()
    if compiler_id=='clang'
        add_global_arguments(
            '-Wno-unused-local-typedefs',
            '-Wno-non-virtual-dtor',
            '-std=c++14',
            language:'cpp' )
    elif compiler_id=='gcc'
        add_global_arguments(
            '-Wno-unused-local-typedefs',
            '-Wno-non-virtual-dtor',
            '-std=c++17',
            language:'cpp' )
    elif compiler_id=='msvc'
    endif
endif

boost_thread=subproject('boost').get_variable('thread')
includes = include_directories('include')

test( 'any_movable_test',
    executable( 'any_movable_test',
        'test/any_movable_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'multiple_active_errors_test',
    executable( 'multiple_active_errors_test',
        'test/multiple_active_errors_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'error_handler_test',
    executable( 'error_handler_test',
        'test/error_handler_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'throw_test',
    executable( 'throw_test',
        'test/throw_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'throw_exception_test',
    executable( 'throw_exception_test',
        'test/throw_exception_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'throw_return_test',
    executable( 'throw_return_test',
        'test/throw_return_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'has_current_error_test',
    executable( 'has_current_error_test',
        'test/has_current_error_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'error_ptr_test',
    executable( 'error_ptr_test',
        'test/error_ptr_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'bad_alloc_test',
    executable( 'bad_alloc_test',
        'test/bad_alloc_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'error_info_test',
    executable( 'error_info_test',
        'test/error_info_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( '_rethrow_test',
    executable( '_rethrow_test',
        'test/_rethrow_test.cpp',
        dependencies: boost_thread,
        include_directories:includes),
    should_fail:true )

test( '_unhandled_error_test1',
    executable( '_unhandled_error_test1',
        'test/_unhandled_error_test1.cpp',
        dependencies: boost_thread,
        include_directories:includes),
    should_fail:true )

test( '_unhandled_error_test2',
    executable( '_unhandled_error_test2',
        'test/_unhandled_error_test2.cpp',
        dependencies: boost_thread,
        include_directories:includes),
    should_fail:true )

test( '_unhandled_error_test3',
    executable( '_unhandled_error_test3',
        'test/_unhandled_error_test3.cpp',
        dependencies: boost_thread,
        include_directories:includes),
    should_fail:true )

test( '_unhandled_error_test4',
    executable( '_unhandled_error_test4',
        'test/_unhandled_error_test4.cpp',
        dependencies: boost_thread,
        include_directories:includes),
    should_fail:true )

test( '_unhandled_error_test5',
    executable( '_unhandled_error_test5',
        'test/_unhandled_error_test5.cpp',
        dependencies: boost_thread,
        include_directories:includes),
    should_fail:true )

test( 'c_api_example',
    executable( 'c_api_example',
        'examples/c_api_example.cpp',
        dependencies: boost_thread,
        include_directories:includes ) )

test( 'FILE_ptr_example',
    executable( 'FILE_ptr_example',
        'examples/FILE_ptr_example.cpp',
        dependencies: boost_thread,
        include_directories:includes ) )

test( 'FILE_ptr_throw_example',
    executable( 'FILE_ptr_throw_example',
        'examples/FILE_ptr_throw_example.cpp',
        dependencies: boost_thread,
        include_directories:includes ) )
