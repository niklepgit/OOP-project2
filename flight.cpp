#include "flight.hpp"
#include "application.hpp"

#include <iostream>
using namespace std;


/*constructor*/
flight::flight(string Destination,int timeOfDeparture,int timeOfFlight,int maxSeatsA,int maxSeatsB){
	destination=Destination;
	time_of_departure=timeOfDeparture;
	time_of_flight=timeOfFlight;
	max_seats_A=maxSeatsA;
	max_seats_B=maxSeatsB;
	available_seats_A=maxSeatsA;
	available_seats_B=maxSeatsB;
}

/*departs_at*/
int flight::departs_at(void) const{
	return(time_of_departure); //return the time of departure
}

/*arrives_at*/
int flight::arrives_at(void) const{
	return(time_of_departure+time_of_flight); //return the time airoplane arrives
}		

/*get_destination*/
string flight::get_destination(void) const{
	return(destination); //return destination
}

/*get_available*/
int flight::get_available(void) const{
	return(available_seats_A+available_seats_B); //return the available seats in both classes A,B
}

/*get_available_seats_A*/
int flight::get_available_seats_A(void) const{
	return(available_seats_A); //return the available seats in class A
}

/*get_available_seats_B*/
int flight::get_available_seats_B(void) const{
	return(available_seats_B); //return the available seats in class B
}

/*add_passenger*/
int flight::add_passenger(application& app){
	if(app.is_luxury_class()){ //if class is A
		if(available_seats_A){ //if there is any available seat 
			available_seats_A--; //decrease available_seats_A member
			list_of_passengers.push_back(app); //add the application to the list_of_passengers
			//cout<<"passenger "<<app.get_name()<<" got on"<<endl;
			return 1;
		}
	else					 //if class is B 
		if(available_seats_B){ //if there is any available seat  
			available_seats_B--; //decrease available_seats_B member
			list_of_passengers.push_back(app); //add the application to the list_of_passengers 
			return 1;
		}
	}
	return 0;
}

/*cancel_reservation*/
int flight::cancel_reservations(int id){
	list<application>::iterator it;
	int check=0;
	for(it=list_of_passengers.begin();it!=list_of_passengers.end();it++) //for every passenger
		 if(id==(*it).get_id()){ //get the id of the application and if matches
		 	it=list_of_passengers.erase(it); //erase it
		 	cout<<"A reservation with id "<<id<<" was canceled."<<endl;
		 	check=1;
         	it--;
         }
    if(check) //if there was any application now is deleted and return 1 else 0
    	return 1;
    else
    	return 0;
}
		 	
/*get_bookings*/
list<application>& flight::get_bookings(void){
	return(list_of_passengers);
}

/*get_max_seats_A*/
int flight::get_max_seats_A(void) const{
	return(max_seats_A);
}		 

/*get_max_seats_B*/
int flight::get_max_seats_B(void) const{
	return(max_seats_B);
}		 		
