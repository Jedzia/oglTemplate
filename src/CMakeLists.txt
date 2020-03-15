#set(COTIRE_DEBUG ON)
#include(cotire)

add_executable(Application main.cpp)
target_include_and_link_boost_libraries(Application
        #        "GrCore;fmt::fmt-header-only"
        #"GrCore;fmt::fmt"
        "GrCore;GrGraphics;sfml-window;sfml-graphics;fmt::fmt"
        "Boost::program_options;Boost::filesystem"
        )
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

Copy_File(Application "${CMAKE_CURRENT_SOURCE_DIR}/Futura Bk BT Book.ttf" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_custom_target(run
        COMMAND Application
        DEPENDS Application
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        )
SET_TARGET_PROPERTIES(run
        PROPERTIES
        FOLDER Application
        )

#include(ucm)
#cotire(Application)
#ucm_add_target(NAME example TYPE EXECUTABLE SOURCES "${sources}" PCH_FILE precompiled.h)
#set(sources main.cpp)
#ucm_add_target(NAME example TYPE EXECUTABLE SOURCES "${sources}" PCH_FILE precompiled.h)

