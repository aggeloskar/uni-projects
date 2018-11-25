#ifndef ROOMC_H
#define ROOMC_H

#include "Room.h"


class RoomC : public Room {
private:
	int MinimumDays;
	int MinimumPeople;
public:
	RoomC();
	void setMinimumDays(int);
	int getMinimumDays();
	void setMinimumPeople(int);
	int getMinimumPeople();
	virtual bool addReservation(Reservation*) override;
};

#endif // ROOMC_H
