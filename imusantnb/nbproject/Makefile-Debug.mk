#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1162190469/suffix_main.o \
	${OBJECTDIR}/_ext/1062344872/IMUSANT_collectionvisitor.o \
	${OBJECTDIR}/_ext/1062344872/IMUSANT_contour_symbol.o \
	${OBJECTDIR}/_ext/1062344872/IMUSANT_interval.o \
	${OBJECTDIR}/_ext/1062344872/IMUSANT_interval_vector.o \
	${OBJECTDIR}/_ext/1062344872/IMUSANT_ivec_collection.o \
	${OBJECTDIR}/_ext/1062344872/IMUSANT_processing.o \
	${OBJECTDIR}/_ext/1062344872/IMUSANT_record.o \
	${OBJECTDIR}/_ext/1062344872/IMUSANT_rvec_collection.o \
	${OBJECTDIR}/_ext/719817117/imusantcat_main.o \
	${OBJECTDIR}/_ext/856625893/Diff.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_XMLFile.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_XMLReader.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_XMLVisitor.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_barline.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_chord.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_comment.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_conversions.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_duration.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_element.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_key.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_measure.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_note.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_part.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_partlist.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_pitch.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_score.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_types.o \
	${OBJECTDIR}/_ext/222917006/IMUSANT_visitor.o \
	${OBJECTDIR}/_ext/222917006/TXML2IMUSANTVisitor.o \
	${OBJECTDIR}/_ext/2104075236/my_main.o \
	${OBJECTDIR}/_ext/2104075236/test_tree.o \
	${OBJECTDIR}/_ext/2104075236/tree_example.o \
	${OBJECTDIR}/_ext/752117920/IMusicXMLReader.o \
	${OBJECTDIR}/_ext/752117920/IMusicXMLVisitor.o \
	${OBJECTDIR}/_ext/752117920/Iexpat.o \
	${OBJECTDIR}/_ext/752117920/TArpeggiate.o \
	${OBJECTDIR}/_ext/752117920/TAttributes.o \
	${OBJECTDIR}/_ext/752117920/TBackupForward.o \
	${OBJECTDIR}/_ext/752117920/TBarline.o \
	${OBJECTDIR}/_ext/752117920/TChord.o \
	${OBJECTDIR}/_ext/752117920/TClef.o \
	${OBJECTDIR}/_ext/752117920/TDirection.o \
	${OBJECTDIR}/_ext/752117920/TFiguredBass.o \
	${OBJECTDIR}/_ext/752117920/THarmony.o \
	${OBJECTDIR}/_ext/752117920/TIdentification.o \
	${OBJECTDIR}/_ext/752117920/TKey.o \
	${OBJECTDIR}/_ext/752117920/TMeasure.o \
	${OBJECTDIR}/_ext/752117920/TMeasureStyle.o \
	${OBJECTDIR}/_ext/752117920/TMidiDevice.o \
	${OBJECTDIR}/_ext/752117920/TMidiInstrument.o \
	${OBJECTDIR}/_ext/752117920/TMusicXMLFile.o \
	${OBJECTDIR}/_ext/752117920/TNotation.o \
	${OBJECTDIR}/_ext/752117920/TNote.o \
	${OBJECTDIR}/_ext/752117920/TOrnaments.o \
	${OBJECTDIR}/_ext/752117920/TOtherDirections.o \
	${OBJECTDIR}/_ext/752117920/TPart.o \
	${OBJECTDIR}/_ext/752117920/TPartGroup.o \
	${OBJECTDIR}/_ext/752117920/TPartList.o \
	${OBJECTDIR}/_ext/752117920/TPitch.o \
	${OBJECTDIR}/_ext/752117920/TRational.o \
	${OBJECTDIR}/_ext/752117920/TRoutedVisitor.o \
	${OBJECTDIR}/_ext/752117920/TScore.o \
	${OBJECTDIR}/_ext/752117920/TScoreHeader.o \
	${OBJECTDIR}/_ext/752117920/TScoreInstrument.o \
	${OBJECTDIR}/_ext/752117920/TScorePart.o \
	${OBJECTDIR}/_ext/752117920/TScorePartwise.o \
	${OBJECTDIR}/_ext/752117920/TScoreTimewise.o \
	${OBJECTDIR}/_ext/752117920/TSound.o \
	${OBJECTDIR}/_ext/752117920/TStaffDetails.o \
	${OBJECTDIR}/_ext/752117920/TTechnical.o \
	${OBJECTDIR}/_ext/752117920/TTimeModification.o \
	${OBJECTDIR}/_ext/752117920/TTimeSign.o \
	${OBJECTDIR}/_ext/752117920/TTranspose.o \
	${OBJECTDIR}/_ext/752117920/TWork.o \
	${OBJECTDIR}/_ext/752117920/common.o \
	${OBJECTDIR}/_ext/752117920/conversions.o \
	${OBJECTDIR}/_ext/752117920/smartpointer.o \
	${OBJECTDIR}/_ext/752117920/xml.o \
	${OBJECTDIR}/_ext/752117920/xmllex.o \
	${OBJECTDIR}/_ext/752117920/xmlparse.o \
	${OBJECTDIR}/_ext/410737512/ContextVisitors.o \
	${OBJECTDIR}/_ext/410737512/MusicXML2Guido.o \
	${OBJECTDIR}/_ext/410737512/RandomMusic.o \
	${OBJECTDIR}/_ext/410737512/RawTranspose.o \
	${OBJECTDIR}/_ext/410737512/ReadWrite.o \
	${OBJECTDIR}/_ext/542922170/TMidiContextVisitor.o \
	${OBJECTDIR}/_ext/542922170/TRolledVisitor.o \
	${OBJECTDIR}/_ext/542922170/TScanVisitor.o \
	${OBJECTDIR}/_ext/542922170/TUnrolledVisitor.o \
	${OBJECTDIR}/_ext/542922170/TXML2GuidoVisitor.o \
	${OBJECTDIR}/_ext/542922170/guido.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imusantnb

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imusantnb: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imusantnb ${OBJECTFILES} ${LDLIBSOPTIONS} -framework boost

