CXX =	g++
CXXFLAGS = -Wall -std=c++11 

OBJECTS = bard.o linkedlist.o

bard: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o bard bard.o linkedlist.o

bard.o: bard.cpp bard.h
	$(CXX) -g $(CXXFLAGS) -c bard.cpp

linkedlist.o: linkedlist.cpp bard.h
	$(CXX) -g $(CXXFLAGS) -c linkedlist.cpp
	
clean: 
	rm -f *.o
	rm bard