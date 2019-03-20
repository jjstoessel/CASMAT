#######################################
# CMAKE IMUSANT_Test
#######################################

cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()


###############  BOOST LIBRARIES ###########
message("INSIDE libIMUSANT_Test")
include(${CMAKE_SOURCE_DIR}/CMakeBoost.txt)


#######################################
# set directories, src and headers.

set (libIMUSANT_TESTS_DIR 	           ${CMAKE_CURRENT_SOURCE_DIR}/../../libIMUSANT_Tests)
set (libIMUSANT_TEST_DATA_DIR 	       ${libIMUSANT_TESTS_DIR}/testdata/MusicXMLv3)
set (libIMUSANT_TEST_DATA_BINARY_DIR   ${CMAKE_CURRENT_BINARY_DIR}/IMUSANT_testdata/MusicXMLv3)

set (libIMUSANT_DIR 	    ${CMAKE_CURRENT_SOURCE_DIR}/../../libIMUSANT)
set (LOKI_DIR               ${CMAKE_CURRENT_SOURCE_DIR}/../../Loki)
set (SUFFIX_TREE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/../../SuffixTree)
set (GOOGLE_TEST_INC_DIR	${CMAKE_CURRENT_SOURCE_DIR}/../../googletest-master/googletest/include)

set (INCFOLDERS
		${libIMUSANT_DIR}
		${libIMUSANT_TESTS_DIR}/Utilities
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
		${libIMUSANT_TESTS_DIR}/Utilities/IMUSANT_test_utilities.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_duration_Tests.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_generalised_interval_Tests.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_interval_Tests.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_interval_Tests.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_key_Tests.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_measure_Tests.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_note_Tests.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_part_Tests.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_pitch_Tests.cpp
		${libIMUSANT_TESTS_DIR}/DomainObjects/IMUSANT_score_Tests.cpp
		${libIMUSANT_TESTS_DIR}/Converters/IMUSANT_mxmlv3_to_imusant_visitor_Tests.cpp
		)


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
# create target and add executable
#set(target libIMUSANT_Test)
#add_executable(${target} ${SRC} )
#${HEADERS}

#find boost
FIND_PACKAGE( Boost 1.57.0 COMPONENTS filesystem system REQUIRED )

if (Boost_FOUND)
	#report boost status
	message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
	message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
	message(STATUS "Boost_VERSION: ${Boost_VERSION}")
	# set includes
	include_directories( ${INCL};${Boost_INCLUDE_DIRS})
	set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)
	#set target, add executable and link libraries (default shared/dynamic libraries)
	set(target libIMUSANT_Test)
	add_executable(${target} ${SRC})   # We need the HEADERS to enable intellisence in CLion
	TARGET_LINK_LIBRARIES(${target} libmusicxml2; libIMUSANT; gtest; ${Boost_LIBRARIES}  )
endif()

###############  Targeted Libraries ###########
# TARGET_LINK_LIBRARIES(${target} ${Boost_LIBRARIES})
# TARGET_LINK_LIBRARIES(${target} libmusicxml2)
# TARGET_LINK_LIBRARIES(${target} libIMUSANT)
# TARGET_LINK_LIBRARIES(${target} gtest)


# Copy the test data files.
set(TEST_DATA ${TEST_DATA}
		MusicXML_ParserTest1.xml
		MusicXML_ParserTest2.xml
		MusicXML_ParserTest3.xml
		MusicXML_ParserTest4.xml
		MusicXML_ParserTest5.xml
		Josquin_MAF_Christe.xml
		Sanctus.xml
		Kyrie.xml
		Yankee_Doodle.xml
		MusicXML_ParserTest_Transpose1.xml
		RepeatedIntervalSubstrings_SimpleTest1.xml
		BeetAnGeSample.xml
		Dichterliebe01.xml
		Telemann.xml
		)

foreach(test_file  ${TEST_DATA})
	add_custom_command(
			TARGET ${target} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy  ${libIMUSANT_TEST_DATA_DIR}/${test_file}  ${libIMUSANT_TEST_DATA_BINARY_DIR}/${test_file}
	)
endforeach(test_file)
