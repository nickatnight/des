#
# Makefile for a des program.  This program uses both the des module
# and a test module. Typing 'make' or 'make des' will create the
# executable file.
#


CC = g++

default: des

des: main.o des.o test.o
	$(CC) -o des main.o des.o test.o

main.o: main.cpp des.h test.h
	$(CC) -c main.cpp

des.o: des.cpp des.h
	$(CC) -c des.cpp

test.o: test.cpp test.h
	$(CC) -c test.cpp

clean:
	rm -f *.o des


