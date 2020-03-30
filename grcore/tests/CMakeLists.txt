# !!! needs the setup done via ${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt !!!
if (NOT PACKAGE_TESTS)
    # Global Switch for testing is not enabled, bailing out
    return()
endif()

include(helpers)

# list of test files of the library
set(DbThingsFUCK_tests
        SimpleTest.cpp
        )

#set(TestTarget "TEST_${PROJECT_NAME}_SimpleTest")
#source_group(tests FILES SimpleTest.cpp)
#add_executable(${TestTarget} SimpleTest.cpp)
#target_link_libraries(${TestTarget} gtest::main)
#add_test(NAME ${TestTarget}_test COMMAND ${TestTarget})
add_gmain_test(SimpleTest SimpleTest.cpp)
add_gmain_test(Property Utility/Property.cpp)
#add_run_target(TEST_${PROJECT_NAME}_Property ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(FooTest SimpleTest.cpp)
target_link_libraries(FooTest  gtest::main)
gtest_add_tests(TARGET      FooTest
        TEST_SUFFIX .noArgs
        TEST_LIST   noArgsTests
        )


return()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(../../tests/googletest
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

add_executable(example SimpleTest.cpp)
target_link_libraries(example gtest_main)
add_test(NAME example_test COMMAND example)

# ToDo: FIX THE GLOBALS !!!
message(WARNING "PROJECT_NAME ${PROJECT_NAME}")
message(WARNING "GrCore ${${PROJECT_NAME}_VERSION}")
message(WARNING "gtest_VERSION ${${gtest_main}_VERSION}")
message(WARNING "gtest_VERSION ${gtest_VERSION}")
message(WARNING "gtest_main ${gtest_main}")


#message(FATAL_ERROR "CMAKE_PROJECT_NAME ${CMAKE_PROJECT_NAME}")

return()

if (${PROJECT_NAME}_BUILD_TESTS)
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
    if (NOT gtest_main)
#        message(FATAL_ERROR "Missing 'googletest' submodule! Either use 'git init submodule' and 'git update submodule' to get googletest according to the README, or deactivate unit tests with -D${PROJECT_NAME}_BUILD_TESTS=OFF")
    endif ()
    #add_subdirectory(googletest)
    #include_directories("${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include")

    # add the unit test executable
    add_executable(DbThingsFUCK_tests ${DbThingsFUCK_tests})
    #    target_link_libraries(DbThingsFUCK_tests gtest_main DbThings sqlite3)
    target_link_libraries(DbThingsFUCK_tests gtest_main sqlite3)
    # Link target with dl for linux
    if (UNIX AND NOT APPLE)
        target_link_libraries(DbThingsFUCK_tests dl)
    endif ()

    # add a "test" target:
    enable_testing()

    # does the tests pass?
    add_test(UnitTests ${CMAKE_BINARY_DIR}/bin/DbThingsFUCK_tests)

    if (DBTHINGS_BUILD_EXAMPLES)
        # does the example1 runs successfully?
        add_test(Example1Run DbThings_example1)
    endif (DBTHINGS_BUILD_EXAMPLES)
    message(STATUS "${PROJECT_NAME}_BUILD_TESTS ON")
else (${PROJECT_NAME}_BUILD_TESTS)
    message(STATUS "${PROJECT_NAME}_BUILD_TESTS OFF")
endif (${PROJECT_NAME}_BUILD_TESTS)






# the Compiler/IDE differences:
if (MSVC)
    set(CPPLINT_ARG_OUTPUT "--output=vs7")
    set(CPPCHECK_ARG_TEMPLATE "--template=vs")
    # disable Visual Studio warnings for fopen() used in the example
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    # Flags for linking with multithread static C++ runtime, required by googletest
    if (${PROJECT_NAME}_BUILD_TESTS)
        #message(STATUS "Linking against multithread static C++ runtime for unit tests with googletest")
        #set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} /MT")
        #set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} /MTd")
        #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        #set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    endif (${PROJECT_NAME}_BUILD_TESTS)
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



