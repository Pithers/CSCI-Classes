CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS = 

restaurant: restaurant.o table.o party.o
	$(CXX) $(LDFLAGS) table.o party.o restaurant.o -o restaurant

party.o: party.cc party.h
	$(CXX) $(CXXFLAGS) party.cc

table.o: table.cc table.h party.h
	$(CXX) $(CXXFLAGS) table.cc

restaurant.o: restaurant.cc restaurant.h doublylinkedlist.h table.h party.h
	$(CXX) $(CXXFLAGS) restaurant.cc

clean:
	rm *o restaurant
