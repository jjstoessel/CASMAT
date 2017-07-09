#######################################
# CMAKE CATSMAT
#######################################
cmake_minimum_required(VERSION 3.6)
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

set (CATSMAT_DIR 	                   		${CMAKE_CURRENT_SOURCE_DIR}/../../catsmat)
set (CATSMAT_ANALYSIS_DIR      				${CATSMAT_DIR}/Analysis)
set (CATSMAT_APPLICATION_DIR      			${CATSMAT_DIR}/Application)
set (CATSMAT_COUNTERPOINT_ANALYSIS_DIR      ${CATSMAT_DIR}/CounterpointAnalysis)
set (CATSMAT_GENERAL_ANALYSIS_DIR      		${CATSMAT_DIR}/GeneralAnalysis)
set (CATSMAT_SEGMENTATION_DIR      			${CATSMAT_DIR}/Segmentation)
set (CATSMAT_UTILITIES_DIR      			${CATSMAT_DIR}/Utilities)

set (LOKI_DIR               				${CATSMAT_DIR}/../Loki)
set (SUFFIX_TREE_DIR        				${CMAKE_CURRENT_SOURCE_DIR}/../../SuffixTree)

set (CATSMAT_ANALYSIS_SRC_DIR      				${CATSMAT_DIR}/Analysis/src)
set (CATSMAT_APPLICATION_SRC_DIR      			${CATSMAT_DIR}/Application)
set (CATSMAT_COUNTERPOINT_ANALYSIS_SRC_DIR      ${CATSMAT_DIR}/CounterpointAnalysis/src)
set (CATSMAT_GENERAL_ANALYSIS_SRC_DIR      		${CATSMAT_DIR}/GeneralAnalysis/src)
set (CATSMAT_SEGMENTATION_SRC_DIR      			${CATSMAT_DIR}/Segmentation/src)
set (CATSMAT_UTILITIES_SRC_DIR      			${CATSMAT_DIR}/Utilities/src)

