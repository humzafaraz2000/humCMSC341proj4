CXX = g++
CXXFLAGS = -Wall

proj4: jqueue.o mytest.cpp
	$(CXX) $(CXXFLAGS) jqueue.o mytest.cpp -o proj4

jqueue.o: jqueue.h jqueue.cpp 
	$(CXX) $(CXXFLAGS) -c jqueue.cpp

run:
	./proj4

val:
	valgrind ./proj4