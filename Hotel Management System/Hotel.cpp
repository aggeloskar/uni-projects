#include "Hotel.h"
#include "Reservation.h"
#include "Room.h"
#include "Hotel.h"
#include "RoomA.h"
#include "RoomC.h"
#include <vector>
#include <iostream>
#include <iomanip>

//Opws parathreitai parakatw xrhsimopoioyme vectors gia th dynamikh katanomh twn dwmatiwn kai twn krathsewn
//Gia ayto to logo kai xrhsimopoioyme th synarthsh push_back() stis methodous addRoom() kai setReservations()


//Methodos prothikis dwmatioy
void Hotel::addRoom(Room* r)
{
	rooms.push_back(r);
}

vector<Room*> Hotel::getRoom()
{
	return rooms;
}


void Hotel::setReservations(Reservation* res)
{
	reservations.push_back(res);
}

vector<Reservation*> Hotel::getReservations()
{
	return reservations;
}

//Methodos anakthshs dwmatioy apo kwdiko
Room* Hotel:: retrieveRoomFromNumber(int roomid)
{
	Room* c = nullptr;
	for (Room* rg : rooms) {                            //Xrhsh misd ranged based for loop gia elegxo yparksis kai taytopoihshs dwmatiou
		if (rg->getRoomNumber() == roomid)
		{
			c = rg; break;
		}
		else {

			c = nullptr;
		}
	}
	return c;
}

//Methodos Anakthshs krathshs apo kwdiko
Reservation* Hotel:: retrieveReservationFromNumber(int resid)
{
	Reservation* a = nullptr;
	for (int i = 0; i < reservations.size(); i++) {
		if(reservations[i]->getReservationNumber()==resid)
		{
			a = reservations[i];
			break;
		}

	}
	return a;
}

//Methodos Prosthikis Krathshs se kapoio sygkekrimeno dwmatio
bool Hotel::addReservationToRoom(Reservation* r, int rnumb)
{
	bool a = true;
	if (retrieveRoomFromNumber(rnumb) == nullptr)                                       //Elegxos yparksis dwmatioy
	{
		cout << "H krathsh den egine kathws den vrethike to dwmatio!"<<endl;
		a = false;
	}
	else
	{
		for (int k = r->getArrival(); k < (r->getArrival() + r->getDaysOfStay()); k++)
		{
			if (retrieveRoomFromNumber(rnumb)->getAvailabilityI(k) != nullptr)                      //Elegxos plhrothtas
			{
				cout << "To dwmatio einai katoxyrwmeno. H krathsh den pragmatopoihthike!"<<endl;
				a = false;
				break;
			}
			else
			{
				r->setRoom(retrieveRoomFromNumber(rnumb));
				if (retrieveRoomFromNumber(rnumb)->addReservation(r) == false)                      //Elegxos plhrothtas periorismwn dwmatiou...(arithmou atomwn,xwrhtikothtas,..)
				{
					r->getRoom()->cancel(r->getReservationNumber());
					cout << "H krathsh den prostethike.Elegxte tis apaithseis toy dwmatiou!"<<endl;
					a = false;
					break;
				}
				cout << "H krathsh me kwdiko " << r->getReservationNumber() << " prostethike epityxws sto dwmatio me kwdiko " << rnumb<<endl;
				reservations.push_back(r);                                                                 //Prosthiki krathshs mesw ths push_back()
				a = true;
				break;
			}

		}
		if (a == false) { delete r; }
	}
	return a;
}

//Prosthiki krathshs sto dwmatio pou mporei na prostethei.H methodos epistrefei ton kwdiko dwmatiou opou mphke h krathsh alliws emfanizei mhnyma otan
// den einai dynath h prosthiki se kapoio dwmatio
int Hotel::addReservationToFirstRoom(Reservation* reserv)
{
	int a=0 ;
	int stopper = 0;
	int reservid=-1;
	for (int i = 0; i < rooms.size(); i++) {
		for (int k = reserv->getArrival(); k < (reserv->getArrival() + reserv->getDaysOfStay()); k++)
		{
			if (rooms[i]->getAvailabilityI(k) != nullptr)
			{

				a = 0;
			}
			else
			{
				if (rooms[i]->addReservation(reserv) == false)
				{
					rooms[i]->cancel(reserv->getReservationNumber());
					if (i < rooms.size() + 1) {
						i = i + 1;
					}
					else {
						a = 0;

					}
					break;

				}
				else
				{
					reserv->setRoom(rooms[i]);
					a = rooms[i]->getRoomNumber();
					rooms[i]->addReservation(reserv);
					retrieveRoomFromNumber(rooms[i]->getRoomNumber())->addReservation(reserv);
					reservid = reserv->getReservationNumber();
					reservations.push_back(reserv);                     //Prosthiki krathshs
					stopper = 1;
				}

			}

			if (a != 0)
			{
				break;
			}
		}
		if (stopper == 1) { break; }
	}
		if (a == 0)
		{
			delete reserv;
			cout<<"De vrethike diathesimo dwmatio!"<<endl;
			return a;
		}
		else {

			cout<<"H krathsh me kwdiko " << reservid << " prostethike epityxws sto dwmatio me kwdiko " << a << ""<<endl;

			return a;
		}
}

//Methodos akyrwshs krathsewn kata thn opoia dinei o xrhsths ton kwdiko krathshs pros akyrwsh kai ean yparxei oloklhrwnetai h diadikasia alliws emfanizetai mhnyma oti h krathsh den akyrwthike
void Hotel::cancelReservation(int reservationid)
{
	if (retrieveReservationFromNumber(reservationid) != nullptr)
	{
		for (int i = 0; i < reservations.size(); i++)
	{
		if (reservations[i]->getReservationNumber() == reservationid)           //elegxos yparksis kwdikoy krathshs
		{
			reservations[i]->getRoom()->cancel(reservationid);
			delete reservations[i];
			reservations.erase(reservations.begin() + i);
		}
	}
		cout<< "H krathsh me kwdiko " << reservationid << " akyrwthike!"<<endl;
	}

	else
	{
		cout << "H krathsh me kwdiko " << reservationid << " den akyrwthike!"<<endl;
	}

}

//Methodos ypologismoy esodwn sygkekrimenou dwmatiou
double Hotel::incomeCalculate(int roomnumb)
{

	double earnings;
	earnings = retrieveRoomFromNumber(roomnumb)->costCalculate();
	return earnings;
}

//Methodos ypologismou esodwn
double Hotel::incomeCalculate()
{
    double earnings=0;
	for(Room* r:rooms)
	{
		 earnings += r->costCalculate();
	}
	return earnings;

}

//Methodos emfanishs planoy krathsewn
void Hotel::reservationPlan()
{
	cout << "Dwmatio\t";
	for (int i = 1; i < 31; i++) {
		cout << setw(3) << i;}
	cout << endl;
	for (Room* roomavailable : rooms) {
		cout <<roomavailable->getRoomNumber() << "      ";
		for (int k = 0; k < 30; k++)
		{
			if (roomavailable->getAvailabilityI(k) == nullptr) {
				cout << " - ";
			}
			else {
			 cout << " * ";
			}

		}
		cout <<endl;
	}
}
