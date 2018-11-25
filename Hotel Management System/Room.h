#ifndef ROOM_H_
#define ROOM_H_

using namespace std;

class Reservation;
class Room {
private:
	int RoomNumber;
	int MaxCapacity;
	double PricePerPerson;
	static int RoomId;

public:
	Reservation* Availability[30];

	Room();
	int getRoomNumber();
	void setMaxCapacity(int);
	int getMaxCapacity();
	void setPricePerPerson(double);
	double getPricePerPerson();
	virtual bool addReservation(Reservation*);
	virtual double costCalculate();
	virtual bool cancel(int);
	float occupiedPercentage();
	Reservation* getAvailabilityI(int);
	void setAvailabilityI(int, Reservation*);
};



#endif
