# Benchmarks

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BENCHMARK_ENABLE_TESTING "Enable testing of the benchmark library." OFF)

add_subdirectory(gbenchmark)
add_subdirectory(Playground)
add_subdirectory(benchmark)
