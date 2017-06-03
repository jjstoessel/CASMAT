#######################################
# CMAKE IMUSANT_Test
#######################################
cmake_minimum_required(VERSION 2.4)
set(CMAKE_CXX_STANDARD 11)
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()

if(UNIX)
	add_definitions(-Wall -DGCC)
endif(UNIX)

#if(APPLE)
#	set (CMAKE_OSX_ARCHITECTURES "x86_64 i386")
#	if (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)
#		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.4u.sdk)
#	elseif (${CMAKE_SYSTEM_VERSION} VERSION_LESS 10.8.0)
#		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
#	elseif (${XCODE_VERSION} VERSION_LESS 4.0.0)
#		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.6.sdk)
#	else ()
#		set (CMAKE_OSX_SYSROOT "macosx10.7")
#	endif ()
#	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
#endif(APPLE)
#
#if(WIN32)
# add_definitions(-DWINVER=0x0400 -DWIN32)
# if(${CMAKE_GENERATOR} STREQUAL "Visual Studio 6")
#  add_definitions(-DVC6)
# elseif(${CMAKE_GENERATOR} STREQUAL "Visual Studio 8 2005")
#  add_definitions(-DVC2005)
# endif(${CMAKE_GENERATOR} STREQUAL "Visual Studio 6")
#endif(WIN32)

###############  BOOST LIBRARIES ###########
if (APPLE)
	set(BOOST_ROOT "/usr/local/boost")
	set(BOOST_LIBRARYDIR /usr/local/boost/lib)
else ()
	set(BOOST_ROOT "C:/local/boost_1_58_0")
	set(BOOST_LIBRARYDIR C:/local/boost_1_58_0/lib64-msvc-12.0)
endif ()


FIND_PACKAGE( Boost 1.58.0 REQUIRED  )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


###############  GTEST LIBRARIES ###########
if (APPLE)
	set(GTEST_ROOT "/Library/Frameworks/gtest.framework/gtest")
	set(GTEST_INCLUDE_DIR "/Library/Frameworks/gtest.framework/Headers")
else ()
	set(GTEST_ROOT "C:/Development/googletest-master/googletest-master/cmake-build-debug/googlemock/gtest")
	set(GTEST_INCLUDE_DIR "C:/Development/googletest-master/googletest-master/googletest/include/")
endif ()

message("GTEST_ROOT=" ${GTEST_ROOT})

FIND_PACKAGE( GTEST REQUIRED  )
include_directories(${GTEST_INCLUDE_DIR})


#######################################
# set directories, src and headers.
# Get source from IMUSANT project.  This would be easier if we moved the source.
# The source in the Segmentation folder probably needs separating into src and inc directories.

set (libIMUSANT_TESTS_DIR 	${CMAKE_CURRENT_SOURCE_DIR}/../../libIMUSANT_Tests)
set (libIMUSANT_DIR 	    ${CMAKE_CURRENT_SOURCE_DIR}/../../libIMUSANT)
set (LOKI_DIR               ${CMAKE_CURRENT_SOURCE_DIR}/../../Loki)
set (SUFFIX_TREE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/../../SuffixTree)
set (CATSMAT_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/../../CATSMAT)    #### REVISIT really need to move IMUSANT_t_repeated_substring.h out of libIMUSANT

set (SRCFOLDERS
#		${IMUSANT_TESTS_DIR}
		${libIMUSANT_TESTS_DIR}/DomainObjects
        ${libIMUSANT_TESTS_DIR}/Converters
		${libIMUSANT_TESTS_DIR}/Utilities
		)

set (INCFOLDERS
		${libIMUSANT_DIR}
		${IMUSANT_TESTS_DIR}/Utilities
		${libIMUSANT_DIR}/DomainObjects/inc
		${libIMUSANT_DIR}/Analysis/inc
		${libIMUSANT_DIR}/Analysis/Segmentation
		${libIMUSANT_DIR}/Analysis/Segmentation/FixedPeriodDetection
		${libIMUSANT_DIR}/Analysis/Segmentation/LocalBoundaryDetectionModel
		${libIMUSANT_DIR}/Utilities/inc
		${libIMUSANT_DIR}/FileProcessing/inc
		${libIMUSANT_DIR}/Converters/MusicXML_v3
		${libIMUSANT_DIR}/Converters/MusicXML_v3/inc
		${libIMUSANT_DIR}/Converters/MusicXML_v3/shared/inc
		${LOKI_DIR}
		${SUFFIX_TREE_DIR}
		${CATSMAT_DIR}/CounterpointAnalysis/inc
		)

