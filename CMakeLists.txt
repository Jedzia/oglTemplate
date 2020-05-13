cmake_minimum_required(VERSION 3.15)

# Set the project name
project(OpenGLTemplate VERSION "0.0.1.1")

# ------------------------------------------------------------------------- #
# CMake/Makefile Debugging
#set(CMAKE_VERBOSE_MAKEFILE ON) #-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON

# ------------------------------------------------------------------------- #
# included CMake scripts
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(versioning)
include(StandardProjectSettings)

# Build options
option(PACKAGE_TESTS "Build all unit tests" ON) # -DPACKAGE_TESTS:BOOL=ON
option(ENABLE_FUZZING "Build fuzzer testing" OFF) # -DENABLE_FUZZING:BOOL=OFF
option(GrCore_BuildBenchmarks "Build GrCore benchmarking" ON) # -DGrCore_BuildBenchmarks:BOOL=ON
option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF) # -DBUILD_SHARED_LIBS_PCH:BOOL=OFF
option(ENABLE_PCH "Enable Precompiled Headers" ON) # -DENABLE_PCH:BOOL=ON
# Unity is currently enabled as separate target via cotire. But this works, too.
option(ENABLE_UNITY "Enable Unity builds of projects" OFF) # -DENABLE_UNITY:BOOL=ON

#add_definitions(-DUSE_SPDLOG)
# Setup Boost, etc.
#set(USE_HEADERONLY_BOOST TRUE)
#set(USE_LIB_BOOST TRUE)
#set(BOOST_USED_COMPONENTS "program_options;filesystem")
include(setup)

# Keep compiled binaries central
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# require C++2A, ToDo: should be done on a project level with target_xyz(...)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # ************************************************************************* # #
# as of https://github.com/lefticus/cpp_starter_project
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)
if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if (ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif ()
endif ()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
# standard compiler warnings
include(CMake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(CMake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(CMake/StaticAnalyzers.cmake)

# enable doxygen
include(CMake/Doxygen.cmake)
enable_doxygen()

# Conan, disabled here.
# # Set up some extra Conan dependencies based on our needs
# # before loading Conan
# set(CONAN_EXTRA_REQUIRES "")
# set(CONAN_EXTRA_OPTIONS "")
#
# if(CPP_STARTER_USE_IMGUI)
#     set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES}
#             imgui-sfml/2.1@bincrafters/stable)
#
#     # set(CONAN_EXTRA_OPTIONS ${CONAN_EXTRA_OPTIONS} sfml:shared=False
#     # sfml:graphics=True sfml:audio=False sfml:window=True
#     # libalsa:disable_python=True)
# endif()
#
# if(CPP_STARTER_USE_SDL)
#     set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES}
#             sdl2/2.0.10@bincrafters/stable)
#     # set(CONAN_EXTRA_OPTIONS ${CONAN_EXTRA_OPTIONS} sdl2:wayland=True)
# endif()
#
# include(cmake/Conan.cmake)
# run_conan()

# ------------------------------------------------------------------------- #
# Test setup and global tests
if (PACKAGE_TESTS)
    message(
            "Building Tests. Be sure to check out test/constexpr_tests for constexpr testing"
    )
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif ()

if (ENABLE_FUZZING)
    message(
            "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html"
    )
    add_subdirectory(fuzz_test)
endif ()

# ************************************************************************* #
# Include documentation generator
add_subdirectory(doc)
# external libraries
add_subdirectory(external)
# own libraries
add_subdirectory(grcore)
use_common_runtime_directory(GrCore)
add_subdirectory(grgraphics)
use_common_runtime_directory(GrGraphics)


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
