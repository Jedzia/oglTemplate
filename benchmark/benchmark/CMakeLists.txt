project(SpeedIOBench VERSION "${OpenGLTemplate_VERSION}")
### list of source files of the SpeedIO executable
configure_file(src/win/SpeedIOBench.rc.in ${CMAKE_CURRENT_BINARY_DIR}/src/win/SpeedIOBench.rc @ONLY)
set(SPEEDIO_SRC_FILES "src/main.cpp")
set(BENCHMARK_RUNNER_NAME ${PROJECT_NAME})
add_executable_with_resource(${BENCHMARK_RUNNER_NAME}
        "${SPEEDIO_SRC_FILES}"
        "${CMAKE_CURRENT_BINARY_DIR}/src/win/SpeedIOBench.rc")

target_include_directories(${BENCHMARK_RUNNER_NAME} PRIVATE include)
target_include_and_link_boost_libraries(${BENCHMARK_RUNNER_NAME}
#        "SpeedIO;fmt::fmt-header-only"
        "SpeedIO;fmt::fmt"
        "Boost::program_options;Boost::filesystem")
set_target_version_properties(${BENCHMARK_RUNNER_NAME} ${PROJECT_VERSION})
enable_precompiled_headers(${BENCHMARK_RUNNER_NAME} ENABLE_PCH)
