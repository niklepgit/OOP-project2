#include "application.hpp"
#include "flight.hpp"

/*constructor*/
application::application(int Id,string firstName,string lastName,string Destination,int timeToAirport,
						 int timeToDestination,char Seat){
	
	id=Id;
	first_name=firstName;
	last_name=lastName;
	destination=Destination;	
	time_to_airport=timeToAirport;
	time_to_destination=timeToDestination;
	seat=Seat;
}

/*is_luxury_class*/
int application::is_luxury_class(void) const{
	return(seat=='A'); //return 1 if seat is A
}

/*get_id*/
int application::get_id(void) const{
	return(id);
}

/*get_name*/
string application::get_name(void) const{
	return(first_name+' '+last_name);
}

/*arrived_by*/
int application::arrived_by(void) const{
	return(time_to_destination); //return the time to destination member
}

/*matches*/
int application::matches(flight& Flight){ 
	if( time_to_airport<=Flight.departs_at() && //if the flight departs before the passenger arrives at the airport
	    time_to_destination>=Flight.arrives_at() && //and if the flight arrives to destination before the time that the passenger wants
	    destination==Flight.get_destination() //and if the destination matches
      )
      return 1;
    else
	  return 0;  
}