${OBJECTDIR}/_ext/1162190469/suffix_main.o: ../imusant\ old/Suffix\ tree/suffix_main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1162190469
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1162190469/suffix_main.o ../imusant\ old/Suffix\ tree/suffix_main.cpp

${OBJECTDIR}/_ext/1062344872/IMUSANT_collectionvisitor.o: ../imusant\ old/imusantcat/src/IMUSANT_collectionvisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062344872
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062344872/IMUSANT_collectionvisitor.o ../imusant\ old/imusantcat/src/IMUSANT_collectionvisitor.cpp

${OBJECTDIR}/_ext/1062344872/IMUSANT_contour_symbol.o: ../imusant\ old/imusantcat/src/IMUSANT_contour_symbol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062344872
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062344872/IMUSANT_contour_symbol.o ../imusant\ old/imusantcat/src/IMUSANT_contour_symbol.cpp

${OBJECTDIR}/_ext/1062344872/IMUSANT_interval.o: ../imusant\ old/imusantcat/src/IMUSANT_interval.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062344872
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062344872/IMUSANT_interval.o ../imusant\ old/imusantcat/src/IMUSANT_interval.cpp

${OBJECTDIR}/_ext/1062344872/IMUSANT_interval_vector.o: ../imusant\ old/imusantcat/src/IMUSANT_interval_vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062344872
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062344872/IMUSANT_interval_vector.o ../imusant\ old/imusantcat/src/IMUSANT_interval_vector.cpp

${OBJECTDIR}/_ext/1062344872/IMUSANT_ivec_collection.o: ../imusant\ old/imusantcat/src/IMUSANT_ivec_collection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062344872
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062344872/IMUSANT_ivec_collection.o ../imusant\ old/imusantcat/src/IMUSANT_ivec_collection.cpp

${OBJECTDIR}/_ext/1062344872/IMUSANT_processing.o: ../imusant\ old/imusantcat/src/IMUSANT_processing.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062344872
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062344872/IMUSANT_processing.o ../imusant\ old/imusantcat/src/IMUSANT_processing.cpp

${OBJECTDIR}/_ext/1062344872/IMUSANT_record.o: ../imusant\ old/imusantcat/src/IMUSANT_record.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062344872
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062344872/IMUSANT_record.o ../imusant\ old/imusantcat/src/IMUSANT_record.cpp

${OBJECTDIR}/_ext/1062344872/IMUSANT_rvec_collection.o: ../imusant\ old/imusantcat/src/IMUSANT_rvec_collection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1062344872
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1062344872/IMUSANT_rvec_collection.o ../imusant\ old/imusantcat/src/IMUSANT_rvec_collection.cpp

${OBJECTDIR}/_ext/719817117/imusantcat_main.o: ../imusant\ old/imusantcat_main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/719817117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/719817117/imusantcat_main.o ../imusant\ old/imusantcat_main.cpp

