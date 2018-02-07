#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void read_application(int& stop,fstream& applications_txt,int& Id,string& firstName,string& lastName,
					  string& Destination,int& timeToAirport,int& timeToDestination,char& Seat){

	applications_txt>>Id;
	applications_txt>>firstName;
	applications_txt>>lastName;
	applications_txt>>Destination;
	applications_txt>>timeToAirport;
	applications_txt>>timeToDestination;
	applications_txt>>Seat;
	if(applications_txt.eof())
		stop=1;

}

void read_flight(int& stop,fstream& flights_txt,string& Destination,int& timeOfDeparture,int& timeOfFlight,
				 int& maxSeatsA,int& maxSeatsB){

	flights_txt>>Destination;
	flights_txt>>timeOfDeparture;
	flights_txt>>timeOfFlight;
	flights_txt>>maxSeatsA;
	flights_txt>>maxSeatsB;
	if(flights_txt.eof())
		stop=1;

}
