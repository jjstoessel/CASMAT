#######################################
# CMAKE CATSMAT_TESTS
#######################################
# Note: set environmental variable DYLD_LIBRARY_PATH=/usr/local/boost/lib (or custom directory)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()

# This file contains all the paths for the CATSMAT code that we are testing.
include(${CMAKE_CURRENT_SOURCE_DIR}/../../catsmat/cmake/CMakeCatsmatFiles.txt)

set (CATSMAT_TEST_DIR				${CMAKE_CURRENT_SOURCE_DIR}/..)
set (CATSMAT_SEGMENTATION_TEST_DIR	${CATSMAT_TEST_DIR}/Segmentation)
set (GOOGLE_TEST_INC_DIR			${CMAKE_CURRENT_SOURCE_DIR}/../../googletest-master/googletest/include)

set (CATSMAT_TEST_DATA_DIR 	       	${CATSMAT_TEST_DIR}/testdata)
set (CATSMAT_TEST_DATA_BINARY_DIR   ${CMAKE_CURRENT_BINARY_DIR}/testdata)

set (INCFOLDERS ${INCFOLDERS}
		${CATSMAT_TEST_DIR}
		${CATSMAT_SEGMENTATION_TEST_DIR}
		${GOOGLE_TEST_INC_DIR}
		)

set(SRC ${SRC}
		${CATSMAT_TEST_DIR}/CATSMAT_canonic_techniques_tools_tests.cpp
		${CATSMAT_TEST_DIR}/CATSMAT_cp_matrix_Test.cpp
		${CATSMAT_TEST_DIR}/CATSMAT_dyad_sequences_Test.cpp
		${CATSMAT_TEST_DIR}/CATSMAT_dyadtuple_sequences_Tests.cpp
		${CATSMAT_TEST_DIR}/CATSMAT_scoredatacollector_tests.cpp
		${CATSMAT_TEST_DIR}/CATSMAT_sonority_sequences_Tests.cpp
		${CATSMAT_TEST_DIR}/CATSMAT_test_utility.cpp
		${CATSMAT_TEST_DIR}/CATSMAT_trigramsequences_tests.cpp
		${CATSMAT_SEGMENTATION_TEST_DIR}/IMUSANT_interval_profile_LBDM_Tests.cpp
		${CATSMAT_SEGMENTATION_TEST_DIR}/PartlistOrderedByPartEntry_Tests.cpp
		${CATSMAT_SEGMENTATION_TEST_DIR}/Segment_Tests.cpp
		${CATSMAT_SEGMENTATION_TEST_DIR}/LBDM_SegmentedPart_Tests.cpp
		${CATSMAT_SEGMENTATION_TEST_DIR}/SegmentedScoreFixedPeriod_Tests.cpp
		${CATSMAT_TEST_DIR}/main.cpp
		)

set(HEADERS ${HEADERS}
		${CATSMAT_TEST_DIR}/CATSMAT_canonic_techniques_tools_expected.h
		${CATSMAT_TEST_DIR}/CATSMAT_cp_matrix_Expected.h
		${CATSMAT_TEST_DIR}/CATSMAT_cp_matrix_Josquin_MAF_Kyrie_Expected.h
		${CATSMAT_TEST_DIR}/CATSMAT_cp_matrix_Josquin_Missa_LHASVM_Expected.h
		${CATSMAT_TEST_DIR}/CATSMAT_cp_matrix_Kyrie_Expected.h
		${CATSMAT_TEST_DIR}/CATSMAT_cp_matrix_Sanctus_Expected.h
		${CATSMAT_TEST_DIR}/CATSMAT_dyad_sequences_Expected.h
		${CATSMAT_TEST_DIR}/CATSMAT_dyadtuple_sequences_Expected.h
		${CATSMAT_TEST_DIR}/CATSMAT_scoredatacollector_tests.h
		${CATSMAT_TEST_DIR}/CATSMAT_sonority_sequences_Expected.h
		${CATSMAT_TEST_DIR}/CATSMAT_test_utility.h
		${CATSMAT_TEST_DIR}/CATSMAT_trigramsequences_expected.h
		${CATSMAT_SEGMENTATION_TEST_DIR}/LBDM_SegmentedPart_Expected.h
)

foreach(folder ${INCFOLDERS})
	set(INCL ${INCL} "${folder}")				# add include folders
endforeach(folder)
file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})


# set includes
include_directories( ${INCL})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)


# create the build target and the executable
#set(target CATSMAT_Test)
#add_executable(${target} ${SRC} )

#find boost
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
	set(target CATSMAT_Test)
	add_executable(${target} ${SRC} ${HEADERS})
	TARGET_LINK_LIBRARIES(${target} libmusicxml2; libIMUSANT; gtest; ${Boost_LIBRARIES}  )
endif()


# Targeted Libraries
#TARGET_LINK_LIBRARIES(${target} libmusicxml2)
#TARGET_LINK_LIBRARIES(${target} libIMUSANT)
#TARGET_LINK_LIBRARIES(${target} gtest)
#TARGET_LINK_LIBRARIES(${target} ${BOOST_FILESYSTEM_LIB})
#TARGET_LINK_LIBRARIES(${target} ${BOOST_SYSTEM_LIB})


# Copy the test data files.
set(TEST_DATA ${TEST_DATA}
		Anon-Talent_mest_pris_I-IV_115.xml
		Bononcini-RCM_canon_Musico_prattico_p105.xml
		Cerreto-CM_canon_Della_prattica_musica_p222.xml
		Du_Fay-Bien_veignes_vous.xml
		Josquin-Missa_Lhomme_arme_super_voces_musicales-Agnus_dei_II.xml
		Josquin_MAF_Christe.xml
		Josquin_MAF_Kyrie.xml
		Kyrie.xml
		Kyrie_2.xml
		Kyrie_TwoPartsOnly.xml
		LBDM_Segmented_Part_Test_1.xml
		LBDM_Segmented_Part_Test_2.xml
		LBDM_Segmented_Part_Test_3.xml
		Machaut-Ma_fin_est_mon_commencement.xml
		Ockeghem_Prenez_sur_moi_Cop.xml
		Sanctus.xml
		TestScore_1_Measure.xml
		TestScore_4_Measures.xml
		TestScore_4_Measures_WithQuaverPassingNotes.xml
		TestScore_4_Measures_WithSemiQuaverPassingNotes.xml
		Triplet-test.xml
		Yankee_Doodle.xml
		)

foreach(test_file  ${TEST_DATA})
	add_custom_command(
			TARGET ${target} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy  ${CATSMAT_TEST_DATA_DIR}/${test_file}  ${CATSMAT_TEST_DATA_BINARY_DIR}/${test_file}
	)
endforeach(test_file)