${OBJECTDIR}/_ext/856625893/Diff.o: ../imusant\ old/mindiff/Diff.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/856625893
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/856625893/Diff.o ../imusant\ old/mindiff/Diff.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_XMLFile.o: ../imusant\ old/src/IMUSANT_XMLFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_XMLFile.o ../imusant\ old/src/IMUSANT_XMLFile.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_XMLReader.o: ../imusant\ old/src/IMUSANT_XMLReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_XMLReader.o ../imusant\ old/src/IMUSANT_XMLReader.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_XMLVisitor.o: ../imusant\ old/src/IMUSANT_XMLVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_XMLVisitor.o ../imusant\ old/src/IMUSANT_XMLVisitor.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_barline.o: ../imusant\ old/src/IMUSANT_barline.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_barline.o ../imusant\ old/src/IMUSANT_barline.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_chord.o: ../imusant\ old/src/IMUSANT_chord.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_chord.o ../imusant\ old/src/IMUSANT_chord.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_comment.o: ../imusant\ old/src/IMUSANT_comment.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_comment.o ../imusant\ old/src/IMUSANT_comment.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_conversions.o: ../imusant\ old/src/IMUSANT_conversions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_conversions.o ../imusant\ old/src/IMUSANT_conversions.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_duration.o: ../imusant\ old/src/IMUSANT_duration.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_duration.o ../imusant\ old/src/IMUSANT_duration.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_element.o: ../imusant\ old/src/IMUSANT_element.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_element.o ../imusant\ old/src/IMUSANT_element.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_key.o: ../imusant\ old/src/IMUSANT_key.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_key.o ../imusant\ old/src/IMUSANT_key.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_measure.o: ../imusant\ old/src/IMUSANT_measure.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_measure.o ../imusant\ old/src/IMUSANT_measure.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_note.o: ../imusant\ old/src/IMUSANT_note.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_note.o ../imusant\ old/src/IMUSANT_note.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_part.o: ../imusant\ old/src/IMUSANT_part.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_part.o ../imusant\ old/src/IMUSANT_part.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_partlist.o: ../imusant\ old/src/IMUSANT_partlist.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_partlist.o ../imusant\ old/src/IMUSANT_partlist.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_pitch.o: ../imusant\ old/src/IMUSANT_pitch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_pitch.o ../imusant\ old/src/IMUSANT_pitch.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_score.o: ../imusant\ old/src/IMUSANT_score.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_score.o ../imusant\ old/src/IMUSANT_score.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_types.o: ../imusant\ old/src/IMUSANT_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_types.o ../imusant\ old/src/IMUSANT_types.cpp

${OBJECTDIR}/_ext/222917006/IMUSANT_visitor.o: ../imusant\ old/src/IMUSANT_visitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/IMUSANT_visitor.o ../imusant\ old/src/IMUSANT_visitor.cpp

${OBJECTDIR}/_ext/222917006/TXML2IMUSANTVisitor.o: ../imusant\ old/src/TXML2IMUSANTVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/222917006
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/222917006/TXML2IMUSANTVisitor.o ../imusant\ old/src/TXML2IMUSANTVisitor.cpp

${OBJECTDIR}/_ext/2104075236/my_main.o: ../imusant\ old/tree-2.03/my_main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2104075236
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2104075236/my_main.o ../imusant\ old/tree-2.03/my_main.cpp

${OBJECTDIR}/_ext/2104075236/test_tree.o: ../imusant\ old/tree-2.03/test_tree.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/2104075236
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2104075236/test_tree.o ../imusant\ old/tree-2.03/test_tree.cc

${OBJECTDIR}/_ext/2104075236/tree_example.o: ../imusant\ old/tree-2.03/tree_example.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/2104075236
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2104075236/tree_example.o ../imusant\ old/tree-2.03/tree_example.cc

${OBJECTDIR}/_ext/752117920/IMusicXMLReader.o: ../libMusicXML-1.00-src/src/core/IMusicXMLReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/IMusicXMLReader.o ../libMusicXML-1.00-src/src/core/IMusicXMLReader.cpp

${OBJECTDIR}/_ext/752117920/IMusicXMLVisitor.o: ../libMusicXML-1.00-src/src/core/IMusicXMLVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/IMusicXMLVisitor.o ../libMusicXML-1.00-src/src/core/IMusicXMLVisitor.cpp

${OBJECTDIR}/_ext/752117920/Iexpat.o: ../libMusicXML-1.00-src/src/core/Iexpat.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/Iexpat.o ../libMusicXML-1.00-src/src/core/Iexpat.cpp

