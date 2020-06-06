CXX = g++
CXXFLAGS = -Wall

driver: Carrier.o Ups.o FedEx.o Mail.o Letter.o Package.o MailHouse.o driver.cpp
	$(CXX) $(CXXFLAGS) Carrier.o Ups.o FedEx.o Mail.o Letter.o Package.o MailHouse.o driver.cpp -o driver

Carrier.o: Carrier.cpp Mail.o
	$(CXX) $(CXXFLAGS) -c Carrier.cpp

Ups.o: Carrier.o Ups.cpp Ups.h
	$(CXX) $(CXXFLAGS) -c Ups.cpp

FedEx.o: Carrier.o FedEx.cpp FedEx.h
	$(CXX) $(CXXFLAGS) -c FedEx.cpp

Mail.o: Mail.cpp Mail.h
	$(CXX) $(CXXFLAGS) -c Mail.cpp

Letter.o: Mail.o Letter.h Letter.cpp
	$(CXX) $(CXXFLAGS) -c Letter.cpp

Package.o: Mail.o Package.h Package.cpp
	$(CXX) $(CXXFLAGS) -c Package.cpp

MailHouse.o: Carrier.o Letter.o Package.o FedEx.o Ups.o MailHouse.cpp MailHouse.h
	$(CXX) $(CXXFLAGS) -c MailHouse.cpp

clean:
	rm *.o*
	rm *~
run:
	./driver

run1:
	./driver proj4_t1.txt

val1:
	valgrind ./driver proj4_t1.txt

run2:
	./driver proj4_t2.txt

val2:
	valgrind ./driver proj4_t2.txt

run3:
	./driver proj4_t3.txt

val3:
	valgrind ./driver proj4_t3.txt

run4:
	./driver proj4_t4.txt

val4:
	valgrind ./driver proj4_t4.txt
