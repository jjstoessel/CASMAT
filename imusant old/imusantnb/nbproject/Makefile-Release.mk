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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1092435682/suffix_main.o \
	${OBJECTDIR}/_ext/1472/imusantcat_main.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_XMLFile.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_XMLReader.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_XMLVisitor.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_barline.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_chord.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_comment.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_conversions.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_duration.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_element.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_key.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_measure.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_note.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_part.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_partlist.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_pitch.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_score.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_types.o \
	${OBJECTDIR}/_ext/1360937237/IMUSANT_visitor.o \
	${OBJECTDIR}/_ext/1360937237/TXML2IMUSANTVisitor.o \
	${OBJECTDIR}/_ext/74954625/my_main.o \
	${OBJECTDIR}/_ext/74954625/test_tree.o \
	${OBJECTDIR}/_ext/74954625/tree_example.o \
	${OBJECTDIR}/_ext/1472/xml2imusant_main.o


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
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imusantnb ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1092435682/suffix_main.o: ../Suffix\ tree/suffix_main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1092435682
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1092435682/suffix_main.o ../Suffix\ tree/suffix_main.cpp

${OBJECTDIR}/_ext/1472/imusantcat_main.o: ../imusantcat_main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1472/imusantcat_main.o ../imusantcat_main.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_XMLFile.o: ../src/IMUSANT_XMLFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_XMLFile.o ../src/IMUSANT_XMLFile.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_XMLReader.o: ../src/IMUSANT_XMLReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_XMLReader.o ../src/IMUSANT_XMLReader.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_XMLVisitor.o: ../src/IMUSANT_XMLVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_XMLVisitor.o ../src/IMUSANT_XMLVisitor.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_barline.o: ../src/IMUSANT_barline.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_barline.o ../src/IMUSANT_barline.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_chord.o: ../src/IMUSANT_chord.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_chord.o ../src/IMUSANT_chord.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_comment.o: ../src/IMUSANT_comment.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_comment.o ../src/IMUSANT_comment.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_conversions.o: ../src/IMUSANT_conversions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_conversions.o ../src/IMUSANT_conversions.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_duration.o: ../src/IMUSANT_duration.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_duration.o ../src/IMUSANT_duration.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_element.o: ../src/IMUSANT_element.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_element.o ../src/IMUSANT_element.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_key.o: ../src/IMUSANT_key.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_key.o ../src/IMUSANT_key.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_measure.o: ../src/IMUSANT_measure.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_measure.o ../src/IMUSANT_measure.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_note.o: ../src/IMUSANT_note.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_note.o ../src/IMUSANT_note.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_part.o: ../src/IMUSANT_part.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_part.o ../src/IMUSANT_part.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_partlist.o: ../src/IMUSANT_partlist.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_partlist.o ../src/IMUSANT_partlist.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_pitch.o: ../src/IMUSANT_pitch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_pitch.o ../src/IMUSANT_pitch.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_score.o: ../src/IMUSANT_score.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_score.o ../src/IMUSANT_score.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_types.o: ../src/IMUSANT_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_types.o ../src/IMUSANT_types.cpp

${OBJECTDIR}/_ext/1360937237/IMUSANT_visitor.o: ../src/IMUSANT_visitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/IMUSANT_visitor.o ../src/IMUSANT_visitor.cpp

${OBJECTDIR}/_ext/1360937237/TXML2IMUSANTVisitor.o: ../src/TXML2IMUSANTVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360937237/TXML2IMUSANTVisitor.o ../src/TXML2IMUSANTVisitor.cpp

${OBJECTDIR}/_ext/74954625/my_main.o: ../tree-2.03/my_main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/74954625
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74954625/my_main.o ../tree-2.03/my_main.cpp

${OBJECTDIR}/_ext/74954625/test_tree.o: ../tree-2.03/test_tree.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/74954625
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74954625/test_tree.o ../tree-2.03/test_tree.cc

${OBJECTDIR}/_ext/74954625/tree_example.o: ../tree-2.03/tree_example.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/74954625
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74954625/tree_example.o ../tree-2.03/tree_example.cc

${OBJECTDIR}/_ext/1472/xml2imusant_main.o: ../xml2imusant_main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1472/xml2imusant_main.o ../xml2imusant_main.cpp

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
