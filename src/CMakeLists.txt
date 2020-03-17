#set(COTIRE_DEBUG ON)
#include(cotire)

# Main Demo Application
add_executable(Application main.cpp)
list(APPEND Libraries_Used
        #oglTemplate::GrCore
        #oglTemplate::GrGraphics
        sfml-window sfml-graphics
        #fmt::fmt
        #docopt_s
        #spdlog::spdlog
        )
#list(APPEND _Libraries "fmt::fmt")
#list(APPEND _Libraries "docopt_s;spdlog::spdlog")
#target_link_libraries(Application PRIVATE
target_include_and_link_boost_libraries(Application
        #        "GrCore;fmt::fmt-header-only"
        #"GrCore;fmt::fmt"
        "${Libraries_Used}"
        "Boost::program_options;Boost::filesystem"
        )
target_link_libraries(Application PRIVATE project_options project_warnings)
target_link_libraries(Application PRIVATE spdlog::spdlog)
#target_compile_definitions(Application PRIVATE SPDLOG_FMT_EXTERNAL)
#target_include_directories(Application PRIVATE "E:/Projects/C++/oglTemplate/external/spdlog/include")
#target_include_directories(Application PRIVATE "E:/Projects/C++/oglTemplate/external/fmt/include")
#target_link_libraries(Application PRIVATE oglTemplate::GrCore)
target_link_libraries(Application PRIVATE oglTemplate::GrGraphics)
#target_link_libraries(Application PRIVATE fmt::fmt)
#target_link_libraries(Application -static-libgcc -static-libstdc++)

# problems with mingw clang
if (NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set_target_properties(Application PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "precompiled.h")
endif ()
enable_precompiled_headers(Application ENABLE_PCH)
# only at CMake version 3.16
#target_precompile_headers(Application PRIVATE
#        "$<$<COMPILE_LANGUAGE:C>:<stddef.h$<ANGLE-R>>"
#        "$<$<COMPILE_LANGUAGE:CXX>:<cstddef$<ANGLE-R>>"
#        )

# Copy fonts to the binary folder
copy_file(Application "${CMAKE_CURRENT_SOURCE_DIR}/Futura Bk BT Book.ttf" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Futura Bk BT Book.ttf")
#copy_file(Application "${CMAKE_CURRENT_SOURCE_DIR}/Futura Bk BT Book.ttf" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#[[
add_custom_command(
        TARGET Application
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/Futura Bk BT Book.ttf" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Futura Bk BT Book.ttf"
        COMMENT "Copy ${CMAKE_CURRENT_SOURCE_DIR}/Futura Bk BT Book.ttf to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}."
)
]]

# Add a runner target for the application
add_run_target(Application ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


# ucm stuff, just as example, not used
#include(ucm)
#cotire(Application)
#ucm_add_target(NAME example TYPE EXECUTABLE SOURCES "${sources}" PCH_FILE precompiled.h)
#set(sources main.cpp)
#ucm_add_target(NAME example TYPE EXECUTABLE SOURCES "${sources}" PCH_FILE precompiled.h)

