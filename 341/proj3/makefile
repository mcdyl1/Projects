CXX = g++
CXXFLAGS = -Wall

p4test1.out: MedianHeap.h p4test1.cpp
	$(CXX) $(CXXFLAGS) MedianHeap.h p4test1.cpp -o p4test1.out 

p4test2.out: MedianHeap.h p4test2.cpp
	$(CXX) $(CXXFLAGS) MedianHeap.h p4test2.cpp -o p4test2.out

p4test3.out: City.o MedianHeap.h p4test3.cpp
	$(CXX) $(CXXFLAGS) City.o MedianHeap.h p4test3.cpp -o p4test3.out

p4test4.out: City.o MedianHeap.h p4test4.cpp
	$(CXX) $(CXXFLAGS) City.o MedianHeap.h p4test4.cpp -o p4test4.out

p4test5.out: City.o MedianHeap.h p4test5.cpp
	$(CXX) $(CXXFLAGS) City.o MedianHeap.h p4test5.cpp -o p4test5.out

p4test6.out: City.o MedianHeap.h p4test6.cpp
	$(CXX) $(CXXFLAGS) City.o MedianHeap.h p4test6.cpp -o p4test6.out

p4test7.out: City.o MedianHeap.h p4test7.cpp
	$(CXX) $(CXXFLAGS) City.o MedianHeap.h p4test7.cpp -o p4test7.out

City.o: City.cpp City.h
	$(CXX) $(CXXFLAGS) -c City.cpp

clean:
	rm *.o*
	rm *~
