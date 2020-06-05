CXX = g++
CXXFLAGS = -Wall

t01.out: InnerCB.o p1test01.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o p1test01.cpp -o t01.out

t02.out: InnerCB.o p1test02.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o p1test02.cpp -o t02.out

t03.out: InnerCB.o p1test03.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o p1test03.cpp -o t03.out

t04.out: InnerCB.o p1test04.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o p1test04.cpp -o t04.out

t05.out: InnerCB.o p1test05.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o p1test05.cpp -o t05.out

t06.out: InnerCB.o CBofCB.o p1test06.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o CBofCB.o p1test06.cpp -o t06.out

t07.out: InnerCB.o CBofCB.o p1test07.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o CBofCB.o p1test07.cpp -o t07.out

t08.out: InnerCB.o CBofCB.o p1test08.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o CBofCB.o p1test08.cpp -o t08.out

t09.out: InnerCB.o CBofCB.o p1test09.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o CBofCB.o p1test09.cpp -o t09.out

t10.out: InnerCB.o CBofCB.o p1test10.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o CBofCB.o p1test10.cpp -o t10.out

t11.out: InnerCB.o CBofCB.o p1test11.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o CBofCB.o p1test11.cpp -o t11.out

t12.out: InnerCB.o CBofCB.o p1test12.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o CBofCB.o p1test12.cpp -o t12.out

t13.out: InnerCB.o CBofCB.o p1test13.cpp
	$(CXX) $(CXXFLAGS) InnerCB.o CBofCB.o p1test13.cpp -o t13.out

CBofCB.o: InnerCB.o CBofCB.cpp CBofCB.h
	$(CXX) $(CXXFLAGS) -c CBofCB.cpp

InnerCB.o: InnerCB.cpp InnerCB.h
	$(CXX) $(CXXFLAGS) -c InnerCB.cpp

clean:
	rm *.o*
	rm *~

