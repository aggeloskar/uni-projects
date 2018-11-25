#include "Reservation.h"
#include "Room.h"
#include "RoomA.h"


RoomA::RoomA(){}
void RoomA::setPricePerDay(double i){
    PricePerDay=i;
}
double RoomA::getPricePerDay(){
    return PricePerDay;
}

//H parakatw methodos yperkalyptei th methodo timologhshs agnowntas ton arithmo twn atomwn kai lamvanontas yp opsin mono tis meres diamonhs
double RoomA::costCalculate(){
    double cost=0;
        for(int i=0; i<30; i++){
            if(getAvailabilityI(i)!=nullptr){
                cost+=PricePerDay;
            }
        }
    return cost;
}
