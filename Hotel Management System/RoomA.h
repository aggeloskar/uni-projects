#ifndef ROOMA_H
#define ROOMA_H

#include "Room.h"


class RoomA : public Room
{
   private:
	double PricePerDay;
public:
	RoomA();
	void setPricePerDay(double);
	double getPricePerDay();
	virtual double costCalculate() override;        //To override voithaei sto na apofeyxthoun bugs paragontas ena mhnuma lathous sto compilation(yperkalupsh methodou timologhshs)
};

#endif // _H
