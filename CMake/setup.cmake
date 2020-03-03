# Conditional compilation constants that are available
# USE_BOOST :
#   Is defined when set(USE_HEADERONLY_BOOST TRUE) or set(USE_LIB_BOOST TRUE) with usage of at least one
#   component( set(BOOST_USED_COMPONENTS "program_options;filesystem") ).
#   This indicates that boost is used at all.
#
# USE_LIB_BOOST :
#   set(USE_LIB_BOOST TRUE) and providing at least one set(BOOST_USED_COMPONENTS "program_options;filesystem")
#   enables linking of static or shared boost libraries and declares the constant USE_LIB_BOOST.
#
# USE_HEADERONLY_BOOST
#   Is defined when set(USE_HEADERONLY_BOOST TRUE). This overrides the library option and
#   enables only the "include" capabilities of the macro target_include_and_link_boost_libraries().

if (MSVC)
    # ToDo: Remove this, the user must be able to point to her boost installation.
    set(BOOST_ROOT "E:/Devel/CPP/Libs/boost/boost-git_master")
    #SET(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib/x64/lib")
endif ()


if (USE_HEADERONLY_BOOST)
    FIND_PACKAGE(Boost 1.68.0 REQUIRED COMPONENTS ${BOOST_USED_COMPONENTS})
    MESSAGE(STATUS "using boost header-only.")

    # add boost include directory and link with boost components
    # _libraries: non boost libraries like "glib;zlib;pango;mylibrary"
    #     if it has exported LIBRARY-NAME_INCLUDE_DIRECTORIES the include directories
    #     are used.
    # _boost_libraries: like "Boost::program_options;Boost::filesystem".
    #                   This is IGNORED in USE_HEADERONLY_BOOST.
    # ToDo: unify this with the other header using version, down.
    macro(target_include_and_link_boost_libraries _target _libraries _boost_libraries)
        foreach (mCOMPONENT ${_libraries})
            #message(WARNING "lib(${mCOMPONENT}) include: ${${mCOMPONENT}_INCLUDE_DIRECTORIES}")
            target_include_directories(${_target} PRIVATE ${${mCOMPONENT}_INCLUDE_DIRECTORIES})
        endforeach (mCOMPONENT)
        target_link_libraries(${_target} ${_libraries})
    endmacro(target_include_and_link_boost_libraries _target _libraries _boost_libraries)

    add_definitions("-DUSE_HEADERONLY_BOOST")
    add_definitions("-DUSE_BOOST")