${OBJECTDIR}/_ext/752117920/TArpeggiate.o: ../libMusicXML-1.00-src/src/core/TArpeggiate.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TArpeggiate.o ../libMusicXML-1.00-src/src/core/TArpeggiate.cpp

${OBJECTDIR}/_ext/752117920/TAttributes.o: ../libMusicXML-1.00-src/src/core/TAttributes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TAttributes.o ../libMusicXML-1.00-src/src/core/TAttributes.cpp

${OBJECTDIR}/_ext/752117920/TBackupForward.o: ../libMusicXML-1.00-src/src/core/TBackupForward.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TBackupForward.o ../libMusicXML-1.00-src/src/core/TBackupForward.cpp

${OBJECTDIR}/_ext/752117920/TBarline.o: ../libMusicXML-1.00-src/src/core/TBarline.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TBarline.o ../libMusicXML-1.00-src/src/core/TBarline.cpp

${OBJECTDIR}/_ext/752117920/TChord.o: ../libMusicXML-1.00-src/src/core/TChord.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TChord.o ../libMusicXML-1.00-src/src/core/TChord.cpp

${OBJECTDIR}/_ext/752117920/TClef.o: ../libMusicXML-1.00-src/src/core/TClef.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TClef.o ../libMusicXML-1.00-src/src/core/TClef.cpp

${OBJECTDIR}/_ext/752117920/TDirection.o: ../libMusicXML-1.00-src/src/core/TDirection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TDirection.o ../libMusicXML-1.00-src/src/core/TDirection.cpp

${OBJECTDIR}/_ext/752117920/TFiguredBass.o: ../libMusicXML-1.00-src/src/core/TFiguredBass.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TFiguredBass.o ../libMusicXML-1.00-src/src/core/TFiguredBass.cpp

${OBJECTDIR}/_ext/752117920/THarmony.o: ../libMusicXML-1.00-src/src/core/THarmony.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/THarmony.o ../libMusicXML-1.00-src/src/core/THarmony.cpp

${OBJECTDIR}/_ext/752117920/TIdentification.o: ../libMusicXML-1.00-src/src/core/TIdentification.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TIdentification.o ../libMusicXML-1.00-src/src/core/TIdentification.cpp

${OBJECTDIR}/_ext/752117920/TKey.o: ../libMusicXML-1.00-src/src/core/TKey.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TKey.o ../libMusicXML-1.00-src/src/core/TKey.cpp

${OBJECTDIR}/_ext/752117920/TMeasure.o: ../libMusicXML-1.00-src/src/core/TMeasure.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TMeasure.o ../libMusicXML-1.00-src/src/core/TMeasure.cpp

${OBJECTDIR}/_ext/752117920/TMeasureStyle.o: ../libMusicXML-1.00-src/src/core/TMeasureStyle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TMeasureStyle.o ../libMusicXML-1.00-src/src/core/TMeasureStyle.cpp

${OBJECTDIR}/_ext/752117920/TMidiDevice.o: ../libMusicXML-1.00-src/src/core/TMidiDevice.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TMidiDevice.o ../libMusicXML-1.00-src/src/core/TMidiDevice.cpp

${OBJECTDIR}/_ext/752117920/TMidiInstrument.o: ../libMusicXML-1.00-src/src/core/TMidiInstrument.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TMidiInstrument.o ../libMusicXML-1.00-src/src/core/TMidiInstrument.cpp

${OBJECTDIR}/_ext/752117920/TMusicXMLFile.o: ../libMusicXML-1.00-src/src/core/TMusicXMLFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TMusicXMLFile.o ../libMusicXML-1.00-src/src/core/TMusicXMLFile.cpp

${OBJECTDIR}/_ext/752117920/TNotation.o: ../libMusicXML-1.00-src/src/core/TNotation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TNotation.o ../libMusicXML-1.00-src/src/core/TNotation.cpp

${OBJECTDIR}/_ext/752117920/TNote.o: ../libMusicXML-1.00-src/src/core/TNote.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TNote.o ../libMusicXML-1.00-src/src/core/TNote.cpp

${OBJECTDIR}/_ext/752117920/TOrnaments.o: ../libMusicXML-1.00-src/src/core/TOrnaments.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TOrnaments.o ../libMusicXML-1.00-src/src/core/TOrnaments.cpp

