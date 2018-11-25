#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>

using namespace std;


class Room;
class Reservation {
private:
	string Client;
	int ReservationNumber;
	int Arrival;
	int DaysOfStay;
	int NumberOfPeople;
	Room* room;
	static int id;

public:
	Reservation();
	void setRoom(Room*);
	Room* getRoom();
	void setArrival(int);
	int getArrival();
	void setDaysOfStay(int);
	int getDaysOfStay();
	void setNumberOfPeople(int);
	int getNumberOfPeople();
	void setReservationNumber(int);
	int getReservationNumber();
	void setClient(string);
	string getClient();
};

#endif
