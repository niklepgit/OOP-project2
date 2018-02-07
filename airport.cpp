#include "airport.hpp"
#include "application.hpp"
#include "iofunctions.hpp"

#include <iostream>
using namespace std;

/*get_time*/
time_t airport::get_time(void) const{
	return(current_time);
}

/*constructor*/
airport::airport(time_t currentTime,int numberOfTerminals){
	int i;

	current_time=currentTime;
	number_of_terminals=numberOfTerminals;
	terminals= new flight*[numberOfTerminals];
	failed_apps=0;
	number_of_current_terminals=0;

	for(i=0;i<numberOfTerminals;i++)
		terminals[i]=nullptr;
}

/*destructor*/
airport::~airport(void){
	int i;
	for(i=0;i<number_of_terminals;i++) //for every terminal
		if(terminals[i]!=nullptr){ //if the terminal is not null
			delete terminals[i]; //delete it
			terminals[i]=nullptr; //pointer to terminal points to null
		}
	delete[] terminals;	//delete the array of pointers to terminals-applications
}

/*add_application*/
void airport::add_application(int Id,string firstName,string lastName,string Direction,int timeToAirport,
							  int timeToDestination,char Seat){
	application app(Id,firstName,lastName,Direction,timeToAirport,timeToDestination,Seat);
	waiting_list.push_back(app);
}

/*increase_failed_apps*/
void airport::increase_failed_apps(void){
	failed_apps++;
}

/*cancel_applications*/
void airport::cancel_applications(int Id){
	int i;
	for(i=0;i<number_of_terminals;i++){ //for every flight
		if(terminals[i]==nullptr)
			continue;
		terminals[i]->cancel_reservations(Id); //cancel all the reservations with the id
		increase_failed_apps();
	}	
	
	list<application>::iterator it;
	for(it=waiting_list.begin();it!=waiting_list.end();it++) //for all the applications in the waiting list
		if(it->get_id()==Id){ //check if there are applications with this id
			it=waiting_list.erase(it); //if yes erase it
			it--; //we have to do it because the return from erase is it++ and we also do it++ in the end of for loop
			increase_failed_apps();
			cout<<"An application from the waiting list with id "<<Id<<" was canceled."<<endl;
		}

 	cout<<"All the applications with id "<<Id<<" were canceled."<<endl<<endl;
}

/*add_flight*/
int airport::add_flight(string Destination,int timeOfDeparture,int timeOfFlight,int maxSeatsA,int maxSeatsB){
	int i;
	for(i=0;i<number_of_terminals;i++)
		if(terminals[i]==nullptr){
			terminals[i]=new flight(Destination,timeOfDeparture,timeOfFlight,maxSeatsA,maxSeatsB);
			number_of_current_terminals++;
			cout<<"A flight with destination to <"<<Destination<<"> time of departure <"<<timeOfDeparture<<
			"> and time of flight <"<<timeOfFlight<<"> is now available."<<endl<<endl;
			return i;		
		}
}
/*cancel_flight*/
void airport::cancel_flight(int terminal){
	list<application> &termporary_list_of_passengers=terminals[terminal]->get_bookings(); //get the list_of_passengers
	list<application>::iterator it=waiting_list.begin(); //it points to the first of the waiting list
	failed_apps+=termporary_list_of_passengers.size(); //increase the number of failed applications
	waiting_list.splice(it,termporary_list_of_passengers); //add the failed_applications from flight to the beginning of the waiting list
	delete terminals[terminal]; //delete the flight from the array of pointers
	number_of_current_terminals--;
	terminals[terminal]=nullptr; //make the pointer points to nullptr
}

/*failed_applicatons*/
int airport::failed_applications(void) const{
	return(failed_apps);
}

/*show_people_waiting*/
void airport::show_people_waiting(void){  //////thema me const why?
	list<application>::iterator it;
	string name;
	cout<<"The people in the waiting list are:"<<endl;
	for(it=waiting_list.begin();it!=waiting_list.end();it++){
		name=it->get_name();
		cout<<name<<endl;
	}
}

/*show_timetable*/
void airport::show_timetable(void){
	flight **terminals2;
	int counter=0;
	bubble_sort(terminals2,counter); //sort the array of flights
	print_flights(counter,terminals2); //print the flights with order
	delete[] terminals2;
	terminals2=nullptr;
}

/*bubble_sort*/	
void airport::bubble_sort(flight**& terminals2,int& counter){
	int i,j=0,found;
	flight* temp;
	
	for(i=0;i<number_of_terminals;i++) //count the terminals that have a flight
		if(terminals[i]!=nullptr)
			counter++;
		terminals2=new flight*[counter]; //make an array of pointers to flight 
										//with size the number of the terminlas that have
										//a flight
	for(i=0;i<number_of_terminals;i++){ //copy the pointers from the terminals array to the terminals2 array
		if(terminals[i]!=nullptr) 	
			terminals2[j++]=terminals[i];
		else
			continue;
	}
								//bubble sort the terminals2 array
	for(i=0;i<counter;i++){
		found=0;
		for(j=counter-1;j>i;j--)
			if(terminals2[j]->departs_at()<terminals2[j]->departs_at()){
				temp=terminals2[j];
				terminals2[j]=terminals2[j-1];
				terminals2[j-1]=temp;
				found=1;
			}
			if(found==0)
				break;
	}
}

