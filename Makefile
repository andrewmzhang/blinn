CC=g++
CPPFLAGS= -g -Wall 

MOCQT4 = moc-qt4

OFLAGS = $(INCL) -Wall -Wno-unreachable-code -Wno-return-type



all: main

main: color.o render.o system.o point.o square.o ray.o tracer.o sphere.o 

test: test.o render.o color.o system.o point.o ray.o
	$(CC) -o$@ $^ -lboost_unit_test_framework

#draw.o: draw.cpp draw.h
#	$(MOCQT4) draw.cpp | $(CC) $(OFLAGS) -c -x c++ - -include draw.cpp -o draw.o

#%: %.cpp draw.o draw.h
#	$(CC) $@.cpp draw.o  $(CFLAGS) -o $@

clean:
	rm -f *.exe main color *.o test render system *.bmp