${OBJECTDIR}/_ext/752117920/TOtherDirections.o: ../libMusicXML-1.00-src/src/core/TOtherDirections.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TOtherDirections.o ../libMusicXML-1.00-src/src/core/TOtherDirections.cpp

${OBJECTDIR}/_ext/752117920/TPart.o: ../libMusicXML-1.00-src/src/core/TPart.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TPart.o ../libMusicXML-1.00-src/src/core/TPart.cpp

${OBJECTDIR}/_ext/752117920/TPartGroup.o: ../libMusicXML-1.00-src/src/core/TPartGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TPartGroup.o ../libMusicXML-1.00-src/src/core/TPartGroup.cpp

${OBJECTDIR}/_ext/752117920/TPartList.o: ../libMusicXML-1.00-src/src/core/TPartList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TPartList.o ../libMusicXML-1.00-src/src/core/TPartList.cpp

${OBJECTDIR}/_ext/752117920/TPitch.o: ../libMusicXML-1.00-src/src/core/TPitch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TPitch.o ../libMusicXML-1.00-src/src/core/TPitch.cpp

${OBJECTDIR}/_ext/752117920/TRational.o: ../libMusicXML-1.00-src/src/core/TRational.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TRational.o ../libMusicXML-1.00-src/src/core/TRational.cpp

${OBJECTDIR}/_ext/752117920/TRoutedVisitor.o: ../libMusicXML-1.00-src/src/core/TRoutedVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TRoutedVisitor.o ../libMusicXML-1.00-src/src/core/TRoutedVisitor.cpp

${OBJECTDIR}/_ext/752117920/TScore.o: ../libMusicXML-1.00-src/src/core/TScore.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TScore.o ../libMusicXML-1.00-src/src/core/TScore.cpp

${OBJECTDIR}/_ext/752117920/TScoreHeader.o: ../libMusicXML-1.00-src/src/core/TScoreHeader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TScoreHeader.o ../libMusicXML-1.00-src/src/core/TScoreHeader.cpp

${OBJECTDIR}/_ext/752117920/TScoreInstrument.o: ../libMusicXML-1.00-src/src/core/TScoreInstrument.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TScoreInstrument.o ../libMusicXML-1.00-src/src/core/TScoreInstrument.cpp

${OBJECTDIR}/_ext/752117920/TScorePart.o: ../libMusicXML-1.00-src/src/core/TScorePart.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TScorePart.o ../libMusicXML-1.00-src/src/core/TScorePart.cpp

${OBJECTDIR}/_ext/752117920/TScorePartwise.o: ../libMusicXML-1.00-src/src/core/TScorePartwise.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TScorePartwise.o ../libMusicXML-1.00-src/src/core/TScorePartwise.cpp

${OBJECTDIR}/_ext/752117920/TScoreTimewise.o: ../libMusicXML-1.00-src/src/core/TScoreTimewise.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TScoreTimewise.o ../libMusicXML-1.00-src/src/core/TScoreTimewise.cpp

${OBJECTDIR}/_ext/752117920/TSound.o: ../libMusicXML-1.00-src/src/core/TSound.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TSound.o ../libMusicXML-1.00-src/src/core/TSound.cpp

${OBJECTDIR}/_ext/752117920/TStaffDetails.o: ../libMusicXML-1.00-src/src/core/TStaffDetails.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TStaffDetails.o ../libMusicXML-1.00-src/src/core/TStaffDetails.cpp

${OBJECTDIR}/_ext/752117920/TTechnical.o: ../libMusicXML-1.00-src/src/core/TTechnical.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TTechnical.o ../libMusicXML-1.00-src/src/core/TTechnical.cpp

${OBJECTDIR}/_ext/752117920/TTimeModification.o: ../libMusicXML-1.00-src/src/core/TTimeModification.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TTimeModification.o ../libMusicXML-1.00-src/src/core/TTimeModification.cpp

${OBJECTDIR}/_ext/752117920/TTimeSign.o: ../libMusicXML-1.00-src/src/core/TTimeSign.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TTimeSign.o ../libMusicXML-1.00-src/src/core/TTimeSign.cpp

${OBJECTDIR}/_ext/752117920/TTranspose.o: ../libMusicXML-1.00-src/src/core/TTranspose.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TTranspose.o ../libMusicXML-1.00-src/src/core/TTranspose.cpp

${OBJECTDIR}/_ext/752117920/TWork.o: ../libMusicXML-1.00-src/src/core/TWork.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/TWork.o ../libMusicXML-1.00-src/src/core/TWork.cpp

