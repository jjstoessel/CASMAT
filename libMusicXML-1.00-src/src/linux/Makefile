

TARGET = ../libMusicXML.a

.PHONY: $(TARGET)

all : $(TARGET) samples

$(TARGET) :
	make -C ../core
	make -C ../visitors
	ar -ru $(TARGET) ../core/*.o ../visitors/*.o
	ranlib $(TARGET)

samples :
	make -C ../samples

clean :
	make -C ../core clean
	make -C ../visitors clean
	make -C ../samples clean
	rm $(TARGET)

dep:
	make -C ../core dep
	make -C ../visitors dep
	make -C ../samples dep

