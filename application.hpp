#ifndef APPLICATION
#define APPLICATION

#include <string> 
using namespace std;

class flight;

class application{
	private:
		int id; //id of the passenger
		string first_name; //first name of the passenger
		string last_name; //last name of the passenger
		string destination; //destination of the passenger
		int time_to_airport; //time he wants to be at the airport
		int time_to_destination; //time he wants to be at the destination
		char seat; //A for luxury class and B for economic class
		
	public:
		/*constructors*/
		application(int Id,string firstName,string lastName,string Direction,int timeToAirport,
					int timeToDestination,char Seat); //constructor
		
		/*accessors*/
		int is_luxury_class(void) const; //return 1 if class is luxury else 0
		int get_id(void) const; //return the id of the passenger
		string get_name(void) const; //return the name
		int arrived_by(void) const; //return the time to destination member
		
	    /*others*/
	    int matches(flight& Flight); //return 1 if the flight matches else 0
};


#endif
