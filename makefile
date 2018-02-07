CC=g++
CFLAGS=-Wall

prog: main.o application.o flight.o airport.o flight.hpp application.hpp airport.hpp iofunctions.o
	$(CC) -o prog main.o application.o flight.o airport.o iofunctions.o

main.o:application.hpp flight.hpp airport.hpp iofunctions.hpp main.cpp
	$(CC) $(CFLAGS) -c main.cpp

application.o:application.hpp application.cpp flight.hpp

	$(CC) $(CFLAGS) -c application.cpp 

flight.o:flight.cpp flight.hpp application.hpp

	$(CC) $(CFLAGS) -c flight.cpp 	

airport.o:airport.hpp airport.cpp
	$(CC) $(CFLAGS) -c airport.cpp

iofunctions.o:iofunctions.cpp
	$(CC) $(CFLAGS) -c iofunctions.cpp

clean:
	rm -f *.o	
