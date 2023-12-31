CXX = g++
CXXFLAGS = -Wall

OBJECTS = avltree.o wordrange.o

wordrange: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o wordrange avltree.o wordrange.o

avltree.o: avltree.cpp avltree.h
	$(CXX) -g $(CXXFLAGS) -c avltree.cpp

wordrange.o: avltree.cpp avltree.h wordrange.cpp
	$(CXX) -g $(CXXFLAGS) -c wordrange.cpp

clean:
	rm -f *.o
	rm wordrange