set(SRC ${SRC}
		${libIMUSANT_TESTS_DIR}/main.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_key_Tests.cpp)

#[[   ====   REVISIT - Not building the actual tests at the moment. ======
foreach(folder ${SRCFOLDERS})
	set(SRC ${SRC} "${folder}/*.cpp")			# add source files
endforeach(folder)
file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})
]]

foreach(folder ${INCFOLDERS})
	set(HEADERS ${HEADERS} "${folder}/*.h")
endforeach(folder)
file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

foreach(folder ${INCFOLDERS})
	set(INCL ${INCL} "${folder}")				# add include folders
endforeach(folder)


set (LIBFOLDERS ${LIBFOLDERS}
		"/cygdrive/c/Development/CATSMAT/CATSMAT/cmake-build-debug/catsmat/libIMUSANT/cmake/libIMUSANT.dll")


#######################################
# set includes
include_directories( ${INCL})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)


#######################################
# set library target
if(APPLE OR MSVC)
	set(target libIMUSANT_Test)
else(APPLE OR MSVC)
	set(target libIMUSANT_Test)
endif(APPLE OR MSVC)

if(MSVC)
	enable_language(RC)
	set(LIBCONTENT ${CORESRC} ${COREH} ${libIMUSANT_TESTS_DIR}/win32/libIMUSANT/libIMUSANT.rc)
else(MSVC)
	set(LIBCONTENT ${CORESRC} ${COREH})
endif(MSVC)

#add_library(gtest STATIC IMPORTED)
#add_library(gtest-main STATIC IMPORTED)
#set_property(TARGET gtest PROPERTY IMPORTED_LOCATION "${GTEST_ROOT}/libgtest.a")
#set_property(TARGET gtest-main PROPERTY IMPORTED_LOCATION "${GTEST_ROOT}/libgtest_main.a")

add_executable(${target} ${SRC} )

target_link_libraries(${target} gtest )
target_link_libraries( ${target} ${Boost_LIBRARIES})

link_directories("/cygdrive/c/Development/CATSMAT/CATSMAT/cmake-build-debug/catsmat/libIMUSANT/cmake/")
#add_library(libIMUSANT SHARED IMPORTED)
add_dependencies(libIMUSANT ${target})

set_target_properties (${target} PROPERTIES
			FRAMEWORK TRUE
			VERSION ${VERSION}
			FRAMEWORK_VERSION ${VERSION}
			PUBLIC_HEADER "${COREH}"
			DEFINE_SYMBOL LIBMUSICXML_EXPORTS
			MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${STRVERS}
			MACOSX_FRAMEWORK_BUNDLE_VERSION ${SSTRVERS}
)




#[[#######################################
# set sample targets
set (SAMPLES RandomMusic xmlfactory partsummary xml2guido xmliter countnotes readunrolled xml2midi xmlread xmltranspose xmlclone)
set (TOOLS  xml2guido xmltranspose)

foreach(sample ${SAMPLES})
	add_executable( ${sample} ${LXMLSAMPLE}/${sample}.cpp )
	target_link_libraries( ${sample} ${target})
	add_dependencies(${sample} ${target})
endforeach(sample)
]]


#######################################
# install setup
if(NOT APPLE)
install ( TARGETS ${target} ${TOOLS}
	RUNTIME DESTINATION bin
    	LIBRARY DESTINATION lib
    	ARCHIVE DESTINATION lib
    	FRAMEWORK DESTINATION "/Library/Frameworks" CONFIGURATIONS Release
    	PUBLIC_HEADER DESTINATION include/libmusicxml
)
endif()
