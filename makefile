CC = g++
CPPFLAGS = -Wall -std=c++11

all: eldrow eldrow-parser

eldrow:
	$(CC) -o eldrow eldrow.cpp -lreadline

eldrow-parser:
	$(CC) -o eldrow-parser eldrow-parser.cpp

.PHONY: clean
clean:
	$(info -- cleaning the directory --)
	rm -f *.o
	rm -f *.gch
	rm -f eldrow
	rm -f eldrow-parser
