
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
CXXFLAGS = -Wall -O3 -I../include 

TARGET = MusicXMLVisitors.a

lib : $(TARGET)

$(TARGET) : $(OBJ)
	ar -ru $(TARGET) $(OBJ)
	ranlib $(TARGET)

clean :
	rm -f $(TARGET) $(OBJ) xml

dep:
	makedepend -- $(CXXFLAGS) -- $(SRC)

# DO NOT DELETE

guido.o: ../include/guido.h ../include/exports.h ../include/smartpointer.h
guido.o: ../include/guidovisitor.h
TMidiContextVisitor.o: /usr/include/math.h /usr/include/features.h
TMidiContextVisitor.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
TMidiContextVisitor.o: /usr/include/bits/huge_val.h
TMidiContextVisitor.o: /usr/include/bits/mathdef.h
TMidiContextVisitor.o: /usr/include/bits/mathcalls.h ../include/LibMusicXML.h
TMidiContextVisitor.o: ../include/common.h ../include/exports.h
TMidiContextVisitor.o: ../include/TScoreVisitor.h ../include/smartclasses.h
TMidiContextVisitor.o: ../include/smartpointer.h ../include/bimap.h
TMidiContextVisitor.o: ../include/conversions.h ../include/TRational.h
TMidiContextVisitor.o: ../include/TArpeggiate.h ../include/TAttributes.h
TMidiContextVisitor.o: ../include/TClef.h ../include/TKey.h
TMidiContextVisitor.o: ../include/TTimeSign.h ../include/TTranspose.h
TMidiContextVisitor.o: ../include/TStaffDetails.h ../include/TMeasureStyle.h
TMidiContextVisitor.o: ../include/TBackupForward.h ../include/TBarline.h
TMidiContextVisitor.o: ../include/TOrnaments.h ../include/TChord.h
TMidiContextVisitor.o: ../include/TNote.h ../include/TPitch.h
TMidiContextVisitor.o: ../include/TNotation.h ../include/TScoreInstrument.h
TMidiContextVisitor.o: ../include/TTimeModification.h ../include/TDirection.h
TMidiContextVisitor.o: ../include/TSound.h ../include/TMidiInstrument.h
TMidiContextVisitor.o: ../include/TFiguredBass.h ../include/THarmony.h
TMidiContextVisitor.o: ../include/TTechnical.h ../include/TIdentification.h
TMidiContextVisitor.o: ../include/TMeasure.h ../include/TMidiDevice.h
TMidiContextVisitor.o: ../include/TMusicXMLFile.h ../include/TScore.h
TMidiContextVisitor.o: ../include/TScoreHeader.h ../include/TPartList.h
TMidiContextVisitor.o: ../include/TPartGroup.h ../include/TScorePart.h
TMidiContextVisitor.o: ../include/TWork.h ../include/xml.h
TMidiContextVisitor.o: ../include/TOtherDirections.h ../include/TPart.h
TMidiContextVisitor.o: ../include/TRoutedVisitor.h
TMidiContextVisitor.o: ../include/TScorePartwise.h
TMidiContextVisitor.o: ../include/TScoreTimewise.h
TMidiContextVisitor.o: ../include/TMidiContextVisitor.h
TMidiContextVisitor.o: ../include/TNodeVisitor.h
TRolledVisitor.o: ../include/TRolledVisitor.h ../include/exports.h
TRolledVisitor.o: ../include/TRoutedVisitor.h ../include/TScoreVisitor.h
TRolledVisitor.o: ../include/smartclasses.h ../include/smartpointer.h
TRolledVisitor.o: ../include/TNodeVisitor.h
TScanVisitor.o: ../include/TScanVisitor.h ../include/exports.h
TScanVisitor.o: ../include/bimap.h ../include/TRoutedVisitor.h
TScanVisitor.o: ../include/TScoreVisitor.h ../include/smartclasses.h
TScanVisitor.o: ../include/smartpointer.h ../include/LibMusicXML.h
TScanVisitor.o: ../include/common.h ../include/conversions.h
TScanVisitor.o: ../include/TRational.h ../include/TArpeggiate.h
TScanVisitor.o: ../include/TAttributes.h ../include/TClef.h ../include/TKey.h
TScanVisitor.o: ../include/TTimeSign.h ../include/TTranspose.h
TScanVisitor.o: ../include/TStaffDetails.h ../include/TMeasureStyle.h
TScanVisitor.o: ../include/TBackupForward.h ../include/TBarline.h
TScanVisitor.o: ../include/TOrnaments.h ../include/TChord.h
TScanVisitor.o: ../include/TNote.h ../include/TPitch.h ../include/TNotation.h
TScanVisitor.o: ../include/TScoreInstrument.h ../include/TTimeModification.h
TScanVisitor.o: ../include/TDirection.h ../include/TSound.h
TScanVisitor.o: ../include/TMidiInstrument.h ../include/TFiguredBass.h
TScanVisitor.o: ../include/THarmony.h ../include/TTechnical.h
TScanVisitor.o: ../include/TIdentification.h ../include/TMeasure.h
TScanVisitor.o: ../include/TMidiDevice.h ../include/TMusicXMLFile.h
TScanVisitor.o: ../include/TScore.h ../include/TScoreHeader.h
TScanVisitor.o: ../include/TPartList.h ../include/TPartGroup.h
TScanVisitor.o: ../include/TScorePart.h ../include/TWork.h ../include/xml.h
TScanVisitor.o: ../include/TOtherDirections.h ../include/TPart.h
TScanVisitor.o: ../include/TScorePartwise.h ../include/TScoreTimewise.h
TUnrolledVisitor.o: ../include/TUnrolledVisitor.h ../include/exports.h
TUnrolledVisitor.o: ../include/TRolledVisitor.h ../include/TRoutedVisitor.h
TUnrolledVisitor.o: ../include/TScoreVisitor.h ../include/smartclasses.h
TUnrolledVisitor.o: ../include/smartpointer.h ../include/TNodeVisitor.h
TUnrolledVisitor.o: ../include/LibMusicXML.h ../include/common.h
TUnrolledVisitor.o: ../include/bimap.h ../include/conversions.h
TUnrolledVisitor.o: ../include/TRational.h ../include/TArpeggiate.h
TUnrolledVisitor.o: ../include/TAttributes.h ../include/TClef.h
TUnrolledVisitor.o: ../include/TKey.h ../include/TTimeSign.h
TUnrolledVisitor.o: ../include/TTranspose.h ../include/TStaffDetails.h
TUnrolledVisitor.o: ../include/TMeasureStyle.h ../include/TBackupForward.h
TUnrolledVisitor.o: ../include/TBarline.h ../include/TOrnaments.h
TUnrolledVisitor.o: ../include/TChord.h ../include/TNote.h
TUnrolledVisitor.o: ../include/TPitch.h ../include/TNotation.h
TUnrolledVisitor.o: ../include/TScoreInstrument.h
TUnrolledVisitor.o: ../include/TTimeModification.h ../include/TDirection.h
TUnrolledVisitor.o: ../include/TSound.h ../include/TMidiInstrument.h
TUnrolledVisitor.o: ../include/TFiguredBass.h ../include/THarmony.h
TUnrolledVisitor.o: ../include/TTechnical.h ../include/TIdentification.h
TUnrolledVisitor.o: ../include/TMeasure.h ../include/TMidiDevice.h
TUnrolledVisitor.o: ../include/TMusicXMLFile.h ../include/TScore.h
TUnrolledVisitor.o: ../include/TScoreHeader.h ../include/TPartList.h
TUnrolledVisitor.o: ../include/TPartGroup.h ../include/TScorePart.h
TUnrolledVisitor.o: ../include/TWork.h ../include/xml.h
TUnrolledVisitor.o: ../include/TOtherDirections.h ../include/TPart.h
TUnrolledVisitor.o: ../include/TScorePartwise.h ../include/TScoreTimewise.h
TUnrolledVisitor.o: ../include/UTools.h
TXML2GuidoVisitor.o: ../include/TXML2GuidoVisitor.h ../include/exports.h
TXML2GuidoVisitor.o: ../include/TNotation.h ../include/common.h
TXML2GuidoVisitor.o: ../include/TScoreVisitor.h ../include/smartclasses.h
TXML2GuidoVisitor.o: ../include/smartpointer.h ../include/bimap.h
TXML2GuidoVisitor.o: ../include/conversions.h ../include/TRational.h
TXML2GuidoVisitor.o: ../include/TScorePartwise.h ../include/TMeasure.h
TXML2GuidoVisitor.o: ../include/TPart.h ../include/TScore.h
TXML2GuidoVisitor.o: ../include/TScoreHeader.h ../include/TIdentification.h
TXML2GuidoVisitor.o: ../include/TPartList.h ../include/TPartGroup.h
TXML2GuidoVisitor.o: ../include/TScorePart.h ../include/TMidiDevice.h
TXML2GuidoVisitor.o: ../include/TMidiInstrument.h
TXML2GuidoVisitor.o: ../include/TScoreInstrument.h ../include/TWork.h
TXML2GuidoVisitor.o: ../include/xml.h ../include/TScanVisitor.h
TXML2GuidoVisitor.o: ../include/TRoutedVisitor.h ../include/guido.h
TXML2GuidoVisitor.o: ../include/guidovisitor.h ../include/LibMusicXML.h
TXML2GuidoVisitor.o: ../include/TArpeggiate.h ../include/TAttributes.h
TXML2GuidoVisitor.o: ../include/TClef.h ../include/TKey.h
TXML2GuidoVisitor.o: ../include/TTimeSign.h ../include/TTranspose.h
TXML2GuidoVisitor.o: ../include/TStaffDetails.h ../include/TMeasureStyle.h
TXML2GuidoVisitor.o: ../include/TBackupForward.h ../include/TBarline.h
TXML2GuidoVisitor.o: ../include/TOrnaments.h ../include/TChord.h
TXML2GuidoVisitor.o: ../include/TNote.h ../include/TPitch.h
TXML2GuidoVisitor.o: ../include/TTimeModification.h ../include/TDirection.h
TXML2GuidoVisitor.o: ../include/TSound.h ../include/TFiguredBass.h
TXML2GuidoVisitor.o: ../include/THarmony.h ../include/TTechnical.h
TXML2GuidoVisitor.o: ../include/TMusicXMLFile.h ../include/TOtherDirections.h
TXML2GuidoVisitor.o: ../include/TScoreTimewise.h
