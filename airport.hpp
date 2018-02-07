#ifndef AIRPORT
#define AIRPORT

#include <ctime>
#include <list> 
#include "application.hpp"
#include "flight.hpp"

class airport{
	private:
		time_t current_time;
		flight **terminals;
		list<application> waiting_list;
		int number_of_terminals;
		int failed_apps; //number of failed applications
		int number_of_current_terminals;
	public:
		/*constructors*/
		airport(time_t currentTime,int numberOfTerminals);

		
		/*destructor*/
		~airport(void); 
		
		/*mutators*/
		void add_application(int Id,string firstName,string lastName,string Direction,int timeToAirport,
							int timeToDestination,char Seat);		
		void cancel_applications(int Id); //delete all applications from this id	
		int add_flight(string Destination,int timeOfDeparture,int timeOfFlight,int maxSeatsA,int maxSeatsB);
		void cancel_flight(int terminal);
		void increase_failed_apps(void);
		/*accessors*/
		time_t get_time(void) const; //return the current_time
		int failed_applications(void) const; //return the failed_apps member
		void show_people_waiting(void); //print the people in the waiting list
		void show_timetable(void); //show the current flights with order of the departure time
		int free_terminal(void); //return 1 if there is any free terminal else 0
		flight& get_flight(int i); //get a reference to a flight

		/*others*/
		void flow_time(time_t Duration,int& stop,fstream& flights_txt,string& Destination,int& timeOfDeparture,
					   int& timeOfFlight,int& maxSeatsA,int& maxSeatsB);
		
	private:
		void bubble_sort(flight**& terminals2,int& counter); 
		void print_flights(int& counter,flight**& terminals2);
		
};

#endif