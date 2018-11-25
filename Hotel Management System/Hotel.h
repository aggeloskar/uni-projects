#ifndef HOTEL_H
#define HOTEL_H
#include<vector>
using namespace std;
class Room;
class RoomA;
class RoomC;
class Reservation;
class Hotel
{
private:
	vector<Room*> rooms;
	vector<Reservation*> reservations;
public:
	void addRoom(Room*);
	vector<Room*> getRoom();
	void setReservations(Reservation*);
	vector<Reservation*> getReservations();
	Room* retrieveRoomFromNumber(int);
	Reservation* retrieveReservationFromNumber(int);
	bool addReservationToRoom(Reservation*, int);
	int addReservationToFirstRoom(Reservation*);
	void cancelReservation(int);
	double incomeCalculate(int);
	double incomeCalculate();
	void reservationPlan();
};
#endif
