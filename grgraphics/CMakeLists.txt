project(GrGraphics VERSION "${OpenGLTemplate_VERSION}")
#project(GrGraphics)
#message(FATAL_ERROR "{PROJECT_NAME}_{FILE_NAME}_{EXT} ${CMAKE_PROJECT_NAME} - ${FILE_NAME} - ${EXT}")
#message(FATAL_ERROR "{PROJECT_NAME}_{FILE_NAME}_{EXT} ${PROJECT_NAME} - ${FILE_NAME} - ${EXT}")
#configure_file(src/win/GrGraphics.rc.in ${CMAKE_CURRENT_BINARY_DIR}/src/win/GrGraphics.rc @ONLY)

### list of source files of the GrGraphics library
set(GrGraphics_INC_FILES
        include/grgraphics/Application.h
        include/grgraphics/SimpleApplication.h
        include/grgraphics/warning/SFML_Graphics.h
        include/grgraphics/warning/FMT_format.h
        )
set(GrGraphics_SRC_FILES
        src/test.cpp
        src/sfml-test.cpp
        src/Application.cpp
        src/SimpleApplication.cpp
        )
if (WIN32)
    #    set(GrGraphics_SRC_FILES ${GrGraphics_SRC_FILES}
    #            src/win/wgl_common.cpp)
endif (WIN32)
set(INCLUDE_DIRECTORIES
        #         include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        #        external/sqlite_orm/include
        )
# ToDo: make that the paths are automatic escaped with ${CMAKE_CURRENT_SOURCE_DIR} for the export
set(GrGraphics_INCLUDE_DIRECTORIES "${INCLUDE_DIRECTORIES}" PARENT_SCOPE)

source_group(src FILES ${GrGraphics_SRC_FILES} main.cpp)

#[[
add_library_with_resource(GrGraphics SHARED
        "${GrGraphics_SRC_FILES}"
        "${CMAKE_CURRENT_BINARY_DIR}/src/win/GrGraphics.rc"
        )
]]
#add_library(GrGraphics SHARED
add_library(GrGraphics STATIC
        "${GrGraphics_SRC_FILES}"
        )
target_include_directories(GrGraphics PUBLIC ${INCLUDE_DIRECTORIES})
#target_include_directories(GrGraphics PRIVATE "E:/Projects/C++/oglTemplate/external/spdlog/include")
target_compile_definitions(GrGraphics PRIVATE GrGraphics_WIN_EXPORT)

# #get_property(fancy_lib_location TARGET ${PROJECT_NAME} PROPERTY LIBRARY_LOCATION)
# # Push the current (NEW) CMake policy onto the stack, and apply the OLD policy.
# cmake_policy(PUSH)
# cmake_policy(SET CMP0026 OLD)
# #get_property(fancy_lib_location TARGET ${PROJECT_NAME} PROPERTY LOCATION_NAME)
# get_property(fancy_lib_location TARGET ${PROJECT_NAME} PROPERTY LOCATION)
# #message (STATUS "PROJECT_BINARY_DIR == ${PROJECT_BINARY_DIR}")
# #message (STATUS "fancy_lib_location == ${${PROJECT_NAME}_LOCATION}")
# message (STATUS "fancy_lib_location == ${fancy_lib_location}")
# # Pop the previous policy from the stack to re-apply the NEW behavior.
# cmake_policy(POP)

#message(WARNING "MSVC '${MSVC}'")
if (MSVC)
else (MSVC)
    set(GrGraphics_PlatformLinkLibs stdc++fs)
endif (MSVC)
target_link_libraries(GrGraphics
        PUBLIC ${GrGraphics_PlatformLinkLibs}
        PRIVATE spdlog::spdlog
        PRIVATE sfml-graphics
        PUBLIC oglTemplate::GrCore
        #PRIVATE fmt::fmt
        PRIVATE project_options project_warnings
        #        CONAN_PKG::docopt.cpp
        #        CONAN_PKG::fmt CONAN_PKG::spdlog
        )
target_compile_features(GrGraphics INTERFACE cxx_std_17) # require C++17
set_target_version_properties(GrGraphics ${PROJECT_VERSION})
enable_precompiled_headers(GrGraphics ENABLE_PCH)

# Create namespaced alias
add_library(oglTemplate::GrGraphics ALIAS GrGraphics)
