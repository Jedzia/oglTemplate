#option(META_BUILD_TESTS "Build test programs" OFF)
#add_subdirectory(metapushkin)
##list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/metapushkin/cmake")
#set(METAPUSHKIN_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/metapushkin" CACHE PATH "Folder containing metapushkin library" )
#find_package(MetaPushkin REQUIRED)
#message(FATAL_ERROR "METAPUSHKIN_INCLUDE_DIR ${METAPUSHKIN_INCLUDE_DIR}")
##set(METAPUSHKIN_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/metapushkin/include" CACHE PATH "Folder containing metapushkin includes" FORCE)
#message(FATAL_ERROR "METAPUSHKIN_INCLUDE_DIRS ${METAPUSHKIN_INCLUDE_DIRS}")


#option(AFSM_BUILD_TESTS "Build test programs" OFF)
#add_subdirectory(afsm)
##list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/afsm/cmake")
##set(AFSM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/afsm" CACHE PATH "Folder containing afsm library")
##find_package(AFSM REQUIRED)
#message(FATAL_ERROR "AFSM_INCLUDE_DIR ${AFSM_INCLUDE_DIR}")
#set(AFSM_INCLUDE_DIRS "${AFSM_INCLUDE_DIRS};${METAPUSHKIN_INCLUDE_DIRS}" CACHE PATH "afsm library include paths" FORCE)
#message(FATAL_ERROR "AFSM_INCLUDE_DIRS ${AFSM_INCLUDE_DIRS}")

add_library(afsm INTERFACE)
target_include_directories(afsm INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/metapushkin/include;${CMAKE_CURRENT_SOURCE_DIR}/afsm/include")

add_library(afsm::afsm ALIAS afsm)