else (USE_HEADERONLY_BOOST)
    IF (USE_LIB_BOOST)
        #SET(Boost_DEBUG ON)
        #SET(BOOST_ALWAYS_RERUN ON)

        SET(Boost_USE_STATIC_LIBS ON)      # Set to ON to force the use of the static
        # libraries.  Default is OFF.
        #SET(Boost_USE_STATIC_LIBS OFF)

        # SET(Boost_USE_MULTITHREADED OFF) # Set to OFF to use the non-multithreaded
        # libraries ('mt' tag).  Default is ON.
        #    set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
        #    set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs

        FIND_PACKAGE(Boost 1.68.0 REQUIRED COMPONENTS ${BOOST_USED_COMPONENTS})

        if (NOT Boost_USE_STATIC_LIBS)
            MESSAGE(STATUS "boost is using dynamic link libraries.")
            # Linker Flag to use the dynamic linked boost libs.
            add_definitions("-DBOOST_ALL_DYN_LINK")
        endif ()
        #add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
        if (BOOST_USED_COMPONENTS STREQUAL "")
        else ()
            #only when components are used, then set the define.
            add_definitions("-DUSE_LIB_BOOST")
            add_definitions("-DUSE_BOOST")
        endif ()
    endif (USE_LIB_BOOST)

    # add boost include directory and link with boost components
    # _libraries: non boost libraries like "glib;zlib;pango;mylibrary"
    #     if it has exported LIBRARY-NAME_INCLUDE_DIRECTORIES the include directories
    #     are used.
    # _boost_libraries: like "Boost::program_options;Boost::filesystem"
    macro(target_include_and_link_boost_libraries _target _libraries _boost_libraries)
        #    # For later use, e.g. dll copy
        #    foreach (mCOMPONENT ${_boost_libraries})
        #        #MESSAGE("mCOMPONENT:  ${mCOMPONENT}")
        #        string(TOUPPER ${mCOMPONENT} rCOMPONENT)
        #        string(REPLACE "BOOST::" ""  COMPONENT ${rCOMPONENT})
        #        if ("${Boost_${COMPONENT}_LIBRARY}" STREQUAL "")
        #            #MESSAGE("NOT YET FOUND: ${COMPONENT}")
        #            list(APPEND boost_tmp_component_list ${mCOMPONENT})
        #        else ()
        #            #MESSAGE("ALREADY FOUND: ${COMPONENT}: ${Boost_${COMPONENT}_LIBRARY}")
        #        endif ()
        #    endforeach (mCOMPONENT)

        foreach (mCOMPONENT ${_libraries})
            #message(WARNING "lib(${mCOMPONENT}) include: ${${mCOMPONENT}_INCLUDE_DIRECTORIES}")
            target_include_directories(${_target} PRIVATE ${${mCOMPONENT}_INCLUDE_DIRECTORIES})
        endforeach (mCOMPONENT)

        if (USE_LIB_BOOST)
            target_include_directories(${_target} PRIVATE ${Boost_INCLUDE_DIR})
            target_link_libraries(${_target}
                    ${_libraries}
                    ${_boost_libraries}
                    )
        else (USE_LIB_BOOST)
            target_link_libraries(${_target}
                    ${_libraries}
                    )
        endif (USE_LIB_BOOST)
    endmacro(target_include_and_link_boost_libraries _target _libraries _boost_libraries)


    IF (USE_LIB_BOOST_DEPRECATED)
        SET(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;regex;program_options;unit_test_framework;serialization")
        SET(boost_local_root $ENV{BOOST_ROOTDIR})
        IF (NOT boost_local_root)
            #        SET(boost_local_root "E:/Devel/CPP/Libs/boost/boost-1.55.0")
        ENDIF ()
        #SET(boost_local_root E:/Devel/CPP/Libs/boost/boost-svn)
        #    IF (EXISTS "${boost_local_root}" AND NOT BOOST_ROOT)
        #        SET(BOOST_ROOT "${boost_local_root}" CACHE PATH "Boost root directory" FORCE)
        #    ELSE ()
        #        #SET(BOOST_ROOT "" CACHE PATH "Boost root directory")
        #    ENDIF ()
        #### SET(BOOST_ROOT "E:/Devel/CPP/Libs/boost/boost-svn" CACHE PATH "Boost root directory")
        #MESSAGE( FATAL_ERROR " BLAAAA " )

        IF (BOOST_ROOT)
            # If the user specified a non system path for the boost libraries,
            # then prevent from using the systems boost libraries.
            SET(Boost_NO_SYSTEM_PATHS TRUE)
        ENDIF (BOOST_ROOT)
        #SET(Boost_INCLUDE_DIR "" CACHE PATH "Boost root directory")
        #SET(Boost_COMPILER "")
        #SET(Boost_ADDITIONAL_VERSIONS "1.45" "1.45.1" "1.46" "1.46.0")

        #Check for additional boost libs
        SET(Boost_FIND_COMPONENTS ${USE_LIB_BOOST_COMPONENTS})
        SET(boost_tmp_component_list)

        foreach (mCOMPONENT ${Boost_FIND_COMPONENTS})
            string(TOUPPER ${mCOMPONENT} COMPONENT)
            if ("${Boost_${COMPONENT}_LIBRARY}" STREQUAL "")
                #MESSAGE("NOT YET FOUND: ${COMPONENT}")
                list(APPEND boost_tmp_component_list ${mCOMPONENT})
            else ()
                #MESSAGE("ALREADY FOUND: ${COMPONENT}: ${Boost_${COMPONENT}_LIBRARY}")
            endif ()
        endforeach (mCOMPONENT)


        SET(BOOST_ALWAYS_RERUN ON)
        SET(Boost_USE_STATIC_LIBS OFF)
        SET(Boost_USE_MULTITHREADED ON)
        #SET(Boost_USE_STATIC_RUNTIME    ON)
        #SET(Boost_COMPAT_STATIC_RUNTIME ON)
        #SET(Boost_INCLUDE_DIR "")
        # Detailed findboost output
        #set(Boost_DEBUG TRUE)

        # You can call #ADD_DEFINITIONS(${Boost_LIB_DIAGNOSTIC_DEFINITIONS}) to have diagnostic
        # information about Boost's #automatic linking outputted during compilation time.
        ADD_DEFINITIONS(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
        ADD_DEFINITIONS("-DUSE_LIB_BOOST")

        IF (NOT Boost_USE_STATIC_LIBS)
            MESSAGE(STATUS " Using dynamically linked boost libs ")
            # Linker Flag to use the dynamically linked boost libs.
            ADD_DEFINITIONS("-DBOOST_ALL_DYN_LINK")
            # mal schauen wie ich das einbaue
            #ADD_DEFINITIONS("-DBOOST_DYN_LINK")
            #ADD_DEFINITIONS("-DBOOST_ALL_DYN_LINK")
        ENDIF ()

        #    FIND_PACKAGE(Boost 1.46.0 REQUIRED COMPONENTS ${boost_tmp_component_list})
        FIND_PACKAGE(Boost REQUIRED COMPONENTS ${boost_tmp_component_list})
        if ("${Boost_VERSION}0" LESS "1046000")
            set(_shared_msg
                    "NOTE: boost:: targets and tests cannot "
                    "be added: boost >= 1.46.0 required but not found. "
                    "(found: '${Boost_VERSION}'; want >=104600) ")
            message(FATAL_ERROR
                    ${_shared_msg}
                    "You may install the boost libraries on your system and set the"
                    "BOOST_ROOT config var.")
        ENDIF ()

        # Additional check for ICU Library
        FIND_PACKAGE(ICU)
        MARK_AS_ADVANCED(ICU_DLL_DEBUG)
        MARK_AS_ADVANCED(ICU_DLL_RELEASE)

    ENDIF (USE_LIB_BOOST_DEPRECATED)

endif (USE_HEADERONLY_BOOST)

macro(enable_precompiled_headers _target _enable)
    if (${_enable})
        include(cotire)
        MESSAGE("precompiled headers enabled for '${_target}'")
        cotire(${_target})
    else ()
        #MESSAGE("NOOOO precompiled headers enabled for '${_target}'")
    endif ()
endmacro(enable_precompiled_headers _target _enable)

macro(add_library_with_resource _target _shared_or_static _src_files _resource_files)
    if (WIN32)
        # On Windows give .dll embedded version information
        add_library(${_target} ${_shared_or_static} ${_src_files} ${_resource_files})
    else (WIN32)
        add_library(${_target} ${_shared_or_static} ${_src_files})
    endif (WIN32)
endmacro(add_library_with_resource _target _shared_or_static _src_files _resource_files)

macro(add_executable_with_resource _target  _src_files _resource_files)
    if (WIN32)
        # On Windows give .exe embedded version information
        add_executable(${_target} ${_src_files} ${_resource_files})
    else (WIN32)
        add_executable(${_target} ${_src_files})
    endif (WIN32)
endmacro(add_executable_with_resource _target _shared_or_static _src_files _resource_files)

macro(use_common_runtime_directory _target)
set_target_properties(${_target}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
endmacro(use_common_runtime_directory _target)
