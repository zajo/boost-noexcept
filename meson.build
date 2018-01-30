# Copyright (c) 2017-2018 Emil Dotchevski and Reverge Studios, Inc.

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

opt_throw=get_option('throw')
if opt_throw=='std'
    add_global_arguments( '-DBOOST_NOEXCEPT_THROW_EXCEPTION(x)=throw(x)', language:'cpp' )
elif opt_throw=='terminate'
    add_global_arguments( '-DBOOST_NOEXCEPT_THROW_EXCEPTOIN(x)=std::terminate()', language:'cpp' )
endif

opt_exception_info=get_option('exception_info')
if not opt_exception_info
    add_global_arguments( '-DBOOST_NOEXCEPT_NO_EXCEPTION_INFO', language:'cpp' )
endif

opt_rtti=get_option('rtti')
if opt_rtti=='off'
    add_global_arguments( '-DBOOST_NOEXCEPT_NO_RTTI', language:'cpp' )
endif

opt_tls=get_option('tls')
if opt_tls=='boost'
    add_global_arguments( '-DBOOST_NOEXCEPT_USE_BOOST_TSS', language:'cpp' )
    deps = declare_dependency( include_directories:include_directories('include'), dependencies: subproject('boost').get_variable('thread') )
else
    if opt_tls=='static'
        add_global_arguments( '-DBOOST_NOEXCEPT_NO_THREADS', language:'cpp' )
    endif
    deps = declare_dependency( include_directories:include_directories('include'), dependencies: subproject('boost').get_variable('headers') )
endif

lua=subproject('lua').get_variable('all')

executable( 'c_api_example',
    'examples/c_api_example.cpp',
    dependencies: deps )

executable( 'file_ptr_example',
    'examples/file_ptr_example.cpp',
    dependencies: deps )

executable( 'file_ptr_throw_example',
    'examples/file_ptr_throw_example.cpp',
    dependencies: deps )

executable( 'ifstream_example',
    'examples/ifstream_example.cpp',
    dependencies: deps )

executable( 'lua_example',
    'examples/lua_example.cpp',
    dependencies: [ deps, lua ] )

test( 'check_test',
    executable( 'check_test',
        'test/check_test.cpp',
        dependencies: deps ) )

if opt_exception_info
    test( 'error_info_test',
        executable( 'error_info_test',
            'test/error_info_test.cpp',
            dependencies: deps ) )
endif

test( 'diagnostic_information_test',
    executable( 'diagnostic_information_test',
        'test/diagnostic_information_test.cpp',
        dependencies: deps ) )

test( 'error_test',
    executable( 'error_test',
        'test/error_test.cpp',
        dependencies: deps ) )

test( 'result_test',
    executable( 'result_test',
        'test/result_test.cpp',
        dependencies: deps ) )

test( 'has_current_error_test',
    executable( 'has_current_error_test',
        'test/has_current_error_test.cpp',
        dependencies: deps ) )

test( 'multiple_active_errors_test',
    executable( 'multiple_active_errors_test',
        'test/multiple_active_errors_test.cpp',
        dependencies: deps ) )

test( 'result_mt_test',
    executable( 'result_mt_test',
        'test/result_mt_test.cpp',
        dependencies: deps ) )

test( 'throw_exception_test',
    executable( 'throw_exception_test',
        'test/throw_exception_test.cpp',
        dependencies: deps ) )

test( 'throw_return_test',
    executable( 'throw_return_test',
        'test/throw_return_test.cpp',
        dependencies: deps ) )

test( 'throw_test',
    executable( 'throw_test',
        'test/throw_test.cpp',
        dependencies: deps ) )

test( '_rethrow_test',
    executable( '_rethrow_test',
        'test/_rethrow_test.cpp',
        dependencies: deps ),
        should_fail: true )

test( '_unhandled_error_test1',
    executable( '_unhandled_error_test1',
        'test/_unhandled_error_test1.cpp',
        dependencies: deps ),
        should_fail: true )

test( '_unhandled_error_test2',
    executable( '_unhandled_error_test2',
        'test/_unhandled_error_test2.cpp',
        dependencies: deps ),
        should_fail: true )

test( '_unhandled_error_test3',
    executable( '_unhandled_error_test3',
        'test/_unhandled_error_test3.cpp',
        dependencies: deps ),
        should_fail: true )

test( '_unhandled_error_test4',
    executable( '_unhandled_error_test4',
        'test/_unhandled_error_test4.cpp',
        dependencies: deps ),
        should_fail: true )

test( '_unhandled_error_test5',
    executable( '_unhandled_error_test5',
        'test/_unhandled_error_test5.cpp',
        dependencies: deps ),
        should_fail: true )
