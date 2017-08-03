#######################################
# CMAKE CATSMAT
#######################################
cmake_minimum_required(VERSION 3.6)
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

# set includes
include_directories( ${INCL})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)

# create the build target and the executable
set(target CATSMAT)
add_executable(${target} ${SRC} )


###############  Targeted Libraries ###########
TARGET_LINK_LIBRARIES(${target} libmusicxml2)
TARGET_LINK_LIBRARIES(${target} libIMUSANT)
TARGET_LINK_LIBRARIES(${target} ${BOOST_FILESYSTEM_LIB})
TARGET_LINK_LIBRARIES(${target} ${BOOST_SYSTEM_LIB})

