cmake_minimum_required( VERSION 3.2 ) 

if( NOT DEFINED build_type )
    set ( build_type "debug" )
endif()

if( NOT DEFINED dimwits_build_type )
    set( dimwits_build_type "${build_type}" )
endif()

if( NOT DEFINED static_libraries )
    set( build_static_libraries FALSE )
else()
    set( build_static_libraries TRUE )
endif()

project( dimwits VERSION 0.0.1 LANGUAGES CXX )

if( NOT DEFINED is_subproject )
    set( is_subproject )
    add_subdirectory( subprojects/catch-adapter )
    add_subdirectory( subprojects/hana-adapter )
    unset( is_subproject )
endif()

if( NOT DEFINED is_subproject )
    if( DEFINED CXX_compiler_flags )
        if( ( NOT DEFINED dimwits_compiler_flags ) AND ( NOT DEFINED dimwits_use_default_compiler_flags ) )
            set( dimwits_compiler_flags "${CXX_compiler_flags}" )
        endif()
    endif()
    if( NOT DEFINED dimwits_compiler_flags )
        if( DEFINED no_link_time_optimization )
            set( no_link_time_optimization TRUE )
        endif()
        if( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
            if( ${dimwits_build_type} STREQUAL "debug" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -g -gdwarf-3 -std=c++14" )
            elseif( ${dimwits_build_type} STREQUAL "coverage" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -g -gdwarf-3 -fprofile-arcs -ftest-coverage -fno-inline -std=c++14" )
            elseif( ${dimwits_build_type} STREQUAL "release" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -O3 -DNDEBUG -std=c++14" )
                if( NOT DEFINED no_link_time_optimization )
                    set( dimwits_compiler_flags "${dimwits_compiler_flags} -flto" )
                endif()
            elseif( ${dimwits_build_type} STREQUAL "native" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -O3 -DNDEBUG -march=native -std=c++14" )
                if( NOT DEFINED no_link_time_optimization )
                    set( dimwits_compiler_flags "${dimwits_compiler_flags} -flto" )
                endif()
            endif()
        elseif( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
            if( ${dimwits_build_type} STREQUAL "debug" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -g -gdwarf-3 -std=c++14" )
            elseif( ${dimwits_build_type} STREQUAL "coverage" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -g -gdwarf-3 -fprofile-arcs -ftest-coverage -fno-inline -std=c++14" )
            elseif( ${dimwits_build_type} STREQUAL "release" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -O3 -DNDEBUG -std=c++14" )
                if( NOT DEFINED no_link_time_optimization )
                    set( dimwits_compiler_flags "${dimwits_compiler_flags} -flto" )
                endif()
            elseif( ${dimwits_build_type} STREQUAL "native" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -O3 -DNDEBUG -march=native -std=c++14" )
                if( NOT DEFINED no_link_time_optimization )
                    set( dimwits_compiler_flags "${dimwits_compiler_flags} -flto" )
                endif()
            endif()
        elseif( CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" )
            if( ${dimwits_build_type} STREQUAL "debug" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -g -gdwarf-3 -std=c++14" )
            elseif( ${dimwits_build_type} STREQUAL "coverage" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -g -gdwarf-3 -fprofile-arcs -ftest-coverage -fno-inline -std=c++14" )
            elseif( ${dimwits_build_type} STREQUAL "release" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -O3 -DNDEBUG -std=c++14" )
                if( NOT DEFINED no_link_time_optimization )
                    set( dimwits_compiler_flags "${dimwits_compiler_flags} -flto" )
                endif()
            elseif( ${dimwits_build_type} STREQUAL "native" )
                set( dimwits_compiler_flags "-Wall -Wextra -Wpedantic -Werror -O3 -DNDEBUG -march=native -std=c++14" )
                if( NOT DEFINED no_link_time_optimization )
                    set( dimwits_compiler_flags "${dimwits_compiler_flags} -flto" )
                endif()
            endif()
        else()
            message( WARNING "Compiler vendor not recognized. No compilation flags set" )
        endif()
    endif()
    if( DEFINED appended_flags AND NOT dimwits_no_appended_flags )
        set( dimwits_compiler_flags "${dimwits_compiler_flags} ${appended_flags}" )
    endif()
    if( DEFINED dimwits_appended_flags )
        set( dimwits_compiler_flags "${dimwits_compiler_flags} ${dimwits_appended_flags}" )
    endif()
endif()

execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message( STATUS "" )
message( STATUS "-----------------------------------------------------------" )
message( STATUS "" )
message( STATUS "dimwits Version: 0.0.1" )
message( STATUS "Git current branch: ${GIT_BRANCH}" )
message( STATUS "Git commit hash: ${GIT_HASH}" )
message( STATUS "" )
if( NOT DEFINED is_subproject ) 
    message( STATUS "dimwits flags: ${dimwits_compiler_flags}" ) 
    message( STATUS "" ) 
endif() 
message( STATUS "-----------------------------------------------------------" ) 
message( STATUS "" ) 

add_library( dimwits INTERFACE )
target_include_directories( dimwits INTERFACE src )
target_link_libraries( dimwits INTERFACE catch-adapter INTERFACE hana-adapter ) 

if( NOT DEFINED is_subproject ) 
    enable_testing() 
    add_subdirectory( src/dimwits/conversion/test ) 
    add_subdirectory( src/dimwits/scale/test ) 
    add_subdirectory( src/dimwits/quantity/test ) 
    add_subdirectory( src/dimwits/dimension/test ) 
    add_subdirectory( src/dimwits/unit/test ) 
    add_subdirectory( src/dimwits/ratio/test ) 
    add_subdirectory( src/dimwits/basis/test ) 
endif() 