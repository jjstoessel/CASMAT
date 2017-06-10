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
	set(BOOST_FILESYSTEM_LIB  /usr/local/boost/lib/libboost_filesystem.dylib)
	set(BOOST_SYSTEM_LIB      /usr/local/boost/lib/libboost_system.dylib)

else ()
	set(BOOST_ROOT "C:/local/boost_1_58_0")
	set(BOOST_FILESYSTEM_LIB  C:/local/boost_1_58_0/lib64-msvc-12.0)
	set(BOOST_SYSTEM_LIB      C:/local/boost_1_58_0/lib64-msvc-12.0)
endif ()

FIND_PACKAGE( Boost 1.58.0 REQUIRED  )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


#######################################
# set directories, src and headers.

set (libIMUSANT_TESTS_DIR 	${CMAKE_CURRENT_SOURCE_DIR}/../../libIMUSANT_Tests)

set (libIMUSANT_DIR 	    ${CMAKE_CURRENT_SOURCE_DIR}/../../libIMUSANT)
set (LOKI_DIR               ${CMAKE_CURRENT_SOURCE_DIR}/../../Loki)
set (SUFFIX_TREE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/../../SuffixTree)
set (GOOGLE_TEST_INC_DIR	${CMAKE_CURRENT_SOURCE_DIR}/../../googletest-master/googletest/include)

set (SRCFOLDERS
		${libIMUSANT_TESTS_DIR}/DomainObjects
        ${libIMUSANT_TESTS_DIR}/Converters
		${libIMUSANT_TESTS_DIR}/Utilities
		)

set (INCFOLDERS
		${libIMUSANT_DIR}
		${IMUSANT_TESTS_DIR}/Utilities
		${libIMUSANT_DIR}/DomainObjects/inc
		${libIMUSANT_DIR}/Utilities/inc
		${libIMUSANT_DIR}/FileProcessing/inc
		${libIMUSANT_DIR}/Converters/MusicXML_v3
		${libIMUSANT_DIR}/Converters/MusicXML_v3/inc
		${libIMUSANT_DIR}/Converters/MusicXML_v3/shared/inc
		${LOKI_DIR}
		${SUFFIX_TREE_DIR}
		${GOOGLE_TEST_INC_DIR}
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
	set(HEADERS ${HEADERS} "${folder}/*.h")		# add header files
	set(INCL ${INCL} "${folder}")				# add include folders
endforeach(folder)
file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})


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

add_executable(${target} ${SRC} )


###############  Targeted Libraries ###########
TARGET_LINK_LIBRARIES(${target} libmusicxml2)
TARGET_LINK_LIBRARIES(${target} libIMUSANT)
TARGET_LINK_LIBRARIES(${target} gtest)
TARGET_LINK_LIBRARIES(${target} ${BOOST_FILESYSTEM_LIB})
TARGET_LINK_LIBRARIES(${target} ${BOOST_SYSTEM_LIB})


set_target_properties (${target} PROPERTIES
			FRAMEWORK TRUE
			VERSION ${VERSION}
			FRAMEWORK_VERSION ${VERSION}
			PUBLIC_HEADER "${COREH}"
			DEFINE_SYMBOL LIBMUSICXML_EXPORTS
			MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${STRVERS}
			MACOSX_FRAMEWORK_BUNDLE_VERSION ${SSTRVERS}
)


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
