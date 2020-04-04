project(GrCore VERSION "${OpenGLTemplate_VERSION}")

# Prepare Resource File
set(RESOURCE_OUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/src/win/GrCore.rc")
#set(CURRENT_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res" CACHE INTERNAL "")
set(CURRENT_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res")
configure_file(src/win/GrCore.rc.in "${RESOURCE_OUT_FILE}" @ONLY)

### list of source files of the GrCore library
set(GrCore_INC_FILES
        include/grcore/Common.h
        include/grcore/DataAcquisition.h
        include/grcore/FileSystem.h
        include/grcore/GrCore.h
        include/grcore/Instrumentation.h
        include/grcore/Logging.h
        include/grcore/Math.h
        include/grcore/Resource.h
        include/grcore/Telemetry.h
        include/grcore/Utility/Property.h
        include/grcore/Utility/TcpClient.h
        include/grcore/Utility/return_type_trait.h
        include/grcore/wgl_common.h
        )
set(GrCore_SRC_FILES
        src/FileSystem.cpp
        src/Logging.cpp
        src/Math.cpp
        src/Telemetry.cpp
        src/Utility/Property.cpp
        src/test.cpp
        src/win/TcpClient.cpp
        )
if (WIN32)
    set(GrCore_SRC_FILES ${GrCore_SRC_FILES}
            src/win/wgl_common.cpp
            src/win/Resource.cpp
            src/win/DllEntry.cpp
            src/win/console.cpp
            )
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
        "${GrCore_INC_FILES};${GrCore_SRC_FILES}"
        "${RESOURCE_OUT_FILE}")
target_include_directories(GrCore PUBLIC ${INCLUDE_DIRECTORIES})
target_compile_definitions(GrCore PRIVATE GrCore_WIN_EXPORT)
#target_compile_definitions(GrCore PUBLIC SPDLOG_HEADER_ONLY)

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
        PRIVATE ws2_32
        PRIVATE Mswsock
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

# ------------------------------------------------------------------------- #
# Tests
#option(GrCore_BuildTests "Build GrCore unit tests" ON) #-DGrCore_BuildTests:BOOL=ON
option(${PROJECT_NAME}_BUILD_TESTS "Build and run tests for ${PROJECT_NAME}." ON)
if (${PROJECT_NAME}_BUILD_TESTS AND PACKAGE_TESTS AND BUILD_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif ()

if (ENABLE_DOXYGEN)
    add_subdirectory(doc)
endif ()
