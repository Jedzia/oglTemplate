project(GrCoreBench VERSION "${OpenGLTemplate_VERSION}")
### list of source files of the GrCore executable
configure_file(src/win/GrCoreBench.rc.in ${CMAKE_CURRENT_BINARY_DIR}/src/win/GrCoreBench.rc @ONLY)
set(GRCORE_SRC_FILES "src/main.cpp")
set(BENCHMARK_RUNNER_NAME ${PROJECT_NAME})
add_executable_with_resource(${BENCHMARK_RUNNER_NAME}
        "${GRCORE_SRC_FILES}"
        "${CMAKE_CURRENT_BINARY_DIR}/src/win/GrCoreBench.rc")

target_include_directories(${BENCHMARK_RUNNER_NAME} PRIVATE include)
target_include_and_link_boost_libraries(${BENCHMARK_RUNNER_NAME}
#        "GrCore;fmt::fmt-header-only"
        "GrCore;fmt::fmt"
        "Boost::program_options;Boost::filesystem")
set_target_version_properties(${BENCHMARK_RUNNER_NAME} ${PROJECT_VERSION})
enable_precompiled_headers(${BENCHMARK_RUNNER_NAME} ENABLE_PCH)
