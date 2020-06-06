CXX = g++
CXXFLAGS = -Wall

proj3: Train.o Car.o main.cpp
	$(CXX) $(CXXFLAGS) Train.o Car.o main.cpp -o proj3

Train.o: Train.cpp Train.h Car.o
	$(CXX) $(CXXFLAGS) -c Train.cpp

Car.o: Car.h Car.cpp
	$(CXX) $(CXXFLAGS) -c Car.cpp

clean:
	rm *~
	rm *.o

run:
	./proj3

run1:
	./proj3 proj3_t1.txt

val1:
	valgrind ./proj3 proj3_t1.txt

run2:
	./proj3 proj3_t2.txt

val2:
	valgrind ./proj3 proj3_t2.txt

run3:
	./proj3 proj3_t3.txt

val3:
	valgrind ./proj3 proj3_t3.txt