set (CATSMAT_ANALYSIS_INC_DIR      				${CATSMAT_DIR}/Analysis/inc)
set (CATSMAT_APPLICATION_INC_DIR      			${CATSMAT_DIR}/Application)
set (CATSMAT_COUNTERPOINT_ANALYSIS_INC_DIR      ${CATSMAT_DIR}/CounterpointAnalysis/inc)
set (CATSMAT_GENERAL_ANALYSIS_INC_DIR      		${CATSMAT_DIR}/GeneralAnalysis/inc)
set (CATSMAT_SEGMENTATION_INC_DIR      			${CATSMAT_DIR}/Segmentation/inc)
set (CATSMAT_SEGMENTATION_LBDM_INC_DIR      	${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/inc)
set (CATSMAT_SEGMENTATION_FIXED_INC_DIR      	${CATSMAT_DIR}/Segmentation/FixedPeriodDetection/inc)
set (CATSMAT_UTILITIES_INC_DIR      			${CATSMAT_DIR}/Utilities)
set (LIBIMUSNT_HEADER_DIR						${CMAKE_BINARY_DIR}/catsmat/libIMUSANT/cmake/libIMUSANT.framework/Headers)

set (INCFOLDERS
		${CATSMAT_ANALYSIS_INC_DIR}
		${CATSMAT_APPLICATION_INC_DIR}
		${CATSMAT_COUNTERPOINT_ANALYSIS_INC_DIR}
		${CATSMAT_GENERAL_ANALYSIS_INC_DIR}
		${CATSMAT_SEGMENTATION_INC_DIR}
		${CATSMAT_SEGMENTATION_LBDM_INC_DIR}
		${CATSMAT_SEGMENTATION_FIXED_INC_DIR}
		${CATSMAT_UTILITIES_INC_DIR}
		${CATSMAT_DIR}
		${LOKI_DIR}
		${SUFFIX_TREE_DIR}
		${LIBIMUSNT_HEADER_DIR}
		)

set(SRC ${SRC}
		${CATSMAT_ANALYSIS_SRC_DIR}/IMUSANT_contour_suffixtree_builder.cpp
		${CATSMAT_ANALYSIS_SRC_DIR}/IMUSANT_generalised_interval_suffixtree_builder.cpp
		${CATSMAT_ANALYSIS_SRC_DIR}/IMUSANT_interval_suffixtree_builder.cpp
		${CATSMAT_ANALYSIS_SRC_DIR}/IMUSANT_pitch_suffixtree_builder.cpp
		${CATSMAT_ANALYSIS_SRC_DIR}/IMUSANT_repeated_interval_substring.cpp
		${CATSMAT_ANALYSIS_SRC_DIR}/IMUSANT_t_repeated_substring.cpp
		${CATSMAT_ANALYSIS_SRC_DIR}/IMUSANT_VectorMapAnalysisTypes.cpp

		${CATSMAT_APPLICATION_SRC_DIR}/CATSMAT_main.cpp
		${CATSMAT_APPLICATION_SRC_DIR}/CATSMAT_menu.cpp

		${CATSMAT_COUNTERPOINT_ANALYSIS_SRC_DIR}/CATSMAT_chord.cpp
		${CATSMAT_COUNTERPOINT_ANALYSIS_SRC_DIR}/CATSMAT_collectionvisitor.cpp
		${CATSMAT_COUNTERPOINT_ANALYSIS_SRC_DIR}/CATSMAT_cp_matrix.cpp
		${CATSMAT_COUNTERPOINT_ANALYSIS_SRC_DIR}/CATSMAT_dyad_sequences.cpp
		${CATSMAT_COUNTERPOINT_ANALYSIS_SRC_DIR}/CATSMAT_dyadtuple_sequences.cpp
		${CATSMAT_COUNTERPOINT_ANALYSIS_SRC_DIR}/CATSMAT_sonority_sequences.cpp
		${CATSMAT_COUNTERPOINT_ANALYSIS_SRC_DIR}/CATSMAT_TrigramSequences.cpp
		${CATSMAT_COUNTERPOINT_ANALYSIS_SRC_DIR}/CATSMAT_TrigramSuffixTreeBuilder.cpp

		${CATSMAT_GENERAL_ANALYSIS_SRC_DIR}/CATSMAT_canonic_techniques_tools.cpp
		${CATSMAT_GENERAL_ANALYSIS_SRC_DIR}/CATSMAT_partdata.cpp
		${CATSMAT_GENERAL_ANALYSIS_SRC_DIR}/CATSMAT_processing.cpp
		${CATSMAT_GENERAL_ANALYSIS_SRC_DIR}/CATSMAT_score_profile.tpp
		${CATSMAT_GENERAL_ANALYSIS_SRC_DIR}/CATSMAT_score_splitter.cpp
		${CATSMAT_GENERAL_ANALYSIS_SRC_DIR}/CATSMAT_score_profile_special.cpp
		${CATSMAT_GENERAL_ANALYSIS_SRC_DIR}/CATSMAT_scoredata.cpp
		${CATSMAT_GENERAL_ANALYSIS_SRC_DIR}/CATSMAT_scoredatacollector.cpp

		${CATSMAT_SEGMENTATION_SRC_DIR}/IMUSANT_segment.cpp
		${CATSMAT_SEGMENTATION_SRC_DIR}/IMUSANT_set_of_segment.cpp
		${CATSMAT_SEGMENTATION_SRC_DIR}/SegmentContext.cpp

		${CATSMAT_DIR}/Segmentation/FixedPeriodDetection/src/IMUSANT_fixed_period_segmenter.cpp
		${CATSMAT_DIR}/Segmentation/FixedPeriodDetection/src/IMUSANT_partlist_ordered_by_part_entry.cpp
		${CATSMAT_DIR}/Segmentation/FixedPeriodDetection/src/SegmentedScoreFixedPeriod.cpp

		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_interval_profile_LBDM.cpp
		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_LBDM_segmenter.cpp
		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_segmented_note_vectors.cpp
		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_segmented_part_LBDM.cpp
		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_segmented_profile_vectors.cpp
		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_weighted_strength_vectors.cpp
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
# set library target
if(APPLE OR MSVC)
	set(target CATSMAT)
else(APPLE OR MSVC)
	set(target CATSMAT)
endif(APPLE OR MSVC)

if(MSVC)
	enable_language(RC)
	set(LIBCONTENT ${CORESRC} ${COREH} ${CATSMAT_DIR}/win32/CATSMAT/CATSMAT.rc)
else(MSVC)
	set(LIBCONTENT ${CORESRC} ${COREH})
endif(MSVC)

add_executable(${target} ${SRC} )


###############  Targeted Libraries ###########
TARGET_LINK_LIBRARIES(${target} libmusicxml2)
TARGET_LINK_LIBRARIES(${target} libIMUSANT)
#TARGET_LINK_LIBRARIES(${target} gtest)
TARGET_LINK_LIBRARIES(${target} ${BOOST_FILESYSTEM_LIB})
TARGET_LINK_LIBRARIES(${target} ${BOOST_SYSTEM_LIB})


#set_target_properties (${target} PROPERTIES
#			FRAMEWORK FALSE
#			VERSION ${VERSION}      # REVISIT
#		#	PUBLIC_HEADER "${COREH}"
#		#	DEFINE_SYMBOL LIBMUSICXML_EXPORTS
#		#	MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${STRVERS}
#		#	MACOSX_FRAMEWORK_BUNDLE_VERSION ${SSTRVERS}
#)


#######################################
# install setup
if(NOT APPLE)
install ( TARGETS ${target} ${TOOLS}
	RUNTIME DESTINATION bin
    	LIBRARY DESTINATION lib
    	ARCHIVE DESTINATION lib
    	FRAMEWORK DESTINATION "/Library/Frameworks" CONFIGURATIONS Release
    	PUBLIC_HEADER DESTINATION include/catsmat
)
endif()
