#######################################
# CMAKE CATSMAT_count
#######################################
project(count)

if (APPLE)
    set (CMAKE_MACOSX_RPATH ON)
    # use, i.e. don't skip the full RPATH for the build tree
    SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
endif ()

#if(DEBUG)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
#endif()

set(CMAKE_CXX_STANDARD 11)
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()

# This file contains all the paths for the CATSMAT code that we are testing.
# For now we compile all CATSMAT code: CATSMAT would be better as a shared library invoked by tools
include(${CMAKE_SOURCE_DIR}/catsmat/catsmat/cmake/CMakeCatsmatFiles.txt)

set (CATSMAT_COUNT_DIR ..)

set (CATSMAT_COUNT_FILES
        ${CATSMAT_COUNT_DIR}/src/CATSMAT_count_main.cpp
        ${CATSMAT_COUNT_DIR}/src/CATSMAT_count.cpp
        )

set(COMMANDO_INC_FOLDER "${CATSMAT_DIR}/Commando/inc")
foreach(folder ${COMMANDO_INC_FOLDER})
    set(COMMANDO_HEADERS ${COMMANDO_HEADERS} "${folder}/*.h")
    set(COMMANDO_INCL ${COMMANDO_INCL} "${folder}")
endforeach(folder)

# Add the CATSMAT_count main (as instructed in the included file).
set(SRC ${SRC}
        ${CATSMAT_COUNT_FILES}
        )

# Build up the include paths for header files.
foreach(folder ${INCFOLDERS})
    set(HEADERS ${HEADERS} "${folder}/*.h")		# add header files
    set(INCL ${INCL} "${folder}")				# add include folders
endforeach(folder)

file (GLOB COREH RELATIVE . ${HEADERS} ${COMMANDO_HEADERS})

include("${CMAKE_SOURCE_DIR}/CMakeBoost.txt")

add_definitions( -DBOOST_ALL_NO_LIB )

if (Boost_FOUND)
    #report boost status
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    # set includes
    include_directories( ${INCL};${COMMANDO_INC_FOLDER};${Boost_INCLUDE_DIRS})
    set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)
    #set target, add executable and link libraries (default shared/dynamic libraries)
    set(target count)
    add_executable(${target} ${SRC} )
    TARGET_LINK_LIBRARIES(${target} libmusicxml2; libIMUSANT;  ${Boost_LIBRARIES}; libCommando)
    if (APPLE)
        add_custom_command(TARGET ${target} POST_BUILD COMMAND install_name_tool -change libboost_filesystem.dylib /usr/local/boost/lib/libboost_filesystem.dylib $<TARGET_FILE:${target}>)
        add_custom_command(TARGET ${target} POST_BUILD COMMAND install_name_tool -change libboost_system.dylib /usr/local/boost/lib/libboost_system.dylib $<TARGET_FILE:${target}>)
        #add_custom_command(TARGET ${target} POST_BUILD COMMAND sudo install_name_tool -change libboost_system.dylib /usr/local/boost/lib/libboost_system.dylib /usr/local/boost/lib/libboost_filesystem.dylib)
    endif()
endif()
# Note: set environmental variable DYLD_LIBRARY_PATH=/usr/local/boost/lib (or custom directory)