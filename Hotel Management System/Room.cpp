#include "Reservation.h"
#include "Room.h"


Reservation* Availability[30]{0};           //Arxikopoihsh pinaka diathesimothtas

int Room::RoomId = 101;
Room::Room() {
	RoomNumber = RoomId;
	RoomId++;
	for(int i=0;i<30;i++)                   //Arxikopoihsh diathesimothtas
	{
		Availability[i] = nullptr;
	}
}
int Room::getRoomNumber() {
	return RoomNumber;
}
void Room::setMaxCapacity(int i) {
	MaxCapacity = i;
}
int Room::getMaxCapacity() {
	return MaxCapacity;
}
void Room::setPricePerPerson(double i) {
	PricePerPerson = i;
}
double Room::getPricePerPerson() {
	return PricePerPerson;
}
Reservation* Room::getAvailabilityI(int n) {
	return Availability[n];
}
void Room::setAvailabilityI(int n, Reservation* res) {
	Availability[n] = res;
}

//Me thn methodo prosthikhs krathshs tsekaroume th diathesimothta kai tis apaithseis arithmou atomwn se sxesh me th xwrhtikothta
//Ean plhrountai prostithetai h krathsh ston pinaka diathesimothtas diaforetika epistrefetai false
bool Room::addReservation(Reservation* res) {

		bool a = true;
		for (int i = res->getArrival(); i < (res->getArrival() + res->getDaysOfStay()); i++) {
			if (Availability[i] == nullptr && res->getNumberOfPeople() <= MaxCapacity) {
				Availability[i] = res;
				Availability[i]->setReservationNumber(res->getReservationNumber());
				res->setRoom(this);
				a = true;
			}
			else {
				a = false;
			}
		}
		return a;

	}

//Me thn methodo costCalculate() ypologizetai to synolikokostos olwn twn krathsewn tou dwmatiou
double Room::costCalculate() {
	double cost = 0;
	for (int i = 0; i<30; i++) {
		if (Availability[i] != nullptr) {
			cost += (Availability[i]->getNumberOfPeople()*PricePerPerson);
		}
	}
	return cost;
}

//Me thn methodo akurwshs elegxetai ean ypraxei krathsh me sygkekrimeno id wste ean yparxei na akyrwthei
bool Room::cancel(int ReservationId) {
	for (int i = 0; i<30; i++) {
		if (Availability[i] != nullptr) {
			if (Availability[i]->getReservationNumber() == ReservationId) {
				Availability[i] = nullptr;
			}
		}
	}
	return true;
}

//H methodos occupiedPercentage() epistrefei to pososto pou einai plhres ena dwmatio gia ton mhna
float Room::occupiedPercentage() {
	float percentage;
	float counter = 0;
	for (int i = 0; i<30; i++) {
		if (Availability[i] != nullptr) {
			counter++;                      //metrhths gia tis kateilhmmenes meres
		}
	}
	percentage = (counter / 30) * 100;              //typos ypologismoy posostoy
	return percentage;
}

