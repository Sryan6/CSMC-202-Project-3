CXX = g++
CXXFLAGS = -Wall

proj3: BusCompany.o Route.o driver.cpp
	$(CXX) $(CXXFLAGS) Route.o BusCompany.o driver.cpp -o proj3

BusCompany.o: Route.o BusCompany.cpp BusCompany.h
	$(CXX) $(CXXFLAGS) -c BusCompany.cpp

Route.o: Route.cpp Route.h
	$(CXX) $(CXXFLAGS) -c Route.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj3

test2:
	./proj3 proj3_t1.txt

test3:
	./proj3 proj3_t2.txt

run1:
	./proj3 proj3_test1.txt

run2:
	./proj3 proj3_test2.txt

run3:
	./proj3 proj3_test3.txt

run4:
	./proj3 proj3_test4.txt

val1:
	valgrind ./proj3 proj3_test1.txt

val2:
	valgrind ./proj3 proj3_test2.txt

val3:
	valgrind ./proj3 proj3_test3.txt

val4:
	valgrind ./proj3 proj3_test4.txt
