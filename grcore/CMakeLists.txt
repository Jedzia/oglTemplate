project(GrCore VERSION "${OpenGLTemplate_VERSION}")

configure_file(src/win/GrCore.rc.in ${CMAKE_CURRENT_BINARY_DIR}/src/win/GrCore.rc @ONLY)

### list of source files of the GrCore library
set(GrCore_INC_FILES
        #        include/MemoryDB.h
        #        include/DBCreate.h
        #        include/FileUtil.h
        )
set(GrCore_SRC_FILES
        src/test.cpp
        src/logging.cpp
        )
if (WIN32)
    set(GrCore_SRC_FILES ${GrCore_SRC_FILES}
            src/win/wgl_common.cpp)
endif (WIN32)
set(INCLUDE_DIRECTORIES
        #         include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        #        external/sqlite_orm/include
        )
# ToDo: make that the paths are automatic escaped with ${CMAKE_CURRENT_SOURCE_DIR} for the export
set(GrCore_INCLUDE_DIRECTORIES "${INCLUDE_DIRECTORIES}" PARENT_SCOPE)

source_group(src FILES ${GrCore_SRC_FILES} main.cpp)

#add_library_with_resource(GrCore STATIC
add_library_with_resource(GrCore SHARED
        "${GrCore_SRC_FILES}"
        "${CMAKE_CURRENT_BINARY_DIR}/src/win/GrCore.rc")
target_include_directories(GrCore PUBLIC ${INCLUDE_DIRECTORIES})
target_compile_definitions(GrCore PRIVATE GrCore_WIN_EXPORT)

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
    set(GrCore_PlatformLinkLibs stdc++fs)
endif (MSVC)
target_link_libraries(GrCore
        PUBLIC ${GrCore_PlatformLinkLibs}
        PRIVATE project_options project_warnings
        PRIVATE spdlog::spdlog
        #INTERFACE spdlog::spdlog
        #INTERFACE fmt::fmt
        #        CONAN_PKG::docopt.cpp
        #        CONAN_PKG::fmt CONAN_PKG::spdlog
        )
#target_compile_features(GrCore INTERFACE cxx_std_20) # require C++20
set_target_version_properties(GrCore ${PROJECT_VERSION})
enable_precompiled_headers(GrCore ENABLE_PCH)

# Create namespaced alias
add_library(oglTemplate::GrCore ALIAS GrCore)
