cmake_minimum_required(VERSION 3.15)

# Set the project name
project(OpenGLTemplate VERSION "0.0.1.1")

# included CMake scripts
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(versioning)
include(StandardProjectSettings)

# Setup Boost, etc.
#set(USE_HEADERONLY_BOOST TRUE)
#set(USE_LIB_BOOST TRUE)
#set(BOOST_USED_COMPONENTS "program_options;filesystem")
include(setup)

# Build options
option(GrCore_BuildTests "Build GrCore unit tests" ON) #-DGrCore_BuildTests:BOOL=ON
option(GrCore_BuildBenchmarks "Build GrCore benchmarking" ON) #-DGrCore_BuildBenchmarks:BOOL=ON
option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF) #-DBUILD_SHARED_LIBS_PCH:BOOL=OFF
option(ENABLE_PCH "Enable Precompiled Headers" ON) #-DENABLE_PCH:BOOL=ON

# Keep compiled binaries central
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Not needed, is done on a project level #require C++2A
# set(CMAKE_CXX_STANDARD 20)
if (MSVC)
    add_definitions(/wd4800 /wd4251)
else ()
    # ToDo: Cleanup, belongs to users toolchain.cmake file
    #set(CMAKE_CXX_COMPILER "clang++") #-DCMAKE_CXX_COMPILER=clang++
    #set(CMAKE_TOOLCHAIN_PREFIX "llvm-")
endif ()

# # ************************************************************************* # #
# as of https://github.com/lefticus/cpp_starter_project
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
# standard compiler warnings
include(config/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()


# ------------------------------------------------------------------------- #
# CMake/Makefile Debugging
#set(CMAKE_VERBOSE_MAKEFILE ON) #-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON


# ************************************************************************* #
# Include other projects
add_subdirectory(doc)
# external libraries
add_subdirectory(external)
# own libraries
add_subdirectory(grcore)
use_common_runtime_directory(GrCore)
add_subdirectory(grgraphics)
use_common_runtime_directory(GrGraphics)

# ------------------------------------------------------------------------- #
# Tests
include(CTest)
#if(GrCore_BuildTests AND BUILD_TESTING)
enable_testing()
add_subdirectory(tests)
#endif()

# ------------------------------------------------------------------------- #
# Benchmarks
if (GrCore_BuildBenchmarks)
    set(GTEST_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/lib/libgtestd.dll.a)
    set(GTEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/googletest/googletest/include ${CMAKE_CURRENT_SOURCE_DIR}/tests/googletest/googlemock/include)
    set(GTEST_MAIN_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/lib/libgtest_maind.dll.a)
    add_subdirectory(benchmark)
endif (GrCore_BuildBenchmarks)

message("GrCore_VERSION: '${GrCore_VERSION}'")

# Set global property (all targets are impacted)
#set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "\"${CMAKE_COMMAND}\" -E time")
# Set property for my_target only
#set_property(TARGET my_target PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

# Include the Playground
add_subdirectory(playground)

# Include the main application
add_subdirectory(src)
