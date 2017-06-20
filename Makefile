CC=g++
CFLAGS= -g -Wall -std=c++11

all: main 

main: color.o render.o

clean:
	rm -f *.exe main color
