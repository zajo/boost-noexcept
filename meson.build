# Copyright (c) 2017 Emil Dotchevski and Reverge Studios, Inc.

# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

project('noexcept','cpp',default_options : ['b_pch=false'])
compiler = meson.get_compiler('cpp')
compiler_id = compiler.get_id()

if not meson.is_subproject()
	if compiler_id=='clang'
	elif compiler_id=='gcc'
		add_global_arguments(
			'-Wno-unused-local-typedefs',
			'-Wno-non-virtual-dtor',
			'-std=c++17',
			language:'cpp' )
	elif compiler_id=='msvc'
	endif
endif
add_global_arguments('-DBOOST_NOEXCEPT_USE_STD_OPTIONAL', language:'cpp')
add_global_arguments('-DBOOST_NOEXCEPT_NO_THREADS', language:'cpp')

includes = include_directories('include','../..')

test( 'c_function_example',
	executable( 'c_function_example',
		'examples/c_function_example.cpp',
		include_directories:includes ) )

test( 'multiple_active_errors_test',
	executable( 'multiple_active_errors_test',
		'test/multiple_active_errors_test.cpp',
		include_directories:includes) )

test( 'propagate_test',
	executable( 'propagate_test',
		'test/propagate_test.cpp',
		include_directories:includes) )

test( 'propagate_error_code_test',
	executable( 'propagate_error_code_test',
		'test/propagate_error_code_test.cpp',
		include_directories:includes) )

test( 'throw_exception_test',
	executable( 'throw_exception_test',
		'test/throw_exception_test.cpp',
		include_directories:includes) )

test( '_unhandled_error_test1',
	executable( '_unhandled_error_test1',
		'test/_unhandled_error_test1.cpp',
		include_directories:includes),
	should_fail:true )

test( '_unhandled_error_test2',
	executable( '_unhandled_error_test2',
		'test/_unhandled_error_test2.cpp',
		include_directories:includes),
	should_fail:true )

test( '_unhandled_error_test3',
	executable( '_unhandled_error_test3',
		'test/_unhandled_error_test3.cpp',
		include_directories:includes),
	should_fail:true )

test( 'exception_holder_test',
	executable( 'exception_holder_test',
		'test/exception_holder_test.cpp',
		include_directories:includes) )
