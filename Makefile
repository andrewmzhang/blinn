CC=g++
CFLAGS= -g -Wall

all: main 

main: color.o

clean:
	rm -f *.exe main color
