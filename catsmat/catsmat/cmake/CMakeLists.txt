#######################################
# CMAKE CATSMAT
#######################################
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
# include("./CMakeCatsmatFiles.txt")

###########
###########
###############  BOOST LIBRARIES ###########
if (APPLE)
	set(BOOST_ROOT /usr/local/boost)
	#set(BOOST_LIBRARYDIR /usr/local/boost/lib)
	#set(BOOST_INCLUDEDIR /usr/local/boost/include/boost)
	#set(BOOST_FILESYSTEM_LIB  /usr/local/boost/lib/libboost_filesystem.dylib)
	#set(BOOST_SYSTEM_LIB      /usr/local/boost/lib/libboost_system.dylib)
else ()
	set(BOOST_ROOT "/usr/local/boost")
	set(BOOST_INCLUDEDIR "/usr/local/boost/include/boost")
	set(BOOST_FILESYSTEM_LIB  /usr/local/boost/lib/libboost_filesystem.dll.a)
	set(BOOST_SYSTEM_LIB      /usr/local/boost/lib/libboost_system.dll.a)
endif ()

#######################################
# set directories, src and headers.

set (CATSMAT_DIR 	                   		${CMAKE_CURRENT_SOURCE_DIR}/../../catsmat)
set (CATSMAT_ANALYSIS_DIR      				${CATSMAT_DIR}/Analysis)
set (CATSMAT_APPLICATION_DIR      			${CATSMAT_DIR}/Application)
set (CATSMAT_COUNTERPOINT_ANALYSIS_DIR      ${CATSMAT_DIR}/CounterpointAnalysis)
set (CATSMAT_GENERAL_ANALYSIS_DIR      		${CATSMAT_DIR}/GeneralAnalysis)
set (CATSMAT_SEGMENTATION_DIR      			${CATSMAT_DIR}/Segmentation)
set (CATSMAT_UTILITIES_DIR      			${CATSMAT_DIR}/Utilities)

set (LOKI_DIR               				${CATSMAT_DIR}/..)
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

		${CATSMAT_DIR}/Segmentation/FixedPeriodDetection/src/FixedPeriodSegmenter.cpp
		${CATSMAT_DIR}/Segmentation/FixedPeriodDetection/src/IMUSANT_partlist_ordered_by_part_entry.cpp
		${CATSMAT_DIR}/Segmentation/FixedPeriodDetection/src/SegmentedScoreFixedPeriod.cpp

		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_interval_profile_LBDM.cpp
		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/LBDM_Segmenter.cpp
		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_segmented_note_vectors.cpp
		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_segmented_part_LBDM.cpp
		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_segmented_profile_vectors.cpp
		${CATSMAT_DIR}/Segmentation/LocalBoundaryDetectionModel/src/IMUSANT_weighted_strength_vectors.cpp
		)

#
# If you are building the CATSMAT application then you will need to add these files into SRC in your own CMakeLists.txt
# file that is including this one.  This construct allows users of this file that have their own main() to build that
# instead of the main() in the CATSMAT project.
#
set (CATSMAT_APPLICATION_FILES
		${CATSMAT_APPLICATION_SRC_DIR}/CATSMAT_main.cpp
		${CATSMAT_APPLICATION_SRC_DIR}/CATSMAT_menu.cpp
		)

#########
#########



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
