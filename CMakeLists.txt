cmake_minimum_required(VERSION 3.15)
project(OpenGLTemplate VERSION "0.0.1.1")

# included CMake scripts
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(versioning)

#set(USE_HEADERONLY_BOOST TRUE)
#set(USE_LIB_BOOST TRUE)
#set(BOOST_USED_COMPONENTS "program_options;filesystem")
include(setup)

# Build options
option(GrCore_BuildTests "Build GrCore unit tests" ON) #-DGrCore_BuildTests:BOOL=ON
option(GrCore_BuildBenchmarks "Build GrCore benchmarking" ON) #-DGrCore_BuildBenchmarks:BOOL=ON
option(ENABLE_PCH "Enable Precompiled Headers" ON) #-DENABLE_PCH:BOOL=ON

# require C++2A
set(CMAKE_CXX_STANDARD 20)
if (MSVC)
    add_definitions(/wd4800 /wd4251)
else ()
    # ToDo: Cleanup, belongs to users toolchain.cmake file
    #set(CMAKE_CXX_COMPILER "clang++") #-DCMAKE_CXX_COMPILER=clang++
    #set(CMAKE_TOOLCHAIN_PREFIX "llvm-")
endif ()

# CMake/Makefile Debugging
#set(CMAKE_VERBOSE_MAKEFILE ON) #-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON

# Include other projects
add_subdirectory(doc)
add_subdirectory(external)
add_subdirectory(grcore)
use_common_runtime_directory(GrCore)

# Tests
include(CTest)
#if(GrCore_BuildTests AND BUILD_TESTING)
enable_testing()
add_subdirectory(tests)
#endif()

# Benchmarks
if(GrCore_BuildBenchmarks)
    set(GTEST_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/lib/libgtestd.dll.a)
    set(GTEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/googletest/googletest/include ${CMAKE_CURRENT_SOURCE_DIR}/tests/googletest/googlemock/include)
    set(GTEST_MAIN_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/lib/libgtest_maind.dll.a)
    add_subdirectory(benchmark)
endif(GrCore_BuildBenchmarks)

message("GrCore_VERSION: '${GrCore_VERSION}'")

# Set global property (all targets are impacted)
#set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "\"${CMAKE_COMMAND}\" -E time")
# Set property for my_target only
#set_property(TARGET my_target PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

add_subdirectory(playground)

