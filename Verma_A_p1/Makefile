all: program1
CC = clang++
CFLAGS =-std=c++11 -Wall -Wextra -g 
all: program1
program1: Driver.o program1.o
	$(CC) $(CFLAGS) program1.o Driver.o -o program1
Driver.o: Driver.cpp
	$(CC) $(CFLAGS) -c Driver.cpp -o Driver.o
program1.o: program1.cpp program1.h
	$(CC) $(CFLAGS) -c program1.cpp -o program1.o
clean:
	rm *.o program1 *~ 

