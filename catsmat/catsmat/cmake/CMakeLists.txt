#######################################
# CMAKE CATSMAT
#######################################
cmake_minimum_required(VERSION 3.6)
project(CATSMAT) #js
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

FIND_PACKAGE( Boost 1.57.0 COMPONENTS filesystem system REQUIRED ) #JS changed to look for specific libraries

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
	TARGET_LINK_LIBRARIES(${target} libmusicxml2; libIMUSANT; ${Boost_LIBRARIES}  )
endif()
# Note: set environmental variable DYLD_LIBRARY_PATH=/usr/local/boost/lib (or custom directory)
