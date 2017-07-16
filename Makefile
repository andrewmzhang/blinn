CC=g++
CFLAGS= -g -Wall -lQtCore -lQtGui

MOCQT4 = moc-qt4

INCL = -I/usr/include/qt4 -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui
OFLAGS = $(INCL) -Wall -Wno-unreachable-code -Wno-return-type



all: main 

main: color.o render.o system.o

test: test.o

#draw.o: draw.cpp draw.h
#	$(MOCQT4) draw.cpp | $(CC) $(OFLAGS) -c -x c++ - -include draw.cpp -o draw.o

#%: %.cpp draw.o draw.h
#	$(CC) $@.cpp draw.o  $(CFLAGS) -o $@

clean:
	rm -f *.exe main color *.o
