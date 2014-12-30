
SRC = $(wildcard *.cpp)
CXXFLAGS =  -I../include -O3

LIB = ../libMusicXML.a

PROGS = rmusic xmlread transpose musicXML2Guido getcontext

all: $(PROGS)

rmusic : $(CORE) RandomMusic.o
	$(CC) RandomMusic.o $(LIB) -lstdc++ -lm -o rmusic

xmlread : $(CORE) ReadWrite.o
	$(CC) ReadWrite.o $(LIB) -lstdc++ -o xmlread

transpose : $(CORE) RawTranspose.o
	$(CC) RawTranspose.o $(LIB) -lstdc++ -o transpose

musicXML2Guido : $(LIB) MusicXML2Guido.o
	$(CC) MusicXML2Guido.o $(LIB) -lstdc++ -o musicXML2Guido

getcontext : $(LIB) ContextVisitors.o
	$(CC) ContextVisitors.o $(LIB) -lstdc++ -o getcontext

clean :
	rm -f $(PROGS) *.o

dep:
	makedepend -- $(CXXFLAGS) -- $(SRC)
