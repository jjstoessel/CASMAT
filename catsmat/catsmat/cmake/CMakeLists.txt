#######################################
# CMAKE CATSMAT
#######################################
# Note: set environmental variable DYLD_LIBRARY_PATH=/usr/local/boost/lib (or custom directory) on Mac only
cmake_minimum_required(VERSION 3.6)
project(CATSMAT) #js

if (APPLE)
	set (CMAKE_MACOSX_RPATH ON)
endif ()

set(CMAKE_CXX_STANDARD 11)
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()

# All the files that make up CATSMAT are listed in the file that is included below.  Edit that file
# if you want to add files into CATSMAT.
include("./CMakeCatsmatFiles.txt")

# Add the CATSMAT main (as instructed in the included file).
set(SRC ${SRC}
		${CATSMAT_APPLICATION_FILES}
		)

# Build up the include paths for header files.
foreach(folder ${INCFOLDERS})
	set(HEADERS ${HEADERS} "${folder}/*.h")		# add header files
	set(INCL ${INCL} "${folder}")				# add include folders
endforeach(folder)
file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

include("${CMAKE_SOURCE_DIR}/CMakeBoost.txt")

if (Boost_FOUND)
	#report boost status
	message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
	message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
	message(STATUS "Boost_VERSION: ${Boost_VERSION}")
	# set includes
	include_directories( ${INCL};${Boost_INCLUDE_DIRS})
	set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)
	#set target, add executable and link libraries (default shared/dynamic libraries)
	set(target CATSMAT)
	add_executable(${target} ${SRC} )
	TARGET_LINK_LIBRARIES(${target} libmusicxml2; libIMUSANT; ${Boost_LIBRARIES} )
	if (APPLE)
		add_custom_command(TARGET ${target} POST_BUILD COMMAND install_name_tool -change libboost_filesystem.dylib /usr/local/boost/lib/libboost_filesystem.dylib $<TARGET_FILE:${target}>)
		add_custom_command(TARGET ${target} POST_BUILD COMMAND install_name_tool -change libboost_system.dylib /usr/local/boost/lib/libboost_system.dylib $<TARGET_FILE:${target}>)
		add_custom_command(TARGET ${target} POST_BUILD COMMAND sudo install_name_tool -change libboost_system.dylib /usr/local/boost/lib/libboost_system.dylib /usr/local/boost/lib/libboost_filesystem.dylib)
	endif()
endif()

