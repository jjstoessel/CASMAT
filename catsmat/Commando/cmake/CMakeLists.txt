#######################################
# CMAKE Commando
#######################################

cmake_minimum_required(VERSION 3.6)
project(libCommando)

set(CMAKE_CXX_STANDARD 11)

#######################################
# versions management
set (VERSION 1.00)
set (STRVERS "v.1.00")
set (SSTRVERS "1.00")

set (CATSMAT_DIR 	                   		${CMAKE_CURRENT_SOURCE_DIR}/../../)
set (CATSMAT_COMMANDO_DIR      				${CATSMAT_DIR}/Commando)

set(INCLUDE_DIRS ${CATSMAT_COMMANDO_DIR}/inc)

set(SOURCE_FILES ${CATSMAT_COMMANDO_DIR}/src/MultiMode.cpp ${CATSMAT_COMMANDO_DIR}/src/SingleMode.cpp)
file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCE_FILES})

foreach(folder ${INCLUDE_DIRS})
    set(HEADERS     ${HEADERS}      "${folder}/*.hpp")		# add header files
endforeach(folder)

file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})
file (GLOB EXPORTED_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)

set(LIBCONTENT ${CORESRC} ${COREH})

set(target libCommando)

include_directories(${INCLUDE_DIRS})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)

#add_library( ${target} SHARED ${LIBCONTENT})
add_library( ${target} ${SOURCE_FILES})


set_target_properties (${target} PROPERTIES
        #FRAMEWORK TRUE
        LINKER_LANGUAGE CXX
        VERSION ${VERSION}
        #FRAMEWORK_VERSION ${VERSION}
        PUBLIC_HEADER "${HEADERS}"
        DEFINE_SYMBOL LIBCOMMANDO_EXPORTS
        #MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${STRVERS}
        #MACOSX_FRAMEWORK_BUNDLE_VERSION ${SSTRVERS}
        )