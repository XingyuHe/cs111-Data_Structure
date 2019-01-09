fractest: fraction.o fractest.o
	g++ -o fractest fraction.o fractest.o 
fraction.o: fraction.cc fraction.h
	g++ -c fraction.cc 
fractest.o: fractest.cc fraction.h
	g++ -c fractest.cc 