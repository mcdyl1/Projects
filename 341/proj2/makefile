CXX = g++
CXXFLAGS = -Wall

Driver: Sally.o
	$(CXX) $(CXXFLAGS) Sally.o Driver.cpp -o Driver

driver1: Sally.o
	$(CXX) $(CXXFLAGS) Sally.o driver1.cpp -o driver1

Sally: Sally.h Sally.cpp
	$(CXX) $(CXXFLAGS) -c Sally.cpp

clean:
	rm *.o*
	rm *~
run1:
	./driver1
