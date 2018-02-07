#include <iostream>
#include <string>
#include <fstream>

#include "flight.hpp"
#include "application.hpp"
#include "airport.hpp"
#include "iofunctions.hpp"

using namespace std;

int main(int argc,char** argv){
	
	string firstName,lastName,Destination;
	int timeToDestination,timeToAirport,Id,timeOfDeparture,timeOfFlight,maxSeatsA,maxSeatsB;
	char Seat;
	int stop=0;
	int duration=atoi(argv[1]); //take the duration from the command line

	fstream applications_txt; 
	fstream flights_txt;
	applications_txt.open("applications.txt",fstream::in); //open the applications.txt file
	flights_txt.open("flights.txt",fstream::in); //open the flights.txt file
	time_t t=0;
	airport Airport(t,4); //create an airport
	
	while(!applications_txt.eof()){

		read_application(stop,applications_txt,Id,firstName,lastName,Destination,timeToAirport,
				         timeToDestination,Seat);
		if(stop)
			break;
	    cout<<firstName<<" "<<lastName<<" "<<Destination<<" "<<timeToAirport<<" "<<timeToDestination<<" "<<Seat<<endl;
		Airport.add_application(Id,firstName,lastName,Destination,timeToAirport,timeToDestination,Seat);
	}
	cout<<"\n----------All the applications have been read----------"<<endl<<endl;
	stop=0;

	Airport.flow_time(duration,stop,flights_txt,Destination,timeOfDeparture,
	   			  timeOfFlight,maxSeatsA,maxSeatsB);

	Airport.show_people_waiting();
	cout<<"The number of failed applications are "<<Airport.failed_applications()<<endl;
	
	applications_txt.close();
	flights_txt.close();

	return 0;
}
