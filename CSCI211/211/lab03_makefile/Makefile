#Makefile for foobar
#Brandon Smith
#CSCI 211
#Lab 3 Excercise 3

foobar: main.o foo.o bar.o
	g++ -Wall -pedantic -o foobar main.o foo.o bar.o

#Main relies on main, foo.h, and bar.h
main.o: main.cpp foo.h bar.h 
	g++ -Wall -pedantic -g -std=c++11 -c main.cpp
#Foo relies on foo.h
foo.o: foo.cpp foo.h
	g++ -Wall -pedantic -g -std=c++11 -c foo.cpp
#bar relies on bar.h
bar.o: bar.cpp bar.h
	g++ -Wall -pedantic -g -std=c++11 -c bar.cpp
#remove all .o files
clean:
	rm bar.o foo.o main.o
