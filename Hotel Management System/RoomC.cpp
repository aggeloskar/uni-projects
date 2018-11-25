#include "RoomC.h"
#include "Reservation.h"
#include "Room.h"

RoomC::RoomC() {};
void RoomC::setMinimumDays(int i){
    MinimumDays=i;
}
int RoomC::getMinimumDays(){
    return MinimumDays;
}
void RoomC::setMinimumPeople(int i){
    MinimumPeople=i;
}
int RoomC::getMinimumPeople(){
    return MinimumPeople;
}
//Yperkalupsh ths methodou prosthikis krathshs wste na elegxetai ean ta atoma ths krathshs einai >=twn elaxistwn kai oi meres diamonhs >=twn elaxistwn
bool RoomC::addReservation(Reservation* res){

		bool a = true;
		for (int i = res->getArrival(); i < (res->getArrival() + res->getDaysOfStay()); i++)
		{
			if (Availability[i] == nullptr &&res->getNumberOfPeople() <= getMaxCapacity() && res->getDaysOfStay() >= MinimumDays&&res->getNumberOfPeople() >= MinimumPeople)
			{

				Availability[i] = res;
				Availability[i]->setReservationNumber(res->getReservationNumber());
				res->setRoom(this);
				a = true;
			}
			else
			{
				a = false;
			}

		}
		return a;

}
