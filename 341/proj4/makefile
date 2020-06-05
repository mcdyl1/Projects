CXX = g++
CXXFLAGS = -Wall

test1.out: HashTable.o primes.o test1.cpp
	$(CXX) $(CXXFLAGS) HashTable.o primes.o test1.cpp -o test1.out

test2.out: HashTable.o primes.o test2.cpp
	$(CXX) $(CXXFLAGS) HashTable.o primes.o test2.cpp -o test2.out

Driver.out: HashTable.o primes.o Driver.cpp
	$(CXX) $(CXXFLAGS) HashTable.o primes.o Driver.cpp -o Driver.out

test4.out: HashTable.o primes.o test4.cpp
	$(CXX) -g HashTable.o primes.o test4.cpp -o test4.out

test5.out: HashTable.o primes.o test5.cpp
	$(CXX) $(CXXFLAGS) HashTable.o primes.o test5.cpp -o test5.out

xHashTable.o: HashTable.cpp HashTable.h
	$(CXX) $(CXXFLAGS) -c HashTable.cpp

primes.o: primes.h primes.cpp
	$(CXX) $(CXXFLAGS) -c primes.cpp

clean:
	rm *.o*
	rm *~
