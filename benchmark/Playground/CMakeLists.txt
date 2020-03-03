
set(BenchmarkName BM_Strings)
add_executable(${BenchmarkName} ${BenchmarkName}.cpp)
target_include_directories(${BenchmarkName} PUBLIC ../gbenchmark/include)
if (MSVC)
    target_link_libraries(${BenchmarkName} benchmark shlwapi)
else (MSVC)
    target_link_libraries(${BenchmarkName} benchmark)
endif(MSVC)
