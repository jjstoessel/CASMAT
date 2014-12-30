
VERSION =1.00
SRC 	= libMusicXML-$(VERSION)-src
PACKDIR  = package
DEST     = $(PACKDIR)
PDFDOC   = doc/libmusicxml-$(VERSION).pdf

MACOSLIB = libmusicxml-$(VERSION)-macosx
MACOSDIR = $(PACKDIR)/$(MACOSLIB)
LINUXLIB = libmusicxml-$(VERSION)-linux-x86
LINUXDIR = $(PACKDIR)/$(LINUXLIB)
WINLIB   = libmusicxml-$(VERSION)-win32
WINDIR   = $(PACKDIR)/$(WINLIB)


files   = CHANGELOG.txt README.txt license.txt
modules =  	libmusicxml/doc 	\
			libmusicxml/dtds 	\
			libmusicxml/src

.PHONY: linux windows macos

nothing:
	@ echo this is a packaging makefile, available targets are:
	@ echo "  'srcpack': builds an archive with doc, source code and dtds"
	@ echo "  'macos'  : builds an archive with doc, dtds and binary framework"
	@ echo "  'linux'  : builds an archive with doc, dtds, includes, static and dynamic lib"
	@ echo "  'windows': builds an archive with doc, dtds, includes, dll and lib"
	@ echo "  'doc'    : builds an archive with doc, dtds, includes, dll and lib"

doc:
	cd ../doc && doxygen
	make -C ../doc/latex 
	cp ../doc/latex/refman.pdf ../$(PDFDOC)

srcpack:
	@ echo in case of trouble, make sure your CVSROOT is correctly set
	cvs export -D tomorrow $(modules)
	mv libmusicxml $(SRC)
	tar czf $(SRC).tgz $(SRC)

macos:
	make common DEST=$(MACOSDIR)
	cp -R macosx/build/libMusicXML.framework $(MACOSDIR)
	cd $(PACKDIR) && tar czf $(MACOSLIB).tgz $(MACOSLIB)

linux:
	make common DEST=$(LINUXDIR)
	make incl DEST=$(LINUXDIR)
	cp  libMusicXML.a $(LINUXDIR)
	cd $(PACKDIR) && tar czf $(LINUXLIB).tgz $(LINUXLIB)

windows:
	make common DEST=$(WINDIR)
	make include DEST=$(WINDIR)

common:
	rm -rf $(DEST)
	mkdir -p $(DEST)
	cp -R ../doc/html $(DEST)/doc
	cp    ../$(PDFDOC) $(DEST)
	cp    $(files) $(DEST)
	cd $(DEST) && cvs export -D tomorrow -d dtds    libmusicxml/dtds      
	cd $(DEST) && cvs export -D tomorrow -d samples libmusicxml/src/samples

incl:
	[ -d $(DEST)/include ] || mkdir $(DEST)/include
	cp include/*.h $(DEST)/include
	cd $(DEST)/include && chmod -x *.h

clean :
	rm -rf $(PACKDIR)

