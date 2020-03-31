
# s. E:\Projects\C++\Playground\projects\Playground\CMakeLists.txt for globbing
#add_executable(simple_main hello.cpp)


# playground single source files
SET(PLAYGROUND_CPP_FILES *.cpp)
SET(PLAYGROUND_HPP_FILES *.h)
SET(PLAYGROUND_MOC_FILES moc_*.cpp)

FILE(GLOB playground_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PLAYGROUND_CPP_FILES})
FILE(GLOB playground_headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PLAYGROUND_HPP_FILES})

#LIST(REMOVE_ITEM playground_sources ${TOP_SRC_DIR}/src/insets/InsetTheorem.cpp)
#MESSAGE(STATUS "[GLOB] Files: ${playground_sources}")

FOREACH (f ${playground_sources})
    GET_FILENAME_COMPONENT(_target_name ${f} NAME_WE)
    IF (${_target_name} STREQUAL "stdafx")
    ELSE (${_target_name} STREQUAL "stdafx")
        set(_target_name "Playground_Simple_${_target_name}")
        ADD_EXECUTABLE(${_target_name} ${f})
        #        TargetLinkBoost(${_target_name} "filesystem;system;regex;thread;date_time;chrono")
        #SET_PROPERTY(TARGET throw_error PROPERTY FOLDER "Playground/3rdParty")
        SET_PROPERTY(TARGET ${_target_name} PROPERTY FOLDER "Playground")

        SET_TARGET_PROPERTIES(${_target_name}
                PROPERTIES
                #		EXCLUDE_FROM_DEFAULT_BUILD
                EXCLUDE_FROM_ALL_BUILD
                TRUE)
        MESSAGE(STATUS "[GLOB EXAMPLE] Adding Example Project: ${_target_name}")
    ENDIF (${_target_name} STREQUAL "stdafx")
ENDFOREACH ()

if (CMAKE_CXX_COMPILER MATCHES "clang[+][+]" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Only Clang 9.0.0 has coroutine support
    target_compile_options(Playground_Simple_coroutine1 PRIVATE -stdlib=libc++ -fcoroutines-ts -orangesCoroutines01)
    #target_link_options(Playground_Simple_coroutine1 PRIVATE -stdlib=libc++ -fcoroutines-ts -orangesCoroutines01)
    target_link_libraries(Playground_Simple_coroutine1 PRIVATE c++ c++abi supc++ )
else ()
    set_target_properties(Playground_Simple_coroutine1 PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
endif ()


#target_link_libraries(Playground_Simple_coroutine1 /mingw64/lib/libc++ ) # c++experimental
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")