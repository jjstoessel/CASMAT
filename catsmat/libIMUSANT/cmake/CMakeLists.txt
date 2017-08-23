#######################################
# CMAKE libIMUSANT
#######################################
#project(libIMUSANT)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()

if(UNIX)
	add_definitions(-Wall -DGCC)
endif(UNIX)

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET=10.5)
    set(MACOSX_RPATH ON)
endif(APPLE)

if(WIN32)
 add_definitions(-DWINVER=0x0400 -DWIN32)
 if(${CMAKE_GENERATOR} STREQUAL "Visual Studio 6")
  add_definitions(-DVC6)
 elseif(${CMAKE_GENERATOR} STREQUAL "Visual Studio 8 2005")
  add_definitions(-DVC2005)
 endif(${CMAKE_GENERATOR} STREQUAL "Visual Studio 6")
endif(WIN32)


#######################################
# set library target
if(APPLE OR MSVC)
    set(target libIMUSANT)
else(APPLE OR MSVC)
    set(target libIMUSANT)
endif(APPLE OR MSVC)


###############  BOOST LIBRARIES ###########
message("INSIDE libIMUSANT")
include(${CMAKE_SOURCE_DIR}/CMakeBoost.txt)

#######################################
# set directories, src and headers.

set (IMUSANT_DIR 	    ${CMAKE_CURRENT_SOURCE_DIR}/../../libIMUSANT)
set (SUFFIXTREE_DIR 	${CMAKE_CURRENT_SOURCE_DIR}/../../SuffixTree)
set (LOKI_DIR 	        ${CMAKE_CURRENT_SOURCE_DIR}/../../Loki)
set (LIBMUSICXML_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/../../libMusicXMLv3)

set (SRCFOLDERS
        ${IMUSANT_DIR}/DomainObjects/src
        ${IMUSANT_DIR}/Converters/MusicXML_v3/src
		${IMUSANT_DIR}/FileProcessing/src
		${IMUSANT_DIR}/Utilities/src
        )

set (EXPORTED_HEADER_FOLDERS
		${IMUSANT_DIR}/
		${IMUSANT_DIR}/DomainObjects/inc
		${IMUSANT_DIR}/Converters/MusicXML_v3
		${IMUSANT_DIR}/Converters/MusicXML_v3/inc
		${IMUSANT_DIR}/Converters/Shared/inc
		${IMUSANT_DIR}/FileProcessing/inc
		${IMUSANT_DIR}/Utilities/inc
		)

set (IMPORTED_HEADER_FOLDERS
		${SUFFIXTREE_DIR}
		${LIBMUSICXML_DIR}/libmusicxml-3.00-src/src
		${LIBMUSICXML_DIR}/libmusicxml-3.00-src/src/lib
		${LIBMUSICXML_DIR}/libmusicxml-3.00-src/src/visitors
		${LIBMUSICXML_DIR}/libmusicxml-3.00-src/src/parser
        )

foreach(folder ${SRCFOLDERS})
	set(SRC ${SRC} "${folder}/*.cpp")			# add source files
endforeach(folder)
file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})

foreach(folder ${EXPORTED_HEADER_FOLDERS})
	set(EXP_HEADERS ${EXP_HEADERS}  "${folder}/*.h")
	set(HEADERS     ${HEADERS}      "${folder}/*.h")		# add header files
	set(INCL        ${INCL}         "${folder}")				# add include folders
endforeach(folder)

foreach(folder ${IMPORTED_HEADER_FOLDERS})
	set(HEADERS ${HEADERS} "${folder}/*.h")		# add header files
	set(INCL ${INCL} "${folder}")				# add include folders
endforeach(folder)

file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})
file (GLOB EXPORTED_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${EXP_HEADERS})


#######################################
# set includes
include_directories( ${INCL})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)


if(MSVC)
	enable_language(RC)
	set(LIBCONTENT ${CORESRC} ${COREH} ${IMUSANT_DIR}/win32/libIMUSANT/libIMUSANT.rc)
else(MSVC)
	set(LIBCONTENT ${CORESRC} ${COREH})
endif(MSVC)


add_library(${target} SHARED ${LIBCONTENT})

###############  Targeted Libraries ###########
TARGET_LINK_LIBRARIES(${target} libmusicxml2)
TARGET_LINK_LIBRARIES(${target} ${Boost_LIBRARIES})

set_target_properties (${target} PROPERTIES 
			FRAMEWORK TRUE 
			VERSION ${VERSION}
			FRAMEWORK_VERSION ${VERSION}
			PUBLIC_HEADER "${EXPORTED_HEADERS}"
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
