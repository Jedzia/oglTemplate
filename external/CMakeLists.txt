#set(SQLITECPP_INTERNAL_SQLITE OFF)
#add_subdirectory(sqlite_orm)
add_subdirectory(fmt)
option(OPTION_BUILD_EXAMPLES "Build examples." OFF)

add_subdirectory(docopt.cpp)

option(SPDLOG_FMT_EXTERNAL "Use external fmt library instead of bundled" ON)
#option(SPDLOG_FMT_EXTERNAL_HO "Use external fmt header-only library instead of bundled" ON)
add_subdirectory(spdlog)

add_subdirectory(glbinding)

add_subdirectory(glfw)


if (CMAKE_CXX_COMPILER MATCHES "clang[+][+]" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # The combination CLion + MSYS2 + CLang needs to have the MSYS2 system Freetype library found
    # before including SFML or SFML uses its own provided Freetype, which fails.
    find_package(Freetype REQUIRED)
endif ()
add_subdirectory(SFML)

add_subdirectory(sm)

if(UNIX)
    target_compile_options(fmt PUBLIC -fPIC)
    target_compile_options(spdlog PUBLIC -fPIC)
endif ()