/*print_flights*/
void airport::print_flights(int& counter,flight**& terminals2){
	int i,flag=1;
	cout<<"The available flights are:"<<endl;

	for(i=0;i<counter;i++){
		cout<<"Flight with number "<<i+1<<":"
			<<"\t"<<"Destination "<<terminals2[i]->get_destination()
			<<"  \t"<<"Time of departure "<<terminals2[i]->departs_at()
			<<"\t"<<"Time of arrival "<<terminals2[i]->arrives_at()<<endl;
		flag=0;
	}
	if(flag) //if there are no passengers on the flight
		cout<<"There are no available flights."<<endl;
	cout<<endl;
}

/*free_terminal*/
int airport::free_terminal(void){
	if(number_of_current_terminals!=number_of_terminals) //if there is any empty terminal
		return 1;									
	else												
		return 0;										
}

/*get_flight*/
flight& airport::get_flight(int i){
	return(*(terminals[i])); //returns a reference to a flight 
}

/*flow_time*/
void airport::flow_time(time_t Duration,int& stop,fstream& flights_txt,string& Destination,int& timeOfDeparture,
						int& timeOfFlight,int& maxSeatsA,int& maxSeatsB){
	time_t Time,i,j;
	list<application>::iterator it;
	stop=0;
	for(i=0;i<number_of_terminals;i++){ //read the first flights to full the array of flights if possible
		read_flight(stop,flights_txt,Destination,timeOfDeparture,timeOfFlight,
				 	maxSeatsA,maxSeatsB);
		if(stop) //the finish is reached 
			break; //stop the reading
		add_flight(Destination,timeOfDeparture,timeOfFlight,maxSeatsA,maxSeatsB); //after every read add the flight
	}
			
	for(Time=current_time;Time<=current_time+Duration+1;Time++){ //for the duration of the simulation
		cout<<"Time <"<<Time<<">"<<endl;
		show_timetable();
			/*for the applications*/
		for(it=waiting_list.begin();it!=waiting_list.end();it++){ //for every application in the waiting list	
			if(Time >= it->arrived_by()){ //if the Time now is greater or equal to the time he passenger 
										  //wanted to arrive at the destination 
				cout<<"The appication with name "<<it->get_name()<<" was deleted."<<endl;
				increase_failed_apps();
				it=waiting_list.erase(it); //if yes erase it
			}
			else
				for(j=0;j<number_of_terminals;j++){ //for every terminal
					if(terminals[j]==nullptr) //if the terminal is empty
						continue; 			  //continue	
					flight& Flight=get_flight(j); //get the flight
					if(it->matches(Flight)){ //if the flight matches with the application
						Flight.add_passenger(*it); //add the passenger
						it=waiting_list.erase(it); //erase the application from the waiting list
						it--; //the erase fuction returns it++ but i also do it++ at the end of for loop
							  //so i have to do it-- now.
					}
						
				}	
		}

		if(Time==0){ //make use of the funtion cancel_applications
		cancel_applications(46541);
		}	
		
			/*for the flights*/
		for(j=0;j<number_of_terminals;j++){ //for every terminal
			if(terminals[j]==nullptr) //if the terminal is empty 
						continue;     //continue
		int crew=0;
			if(Time==terminals[j]->departs_at()){ //if it is the time for the flight to depart
				list<application>& passengers=terminals[j]->get_bookings(); //get all the bookings of the flight
				list<application>::iterator iter;
				cout<<"The flight with destination "<<terminals[j]->get_destination()
					<<" is going to take off."<<endl
					<<"The passengers in this flight are:"<<endl;
				for(iter=passengers.begin();iter!=passengers.end();iter++){
					crew=1;
					cout<<iter->get_name()<<endl;
				}
				if(crew)
					cout<<"Have a nice flight all of you!!!"<<endl<<endl;
				else
					cout<<"Only the crew is in this flight."<<endl<<endl;
				delete terminals[j]; //delete the flight
				terminals[j]=nullptr; //terminal is empty
				number_of_current_terminals--; //decrease the number of current terminals by one
			}
		}
					//make use of function cancel_flight
		if(Time==4) //if Time equals to 4 make a random cancelation of a flight
		for(j=0;j<number_of_terminals;j++) //for every terminal
			if(terminals[j]!=nullptr){ //if the terminal isn't empty
				cout<<"The flight with destination "<<terminals[j]->get_destination()
				<<" and time of departure "<<terminals[j]->departs_at()<<" is canceled "<<endl;
				cancel_flight(j); //cancel the flight
				break; //get out of the for loop
			}
		
		stop=0;
		if(free_terminal()) //if there is any free terminal
			for(j=0;j<number_of_terminals-number_of_current_terminals;j++){ //read as many flights as the free terminals
				read_flight(stop,flights_txt,Destination,timeOfDeparture,timeOfFlight,
				 	maxSeatsA,maxSeatsB);
				if(stop) //if you reach the end of the file
					break; //stop reading
				add_flight(Destination,timeOfDeparture,timeOfFlight,maxSeatsA,maxSeatsB); //add the flight
			}	
		for(j=0;j<number_of_terminals;j++){
			if(terminals[j]==nullptr) //if the terminal is empty
				continue; 			  //continue
			if(Time>terminals[j]->departs_at()){ //if the Time is greater than the departure time of the flight
				cout<<"Time has passed so the flight must be canceled."<<endl;
				cout<<"The flight with destination to "<<terminals[j]->get_destination()<<" is canceled."<<endl<<endl; 
				cancel_flight(j); //cancel the flight
			}
				 
		}
	}
	current_time+=Duration+1; //after all the time has flown add to  current time the duration + 1 for the extra loop 
}
