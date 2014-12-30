
APPL = xml
OUT  = xmlparse.cpp xmllex.cpp xmlparse.h
OBJ  = xmlparse.o xmllex.o 
CXXFLAGS = -I../core -DMAIN
LEX  := flex
YACC := bison

code : $(OUT)
	cp $(OUT) ../core

$(APPL) : $(OBJ)
	gcc $(DEBUG) $(OBJ) -lstdc++ -o $(APPL)

xmlparse.cpp : xml.y
	rm -f xmlparse.h
	$(YACC) -d -o xmlparse.cpp xml.y

xmlparse.h :
	-[ -f xmlparse.hpp ] && mv xmlparse.hpp xmlparse.h
	-[ -f xmlparse.cpp.h ] && mv xmlparse.cpp.h xmlparse.h

xmllex.cpp : xml.l xmlparse.h
	$(LEX) -oxmllex.cpp xml.l

clean:
	rm -f $(APPL) $(OUT) $(OBJ)
