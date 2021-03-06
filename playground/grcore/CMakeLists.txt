
# s. E:\Projects\C++\Playground\projects\Playground\CMakeLists.txt for globbing
#add_executable(simple_main hello.cpp)


# playground single source files
set(PLAYGROUND_CPP_FILES *.cpp)
set(PLAYGROUND_HPP_FILES *.h)
set(PLAYGROUND_MOC_FILES moc_*.cpp)

file(GLOB playground_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PLAYGROUND_CPP_FILES})
file(GLOB playground_headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PLAYGROUND_HPP_FILES})

#LIST(REMOVE_ITEM playground_sources ${TOP_SRC_DIR}/src/insets/InsetTheorem.cpp)
#MESSAGE(STATUS "[GLOB] Files: ${playground_sources}")
include_directories()

foreach (f ${playground_sources})
    get_filename_component(_target_name ${f} NAME_WE)
    if (${_target_name} STREQUAL "stdafx")
    else (${_target_name} STREQUAL "stdafx")
        set(_target_name "Playground_GrCore_${_target_name}")
        add_executable(${_target_name} ${f})
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
        set_property(TARGET ${_target_name} PROPERTY FOLDER "Playground")

        set_target_properties(${_target_name}
                PROPERTIES
                #		EXCLUDE_FROM_DEFAULT_BUILD
                EXCLUDE_FROM_ALL_BUILD
                TRUE)
        add_run_target(${_target_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        message(STATUS "[GLOB EXAMPLE] Adding Example Project: ${_target_name}")
    endif (${_target_name} STREQUAL "stdafx")
endforeach ()

target_link_libraries(Playground_GrCore_statemachine02 PRIVATE afsm::afsm)
#target_include_directories(Playground_GrCore_statemachine02 PRIVATE ${AFSM_INCLUDE_DIRS})
#message(FATAL_ERROR "AFSM_INCLUDE_DIRS ${AFSM_INCLUDE_DIRS}")