${OBJECTDIR}/_ext/752117920/common.o: ../libMusicXML-1.00-src/src/core/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/common.o ../libMusicXML-1.00-src/src/core/common.cpp

${OBJECTDIR}/_ext/752117920/conversions.o: ../libMusicXML-1.00-src/src/core/conversions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/conversions.o ../libMusicXML-1.00-src/src/core/conversions.cpp

${OBJECTDIR}/_ext/752117920/smartpointer.o: ../libMusicXML-1.00-src/src/core/smartpointer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/smartpointer.o ../libMusicXML-1.00-src/src/core/smartpointer.cpp

${OBJECTDIR}/_ext/752117920/xml.o: ../libMusicXML-1.00-src/src/core/xml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/xml.o ../libMusicXML-1.00-src/src/core/xml.cpp

${OBJECTDIR}/_ext/752117920/xmllex.o: ../libMusicXML-1.00-src/src/core/xmllex.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/xmllex.o ../libMusicXML-1.00-src/src/core/xmllex.cpp

${OBJECTDIR}/_ext/752117920/xmlparse.o: ../libMusicXML-1.00-src/src/core/xmlparse.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/752117920
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/752117920/xmlparse.o ../libMusicXML-1.00-src/src/core/xmlparse.cpp

${OBJECTDIR}/_ext/410737512/ContextVisitors.o: ../libMusicXML-1.00-src/src/samples/ContextVisitors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/410737512
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/410737512/ContextVisitors.o ../libMusicXML-1.00-src/src/samples/ContextVisitors.cpp

${OBJECTDIR}/_ext/410737512/MusicXML2Guido.o: ../libMusicXML-1.00-src/src/samples/MusicXML2Guido.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/410737512
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/410737512/MusicXML2Guido.o ../libMusicXML-1.00-src/src/samples/MusicXML2Guido.cpp

${OBJECTDIR}/_ext/410737512/RandomMusic.o: ../libMusicXML-1.00-src/src/samples/RandomMusic.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/410737512
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/410737512/RandomMusic.o ../libMusicXML-1.00-src/src/samples/RandomMusic.cpp

${OBJECTDIR}/_ext/410737512/RawTranspose.o: ../libMusicXML-1.00-src/src/samples/RawTranspose.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/410737512
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/410737512/RawTranspose.o ../libMusicXML-1.00-src/src/samples/RawTranspose.cpp

${OBJECTDIR}/_ext/410737512/ReadWrite.o: ../libMusicXML-1.00-src/src/samples/ReadWrite.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/410737512
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/410737512/ReadWrite.o ../libMusicXML-1.00-src/src/samples/ReadWrite.cpp

${OBJECTDIR}/_ext/542922170/TMidiContextVisitor.o: ../libMusicXML-1.00-src/src/visitors/TMidiContextVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/542922170
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/542922170/TMidiContextVisitor.o ../libMusicXML-1.00-src/src/visitors/TMidiContextVisitor.cpp

${OBJECTDIR}/_ext/542922170/TRolledVisitor.o: ../libMusicXML-1.00-src/src/visitors/TRolledVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/542922170
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/542922170/TRolledVisitor.o ../libMusicXML-1.00-src/src/visitors/TRolledVisitor.cpp

${OBJECTDIR}/_ext/542922170/TScanVisitor.o: ../libMusicXML-1.00-src/src/visitors/TScanVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/542922170
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/542922170/TScanVisitor.o ../libMusicXML-1.00-src/src/visitors/TScanVisitor.cpp

${OBJECTDIR}/_ext/542922170/TUnrolledVisitor.o: ../libMusicXML-1.00-src/src/visitors/TUnrolledVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/542922170
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/542922170/TUnrolledVisitor.o ../libMusicXML-1.00-src/src/visitors/TUnrolledVisitor.cpp

${OBJECTDIR}/_ext/542922170/TXML2GuidoVisitor.o: ../libMusicXML-1.00-src/src/visitors/TXML2GuidoVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/542922170
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/542922170/TXML2GuidoVisitor.o ../libMusicXML-1.00-src/src/visitors/TXML2GuidoVisitor.cpp

${OBJECTDIR}/_ext/542922170/guido.o: ../libMusicXML-1.00-src/src/visitors/guido.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/542922170
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/542922170/guido.o ../libMusicXML-1.00-src/src/visitors/guido.cpp

${OBJECTDIR}/_ext/364893812/config.hpp.gch: /usr/local/include/boost/filesystem/config.hpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/364893812
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o "$@" /usr/local/include/boost/filesystem/config.hpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imusantnb

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
