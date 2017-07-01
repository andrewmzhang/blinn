CC=g++
CFLAGS= -g -Wall -std=c++11

all: main 

main: color.o

clean:
	rm -f *.exe main color *.o
