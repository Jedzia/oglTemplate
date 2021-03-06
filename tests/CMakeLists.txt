#cmake_minimum_required(VERSION 3.2)

if (PACKAGE_TESTS)
    enable_testing()
    #include(googletest)
    add_subdirectory(googletest)

    set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest CACHE INTERNAL "" FORCE)
    include(GoogleTest)

    set(GTEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)
    set(GMOCK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include)
    set(GTEST_MAIN_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/lib/libgtest_maind.dll.a)

    #add_library(gtest INTERFACE)
    #target_include_directories(gtest INTERFACE ${GTEST_INCLUDE_DIR})
    add_library(gtest::gtest ALIAS gtest)


    #target_include_directories(gmock INTERFACE ${GMOCK_INCLUDE_DIR})
    add_library(gtest::gmock ALIAS gmock)

    add_library(gtest::main ALIAS gtest_main)

    #find_package(GTest )


    function(add_gmain_test _name _source_files)
        set(TestTarget "TESTS_${PROJECT_NAME}_${_name}")
        source_group(tests FILES ${_source_files})
        add_executable(${TestTarget} ${_source_files})
        target_link_libraries(${TestTarget} PRIVATE gtest::main ${ARGN})
        target_link_libraries(${TestTarget} PRIVATE project_options project_warnings)
        add_test(NAME ${TestTarget} COMMAND ${TestTarget})
    endfunction()

endif ()


# ToDo: Clean UP THIS MESS
return()

# this directory can later hold global tests, integration, fuzzing ... i dont know


option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
#add_subdirectory(googletest)
#message(FATAL_ERROR "FUCK YOU ${gtest_main_VERSION}")

# list of test files of the library
set(DBTHINGS_TESTS
        SimpleTest.cpp
        )
source_group(tests FILES ${DBTHINGS_TESTS})

# ToDo: FIX THE GLOBALS !!!

# then Compiler/IDE differences:
if (MSVC)
    set(CPPLINT_ARG_OUTPUT "--output=vs7")
    set(CPPCHECK_ARG_TEMPLATE "--template=vs")
    # disable Visual Studio warnings for fopen() used in the example
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    # Flags for linking with multithread static C++ runtime, required by googletest
    if (DBTHINGS_BUILD_TESTS)
        #message(STATUS "Linking against multithread static C++ runtime for unit tests with googletest")
        #set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} /MT")
        #set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} /MTd")
        #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        #set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    endif (DBTHINGS_BUILD_TESTS)
else (MSVC)
    set(CPPLINT_ARG_OUTPUT "--output=eclipse")
    set(CPPCHECK_ARG_TEMPLATE "--template=gcc")
    # Useful compile flags and extra warnings
    #    add_compile_options(-fstack-protector -Wall -Wextra -Wpedantic -Wno-long-long -Wswitch-enum -Wshadow -Winline)
    #add_compile_options(-Wall -Wextra -Wpedantic -Wno-long-long -Wswitch-enum -Wshadow -Winline)
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-long-long -Wswitch-enum -Wshadow)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++0x-compat") # C++ only
    if (CMAKE_COMPILER_IS_GNUCXX)
        # GCC flags
        if (DBTHINGS_USE_GCOV AND CMAKE_COMPILER_IS_GNUCXX)
            if (CMAKE_BUILD_TYPE STREQUAL "Debug")
                message(STATUS "Using GCov instrumentation")
            else ()
                message(WARNING "GCov instrumentation works best in Debug mode")
            endif ()
            add_compile_options(-coverage) # NOTE would be usefull but not working with current google test and gcc 4.8 -fkeep-inline-functions
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage")
        endif ()
    endif (CMAKE_COMPILER_IS_GNUCXX)
endif (MSVC)


option(DBTHINGS_BUILD_TESTS "Build and run tests." ON)
if (DBTHINGS_BUILD_TESTS)
    option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)
    #include(CMakeDependentOption)
    #include(GNUInstallDirs)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    # deactivate some warnings for compiling the gtest library
    if (NOT MSVC)
        add_compile_options(-Wno-variadic-macros -Wno-long-long -Wno-switch-enum -Wno-float-equal -Wno-conversion-null -Wno-switch-default -Wno-pedantic)
    endif (NOT MSVC)

    # add the subdirectory containing the CMakeLists.txt for the gtest library
    # TODO: under Linux, uses libgtest-dev if found
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/googletest/CMakeLists.txt")
        message(FATAL_ERROR "Missing 'googletest' submodule! Either use 'git init submodule' and 'git update submodule' to get googletest according to the README, or deactivate unit tests with -DDBTHINGS_BUILD_TESTS=OFF")
    endif ()
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include")

    # add the unit test executable
    add_executable(DbThings_tests ${DBTHINGS_TESTS})
    #    target_link_libraries(DbThings_tests gtest_main DbThings sqlite3)
    target_link_libraries(DbThings_tests gtest_main sqlite3)
    # Link target with dl for linux
    if (UNIX AND NOT APPLE)
        target_link_libraries(DbThings_tests dl)
    endif ()

    # add a "test" target:
    enable_testing()

    # does the tests pass?
    add_test(UnitTests ${CMAKE_BINARY_DIR}/bin/DbThings_tests)

    if (DBTHINGS_BUILD_EXAMPLES)
        # does the example1 runs successfully?
        add_test(Example1Run DbThings_example1)
    endif (DBTHINGS_BUILD_EXAMPLES)
    message(STATUS "DBTHINGS_BUILD_TESTS ON")
else (DBTHINGS_BUILD_TESTS)
    message(STATUS "DBTHINGS_BUILD_TESTS OFF")
endif (DBTHINGS_BUILD_TESTS)







