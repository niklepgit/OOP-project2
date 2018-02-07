void read_application(int& stop,fstream& applications_txt,int& Id,string& firstName,string& lastName,
					  string& Destination,int& timeToDestination,int& timeToAirport,char& Seat);

void read_flight(int& stop,fstream& flights_txt,string& Destination,int& timeOfDeparture,int& timeOfFlight,
				 int& maxSeatsA,int& maxSeatsB);
 