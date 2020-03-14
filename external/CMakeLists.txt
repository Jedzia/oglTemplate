#set(SQLITECPP_INTERNAL_SQLITE OFF)
#add_subdirectory(sqlite_orm)
add_subdirectory(fmt)
option(OPTION_BUILD_EXAMPLES          "Build examples."                                        OFF)

add_subdirectory(glbinding)

add_subdirectory(glfw)

add_subdirectory(SFML)
