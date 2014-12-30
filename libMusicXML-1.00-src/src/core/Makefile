
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
CXXFLAGS = -Wall -I../include

TARGET = coreMusicXML.a

lib : $(TARGET)

$(TARGET) : $(OBJ)
	ar -ru $(TARGET) $(OBJ)
	ranlib $(TARGET)

clean :
	rm -f $(TARGET) $(OBJ)

dep:
	makedepend -- $(CXXFLAGS) -- $(SRC)

