CXX = g++
CXXFLAGS = -Wall

proj5: Tqueue.cpp Ship.o Imperial.o Rebel.o StarWars.o driver.cpp
	$(CXX) $(CXXFLAGS) Tqueue.cpp Ship.o Imperial.o StarWars.o Rebel.o driver.cpp -o proj5

StarWars.o: StarWars.h StarWars.cpp Ship.o Imperial.o Rebel.o
	$(CXX) $(CXXFLAGS) -c StarWars.cpp

Ship.o: Ship.h Ship.cpp
	$(CXX) $(CXXFLAGS) -c Ship.cpp

Imperial.o: Imperial.h Imperial.cpp Ship.o
	$(CXX) $(CXXFLAGS) -c Imperial.cpp

Rebel.o: Rebel.h Rebel.cpp Ship.o
	$(CXX) $(CXXFLAGS) -c Rebel.cpp

run:
	./proj5 proj5_imperial.txt proj5_rebel.txt

val1:
	valgrind ./proj5 proj5_imperial.txt proj5_rebel.txt

clean:
	rm *~
	rm *.o
