output: rsa.o definition.o 
	g++ -std=c++17 rsa.o definition.o -o output

rsa.o: rsa.cpp
	g++ -c -std=c++17 rsa.cpp 

definition.o: definition.cpp rsa.hpp
	g++ -std=c++17 -c definition.cpp


clean:
	rm *.o output