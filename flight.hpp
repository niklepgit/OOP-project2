#ifndef FLIGHT
#define FLIGHT

#include <list>
#include <string>
using namespace std; 

class application;

class flight{
	public:
		string destination; //the destination of the flight
		int time_of_departure; //time of departure
		int time_of_flight; //the duration of the flight
		int max_seats_A; //max seats in luxury class
		int max_seats_B; //max seats in economy class
		int available_seats_A; //the available seats A
		int available_seats_B; //the available seats B
		list<application> list_of_passengers; //list of the passengers-applications
		
	public:
		/*constructors*/
		flight(string Destination,int timeOfDeparture,int timeOfFlight,int maxSeatsA,int maxSeatsB);
	    /*destructors*/
		
		/*accessors*/
		int departs_at(void) const; //return the time of departure
		int arrives_at(void) const; //return when the airoplane arrives
		string get_destination(void) const; //return the destination of the flight
		int get_available(void) const; //return the number of the available seats
		int get_max_seats_A(void) const; //return the max number of seats A      DELETE
		int get_max_seats_B(void) const; //return the max number of seats B 	 DELETE
		int get_available_seats_A(void) const; //return the available seats in class A
		int get_available_seats_B(void) const; //return the available seats in class B
		list<application>& get_bookings(void); //return a reference to the list_of_passengers
		
		
		/*mutators*/
		int add_passenger(application& app); //return 1 if passenger get on else 0
		int cancel_reservations(int id); //return 1 if the reservations were deleted else 0
		
		/*others*/
		
};

#endif

