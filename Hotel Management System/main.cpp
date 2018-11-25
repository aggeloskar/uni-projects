#include <iostream>
#include <string>
#include "Reservation.h"
#include "Room.h"
#include "RoomA.h"
#include "RoomC.h"
#include "Hotel.h"
#include <ctime>
#include <iomanip>
#include <cstdlib>


using namespace std;

int main()
{
	string clientName;
	int number;
	int arrivalDay;
	int daysToStay;
	int roomiddecider;
	int roomid;
	Hotel* hotel=new Hotel();
	int userinput;                              //To xrhsimopoioume gia eisodo apo to xrhsth sth sunexeia

	string firstNames[] = { "Vasilis", "Dimitris", "Nikos", "Antwnis", "Pantelis", "Kwstas", "Giwrgos", "Elena", "Swkraths", "Panos"};

	string lastNames[] = { "Karras      ", "Mitropanos  ", "Mazwnakis   ", "Makropoulos  ", "Arguros     ", "Remos      ","Pantelidis   ","Paparizou   ", "Malamas     ","Berths      " };

	//Parakatw einai h dhmiourgia dwmatiwn. Tyxaia dhmiourgoume diaforous typwn dwmatiwn kai opoy xreiazetai kaloyme tis aparaithtes methodous
		Room* room1 = new Room();
		room1->setPricePerPerson(80);
		room1->setMaxCapacity(2);
		hotel->addRoom(room1);

		Room* room2 = new Room();
		room2->setPricePerPerson(35);
		room2->setMaxCapacity(3);
		hotel->addRoom(room2);

		RoomA* room3 = new RoomA();
		room3->setPricePerDay(20);
		room3->setPricePerPerson(25);
		room3->setMaxCapacity(2);
		hotel->addRoom(room3);

		RoomA* room4 = new RoomA();
		room4->setPricePerDay(80);
		room4->setPricePerPerson(40);
		room4->setMaxCapacity(4);
		hotel->addRoom(room4);

		RoomC* room5 = new RoomC();
		room5->setMinimumDays(3);
		room5->setMinimumPeople(4);
		room5->setMaxCapacity(5);
		room5->setPricePerPerson(25);
		hotel->addRoom(room5);

		RoomC* room6 = new RoomC();
		room6->setMinimumDays(6);
		room6->setMinimumPeople(5);
		room6->setPricePerPerson(15);
		room6->setMaxCapacity(4);
		hotel->addRoom(room6);

		RoomA* room7 = new RoomA();
		room7->setPricePerDay(200);
		room7->setPricePerPerson(150);
		room7->setMaxCapacity(3);
		hotel->addRoom(room7);

		Room* room8 = new Room();
		room8->setPricePerPerson(85);
		room8->setMaxCapacity(4);
		hotel->addRoom(room8);

		RoomA* room9 = new RoomA();
		room9->setPricePerDay(65);
		room9->setPricePerPerson(20);
		room9->setMaxCapacity(2);
		hotel->addRoom(room9);

		RoomC* room10 = new RoomC();
		room10->setMinimumDays(3);
		room10->setMinimumPeople(3);
		room10->setPricePerPerson(50);
		room10->setMaxCapacity(6);
		hotel->addRoom(room10);

		srand(time(NULL));
		int k = 0;
		int term = 0;
		int random_cancel;
	while(term!=-1){
            //Akolouthei h Dhmiourgia mias krathshs me tyxaio tropo
			while (k == 0) {
				string fullName = firstNames[rand() % (sizeof(firstNames) / sizeof(firstNames[0]))] + " " + lastNames[rand() % (sizeof(lastNames) / sizeof(lastNames[0]))]; //epilogh tyxaiwn onomatwn apo tous pinakes pou dhmiourghsame
				Reservation* reservation = new Reservation();
				reservation->setClient(fullName);
				reservation->setArrival(rand() % 30);                                                           //tyxaia hmera afikshs
				reservation->setDaysOfStay(rand() % (31 - reservation->getArrival())+1);                           //tyxaies meres diamonhs
				reservation->setNumberOfPeople(rand() % 5 + 1);                                                    //tyxaios arithmos atomwn pou tha meinoun
				hotel->addReservationToFirstRoom(reservation);                                                   //prostithetai h krathsh sto prwto dwmatio tou ksenodoxeiou
				random_cancel = rand() % 4;                                                                     //25% pithanothta akurwshs
				if (random_cancel == 2)
				{
					int resget = rand() % hotel->getReservations().size()+1;

					hotel->cancelReservation(resget);                       //akurwsh ths tyxaias krathshs pou pairnoume sto resget

				}
				k = 1;
			}
			cout << "1. Epomeni epanalipsi programmatos" << endl;
			cout << "2. Prosthiki kratisis" << endl;
			cout << "3. Akyrwsi kratisis" << endl;
			cout << "4. Provoli kratisewn" << endl;
			cout << "5. Provoli dwmatiwn" << endl;
			cout << "6. Provoli planoy kratisewn" << endl;
			cout << "7. Provoli Esodwn" << endl;
			cout << "8. Exodos" << endl;
			cout << "->";
			cin >> userinput;
			if (userinput < 1 || userinput > 8)
			{
            cout << "Dwse mia timh apo to 1 ews to 8!!!" <<endl;
			}
			if (userinput == 8)
            {
                term = -1;
            }
        switch(userinput)
			{
			case 1:
				k = 0;                  //Synexizei thn emfwleymenh while loop
				break;
			case 2:           //PROSTHIKI
			{
				cin.ignore(256, '\n');                                                  //Katharizei to input buffer
				Reservation* newres = new Reservation();
				cout << "Eisagete onomatepwnumo:" << endl;
				getline(cin, clientName);
				cout << "Hmera afiksis:" << endl;
				cin >> arrivalDay;

				while (cin.fail()) {
					cout << "Lathos eisodos! Parakalw eisagete pali! " << endl;
					cin.clear();                                                                     //Kanei clear to error flag tou cin
					cin.ignore(256, '\n');                                                           //xreiazetai meta to cin.clear() gia na paei sthn epomenh grammh
					cin >> arrivalDay;
				}
				cout << "Meres diamonhs:" << endl;
				cin >> daysToStay;

				while (cin.fail()) {
					cout << "Lathos eisodos! Parakalw eisagete pali! " << endl;
					cin.clear();
					cin.ignore(256, '\n');
					cin >>daysToStay;
				}
				cout << "Arithmos atomwn:" << endl;
				cin >> number;

				while (cin.fail()) {
					cout << "Lathos eisodos! Parakalw eisagete pali! " << endl;
					cin.clear();
					cin.ignore(256, '\n');
					cin >> number;
				}
				cout << "Pieste 1 gia epilogh sygkekrimenou dwmatiou. (alliws otidhpote gia automath anathesh). " << endl;
				cin >> roomiddecider;
				while (cin.fail()) {
					cout << "Lathos eisodos! Parakalw eisagete pali! " << endl;
					cin.clear();
					cin.ignore(256, '\n');
					cin >> roomiddecider;
				}
				if (roomiddecider == 1) {                                            //Epilogh sygkekrimenou dwmatiou
					cout << "Eisagete Kwdiko Dwmatiou:" << endl;
					cin >> roomid;
				}
				else {
					roomid = -1;                                                        //To orizoume -1 wste na to prosthesoume sto prwto dwmatio argotera
				}
				newres->setArrival(arrivalDay - 1);
				newres->setDaysOfStay(daysToStay);
				newres->setClient(clientName);
				newres->setNumberOfPeople(number);
				if (roomid != -1) {
					hotel->addReservationToRoom(newres, roomid);
				}
				else {
					hotel->addReservationToFirstRoom(newres);
				}
			}
					break;
                case 3:             //AKURWSH
				int idToCancel;
				cout << "Eisagete Kwdiko Krathshs pros akurwsh:" << endl;
				cin >> idToCancel;
				while (cin.fail()) {
					cout << "Lathos eisodos! Parakalw eisagete pali!" << endl;
					cin.clear();
					cin.ignore(256, '\n');
					cin >> idToCancel;
				}
				hotel->cancelReservation(idToCancel);
				break;
                case 4:             //PROVOLH KRATHSEWN
				cout<<"Kwdikos Kratisis  Onomatepwnumo Pelath \t\t Kwdikos Dwmatiou "<<endl;
				for (Reservation* r : hotel->getReservations()) {                           //Ranged based for loop...prospelash krathsewn pou uparxoun mesw methodou get

					if (r->getRoom() == nullptr) { cout<<""; }                              //Emfanish kenwn an den uparxoun krathseis
					else {

						cout << r->getReservationNumber() << "\t\t  " << r->getClient() << "\t\t " << r->getRoom()->getRoomNumber() << endl;

					}
				}
				break;
				case 5:             //PROVOLH DWMATIWN
				cout << "ID \t Plirothta \tEsoda \t" << endl;
				for (Room* r : hotel->getRoom())                                            //Ranged based for loop..prospelash dwmatiwn
				{
					cout << r->getRoomNumber() << " \t " << setprecision(4) << r->occupiedPercentage() << "  \t\t" << hotel->incomeCalculate(r->getRoomNumber()) << " \t " << endl;

				}
				break;
				case 6:             //PROVOLH PLANOU KRATHSEWN
				hotel->reservationPlan();
				break;
				case 7:              //PROVOLH ESODWN
				int roomind;
				cout << "Pieste 1 gia epilogh sygkekrimenou dwmatiou. (alliws otidhpote gia automath anathesh)." << endl;
				cin >> roomind;
				while (cin.fail()) {
					cout << "Lathos eisodos! Parakalw eisagete pali!" << endl;
					cin.clear();
					cin.ignore(256, '\n');
					cin >> roomind;
				}
				if (roomind == 1)
				{
					int RoomNumberb;
					int rtester=-1;
					cout << "Eisagete Kwdiko Dwmatiou:" << endl;
					cin >> RoomNumberb;
					while (cin.fail()) {
						cout << "Lathos eisodos! Parakalw eisagete pali!" << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cin >> RoomNumberb;
					}
					for(Room* r:hotel->getRoom())
					{
						if (RoomNumberb == r->getRoomNumber()) { rtester = 0; break; }
					}
					if (rtester != -1)
					{
						cout << "Esoda dwmatiou " << RoomNumberb << "  : " << hotel->incomeCalculate(RoomNumberb) << " $." << endl;
						break;
					}
					else
					{
						cout << "Den yparxei dwmatio me kwdiko " <<RoomNumberb << endl;
					}
				}
				else {

					cout << "Synolika esoda : " << hotel->incomeCalculate() << " $." << endl;

				}
				break;
			default:
				break;
			}
		}
		return 0;
}


