
# s. E:\Projects\C++\Playground\projects\Playground\CMakeLists.txt for globbing
#add_executable(simple_main hello.cpp)


# playground single source files
SET(PLAYGROUND_CPP_FILES *.cpp)
SET(PLAYGROUND_HPP_FILES *.h)
SET(PLAYGROUND_MOC_FILES moc_*.cpp)

FILE(GLOB playground_sources ${CMAKE_CURRENT_SOURCE_DIR}/${PLAYGROUND_CPP_FILES})
FILE(GLOB playground_headers ${CMAKE_CURRENT_SOURCE_DIR}/${PLAYGROUND_HPP_FILES})

#LIST(REMOVE_ITEM playground_sources ${TOP_SRC_DIR}/src/insets/InsetTheorem.cpp)
#MESSAGE(STATUS "[GLOB] Files: ${playground_sources}")
INCLUDE_DIRECTORIES()

FOREACH (f ${playground_sources})
    GET_FILENAME_COMPONENT(_target_name ${f} NAME_WE)
    IF (${_target_name} STREQUAL "stdafx")
    ELSE (${_target_name} STREQUAL "stdafx")
        set(_target_name "Playground_GrCore_${_target_name}")
        ADD_EXECUTABLE(${_target_name} ${f})
        #target_link_libraries(${_target_name} GrCore)
        #target_include_directories(${BENCHMARK_RUNNER_NAME} PRIVATE include)
        target_link_libraries(${_target_name}
                PRIVATE project_options project_warnings
                #INTERFACE spdlog::spdlog
                PRIVATE fmt::fmt
                #        CONAN_PKG::docopt.cpp
                #        CONAN_PKG::fmt CONAN_PKG::spdlog
                )
        target_include_and_link_boost_libraries(${_target_name}
                #        "GrCore;fmt::fmt-header-only"
                "GrCore"
                "Boost::program_options;Boost::filesystem"
                )
        #        TargetLinkBoost(${_target_name} "filesystem;system;regex;thread;date_time;chrono")
        #SET_PROPERTY(TARGET throw_error PROPERTY FOLDER "Playground/3rdParty")
        SET_PROPERTY(TARGET ${_target_name} PROPERTY FOLDER "Playground")

        SET_TARGET_PROPERTIES(${_target_name}
                PROPERTIES
                #		EXCLUDE_FROM_DEFAULT_BUILD
                EXCLUDE_FROM_ALL_BUILD
                TRUE)
        MESSAGE(STATUS "[GLOB EXAMPLE] Adding Example Project: ${_target_name}")
    ENDIF (${_target_name} STREQUAL "stdafx")
ENDFOREACH ()
