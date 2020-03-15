### list of source files of the GrGraphics library
#configure_file(src/win/GrGraphics.rc.in ${CMAKE_CURRENT_BINARY_DIR}/src/win/GrGraphics.rc @ONLY)
set(GrGraphics_INC_FILES
#        include/MemoryDB.h
#        include/DBCreate.h
#        include/FileUtil.h
        )
set(GrGraphics_SRC_FILES
        src/test.cpp)
if(WIN32)
#    set(GrGraphics_SRC_FILES ${GrGraphics_SRC_FILES}
#            src/win/wgl_common.cpp)
endif(WIN32)
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
add_library(GrGraphics SHARED
        "${GrGraphics_SRC_FILES}"
        )
target_include_directories(GrGraphics PUBLIC ${INCLUDE_DIRECTORIES})
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
target_link_libraries(GrGraphics ${GrGraphics_PlatformLinkLibs})
target_compile_features(GrGraphics INTERFACE cxx_std_17) # require C++17
set_target_version_properties(GrGraphics ${PROJECT_VERSION})
enable_precompiled_headers(GrGraphics ENABLE_PCH)

add_library(oglTemplate::GrGraphics ALIAS GrGraphics)
