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
            '-Wno-dangling-else',
            '-std=c++11',
            language:'cpp' )
    elif compiler_id=='gcc'
        add_global_arguments(
            '-Wno-unused-local-typedefs',
            '-Wno-non-virtual-dtor',
            '-std=c++11',
            language:'cpp' )
    elif compiler_id=='msvc'
    endif
endif

lua=subproject('lua').get_variable('all')
boost_thread=subproject('boost').get_variable('thread')
includes = include_directories('include')

executable( 'c_api_example',
    'examples/c_api_example.cpp',
    dependencies: boost_thread,
    include_directories:includes )

executable( 'file_ptr_example',
    'examples/file_ptr_example.cpp',
    dependencies: boost_thread,
    include_directories:includes )

executable( 'file_ptr_throw_example',
    'examples/file_ptr_throw_example.cpp',
    dependencies: boost_thread,
    include_directories:includes )

executable( 'ifstream_example',
    'examples/ifstream_example.cpp',
    dependencies: boost_thread,
    include_directories:includes )

executable( 'lua_example',
    'examples/lua_example.cpp',
    dependencies: [ boost_thread, lua ],
    include_directories:includes )

test( 'bad_alloc_test',
    executable( 'bad_alloc_test',
        'test/bad_alloc_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'check_test',
    executable( 'check_test',
        'test/check_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'error_info_test',
    executable( 'error_info_test',
        'test/error_info_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'diagnostic_information_test',
    executable( 'diagnostic_information_test',
        'test/diagnostic_information_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'error_test',
    executable( 'error_test',
        'test/error_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'error_test_no_exception_info',
    executable( 'error_test_no_exception_info',
        'test/error_test.cpp',
        dependencies: boost_thread,
        include_directories:includes,
        cpp_args: [ '-DBOOST_NOEXCEPT_NO_EXCEPTION_INFO' ] ) )

test( 'handler_test',
    executable( 'handler_test',
        'test/handler_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'has_current_error_test',
    executable( 'has_current_error_test',
        'test/has_current_error_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'multiple_active_errors_test',
    executable( 'multiple_active_errors_test',
        'test/multiple_active_errors_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'result_test',
    executable( 'result_test',
        'test/result_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( 'result_mt_test',
    executable( 'result_mt_test',
        'test/result_mt_test.cpp',
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

test( 'throw_test',
    executable( 'throw_test',
        'test/throw_test.cpp',
        dependencies: boost_thread,
        include_directories:includes) )

test( '_rethrow_test',
    executable( '_rethrow_test',
        'test/_rethrow_test.cpp',
        dependencies: boost_thread,
        include_directories:includes), should_fail: true )

test( '_unhandled_error_test1',
    executable( '_unhandled_error_test1',
        'test/_unhandled_error_test1.cpp',
        dependencies: boost_thread,
        include_directories:includes), should_fail: true )

test( '_unhandled_error_test2',
    executable( '_unhandled_error_test2',
        'test/_unhandled_error_test2.cpp',
        dependencies: boost_thread,
        include_directories:includes), should_fail: true )

test( '_unhandled_error_test3',
    executable( '_unhandled_error_test3',
        'test/_unhandled_error_test3.cpp',
        dependencies: boost_thread,
        include_directories:includes), should_fail: true )

test( '_unhandled_error_test4',
    executable( '_unhandled_error_test4',
        'test/_unhandled_error_test4.cpp',
        dependencies: boost_thread,
        include_directories:includes), should_fail: true )

test( '_unhandled_error_test5',
    executable( '_unhandled_error_test5',
        'test/_unhandled_error_test5.cpp',
        dependencies: boost_thread,
        include_directories:includes), should_fail: true )

test( '_unhandled_error_test6',
    executable( '_unhandled_error_test6',
        'test/_unhandled_error_test6.cpp',
        dependencies: boost_thread,
        include_directories:includes), should_fail: true )
