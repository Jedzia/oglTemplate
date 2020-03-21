include(helpers)

set(BenchmarkName BM_Strings)
add_executable(${BenchmarkName} ${BenchmarkName}.cpp)
#target_include_directories(${BenchmarkName} PUBLIC ../gbenchmark/include)
if (MSVC)
    target_link_libraries(${BenchmarkName} PRIVATE benchmark shlwapi)
else (MSVC)
    target_link_libraries(${BenchmarkName} PRIVATE benchmark)
endif(MSVC)



set(BenchmarkName BM_FloatingPoint)
add_executable(${BenchmarkName} ${BenchmarkName}.cpp)
target_link_libraries(${BenchmarkName} PRIVATE benchmark sfml-graphics fmt::fmt)
#target_include_directories(${BenchmarkName} PUBLIC ../gbenchmark/include)
if (MSVC)
    target_link_libraries(${BenchmarkName} PRIVATE shlwapi)
else (MSVC)
    #target_link_libraries(${BenchmarkName} PRIVATE benchmark)
endif(MSVC)
add_run_target(${BenchmarkName} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_list_target(${BenchmarkName} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND arm-none-eabi-size --format=berkeley "rtos_clion.elf")
#add_custom_command(${BenchmarkName} ${PROJECT_NAME} POST_BUILD
#        COMMAND arm-none-eabi-size --format=berkeley "rtos_clion.elf")
