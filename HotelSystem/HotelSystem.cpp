// HotelSystem.cpp
//

#include "stdafx.h"
#include "Hotel.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string UserName;   //Used to record each login system user's user name
vector<Hotel *> AllHotel;    //Initialize all hotels
vector<Hotel *> WishList;    //Record your favorite hotel
vector<Hotel *> QueryResult;  //Record query results
vector<Hotel *> BookedList;  //Already reserved
void ToMainMenu();   //Enter the main menu
void Initialise();  //Initialize hotel data			
void BookHotel(string name, string time); //Book hotels
void CheckoutHotel(string name); //Check out hotels
vector<Hotel *> sort(vector<Hotel *> hotel);  //Sort function
void CheckScore(string name, double score);   //Score at check-out

int main()
{
	Initialise();
	cout << "Welcome to the hotel reservation system, please enter your username to login£º" << endl;
	cin >> UserName;
	ToMainMenu();   //Enter the main menu
    return 0;
}

//Enter the main menu
void ToMainMenu() {
	int choose;  //Record user input selection
	int ChooseMenu = -1;   //Record whether to return to the main menu
	cout << "Dear " << UserName << ", Please enter the appropriate selection to do the following£º" << endl;
	cout << "1.Query hotels 2.View your wish list 3.View your booked list 0.Exit system" << endl;
	cin >> choose;
	while (true) {
		//Query hotels
		if (choose == 1) {
			cout << "Please enter the appropriate option to select the query method£º" << endl;
			cout << "1.All hotels 2.By Key words 3.By Star 4.By Price 5.By Facility 6.By Room type" << endl;
			int QueryMethod;
			cin >> QueryMethod;
			cin.get();
			if (QueryMethod == 1) {
				QueryResult = AllHotel;
			}
			else if(QueryMethod == 2)   //By Key words
			{
				QueryResult.clear();
				cout << "Please enter the Key words that you would like to query:" << endl;
				string name;
				getline(cin, name);
				for (int i = 0; i < AllHotel.size(); i++) {
					if (AllHotel[i]->Name.find(name) != string::npos) {
						QueryResult.push_back(AllHotel[i]);
					}
				}
			}
			else if(QueryMethod == 3)   //By Star
			{
				QueryResult.clear();
				cout << "Please enter the Star that you would like to query:" << endl;
				int star;
				cin >> star;
				for (int i = 0; i < AllHotel.size(); i++) {
					if (AllHotel[i]->Star == star) {
						QueryResult.push_back(AllHotel[i]);
					}
				}
			}
			else if (QueryMethod == 4)     //By Price
			{
				QueryResult.clear();
				cout << "Please enter the Price Range that you would like to query:" << endl;
				cout << "Notice:Please enter the lowest price first, then enter the highest price, separated by a space." << endl;
				double MinPrice;
				double MaxPrice;
				cin >> MinPrice >> MaxPrice;
				for (int i = 0; i < AllHotel.size(); i++) {
					if (AllHotel[i]->Price>=MinPrice && AllHotel[i]->Price<=MaxPrice) {
						QueryResult.push_back(AllHotel[i]);
					}
				}
			}
			else if (QueryMethod == 5) {  //By Facility
				QueryResult.clear();
				cout << "Please enter the Facility that you would like to query:" << endl;
				string facility;
				getline(cin, facility);
				for (int i = 0; i < AllHotel.size(); i++) {
					if (AllHotel[i]->Facility.find(facility) != string::npos) {
						QueryResult.push_back(AllHotel[i]);
					}
				}
			}
			else if (QueryMethod == 6) {   //By Room type
				QueryResult.clear();
				cout << "Please enter the Room Type that you would like to query:" << endl;
				string type;
				getline(cin, type);
				for (int i = 0; i < AllHotel.size(); i++) {
					if (AllHotel[i]->Kind.find(type) != string::npos) {
						QueryResult.push_back(AllHotel[i]);
					}
				}
			}
			else {
				cout << "Input error!" << endl;
			}
			if (QueryResult.size() == 0) {
				cout << "The query result is empty!" << endl;
			}
			else
			{
				cout << "The hotels found are as follows:" << endl;
				QueryResult = sort(QueryResult);   //Sort by score
				for (int i = 0; i < QueryResult.size(); i++) {
					cout << "Hotel No." << i + 1 << " :" << QueryResult[i]->Name << " #Room type:" << QueryResult[i]->Kind << " #Can I book? ";
					if (QueryResult[i]->IfBook) {
						cout << "True";
					}
					else
					{
						cout << "False";
					}
					cout << " #Price:" << QueryResult[i]->Price << " #Star:" << QueryResult[i]->Star << " #Score:" << QueryResult[i]->Score;
					cout << endl << "            #Phone number:" << QueryResult[i]->Contact << " #Location:" << QueryResult[i]->Location << endl;
					cout << "            #Services:" << QueryResult[i]->Facility << endl;
				}
				cout << endl << "Please enter the appropriate selection to do the following£º" << endl;
				cout << "1.Book a hotel 2.Add wish list" << endl;
				int AfterQuery;
				cin >> AfterQuery;
				if (AfterQuery == 1) {
					cout << "Please enter the hotel number you want to book:" << endl;
					int number;
					cin >> number;
					if (number<1 || number>QueryResult.size()) {
						cout << "Input error!" << endl;
					}
					else {
						string time;
						cout << "Please enter the time you go to the hotel:" << endl;
						cin >> time;
						BookHotel(QueryResult[number - 1]->Name, time);
					}
				}
				else if (AfterQuery == 2) {
					cout << "Please enter the hotel number you want to add to the wish list:" << endl;
					int number;
					cin >> number;
					if (number<1 || number>QueryResult.size()) {
						cout << "Input error!" << endl;
					}
					else {
						WishList.insert(WishList.begin(), QueryResult[number - 1]);
						cout << "Successfully added a wish list!" << endl;
					}
				}
				else {
					cout << "Input error!" << endl;
				}
			}
			
			cout << endl << "Please enter the appropriate selection to do the following£º" << endl;
			cout << "1.Back to the main menu 0.Exit system" << endl;
			cin >> ChooseMenu;
			break;
		}
		//View your wish list
		else if (choose == 2)
		{
			if (WishList.size() == 0) {
				cout << "Your wish list is empty!" << endl;
			}
			else
			{
				cout << endl << "Your wish list is as follows£º" << endl;
				for (int i = 0; i < WishList.size(); i++) {
					cout << "Hotel No." << i + 1 << " :" << WishList[i]->Name << " #Room type:" << WishList[i]->Kind << " #Can I book? ";
					if (WishList[i]->IfBook) {
						cout << "True";
					}
					else
					{
						cout << "False";
					}
					cout << " #Score:" << WishList[i]->Score << endl;
					cout << "            #Phone number:" << WishList[i]->Contact << " #Description:" << WishList[i]->Describe << endl;
				}
			}
			
			cout << endl << "Please enter the appropriate selection to do the following£º" << endl;
			cout << "1.Back to the main menu 2.Book a hotel 3.Delete a hotel 0.Exit system" << endl;
			cin >> ChooseMenu;
			if (ChooseMenu == 2) {
				cout << endl << "Please enter the hotel number you want to book:" << endl;
				int number;
				cin >> number;
				if (number<1 || number>WishList.size()) {
					cout << "Input error!" << endl;
				}
				else {
					string time;
					cout << "Please enter the time you go to the hotel:" << endl;
					cin >> time;
					BookHotel(WishList[number - 1]->Name, time);
				}
				ChooseMenu = 1;
			}
			if (ChooseMenu == 3) {
				cout << endl << "Please enter the hotel number you want to delete:" << endl;
				int number;
				cin >> number;
				if (number<1 || number>WishList.size()) {
					cout << "Input error!" << endl;
				}
				else {
					WishList.erase(WishList.begin() + (number - 1));
					cout << endl << "Delete room success!" << endl;
				}
				ChooseMenu = 1;
			}
			break;
		}
		//View your booked list
		else if (choose == 3)
		{
			if (BookedList.size() == 0) {
				cout << "Your booked list is empty!" << endl;
			}
			else
			{
				cout << endl << "Your booked list is as follows£º" << endl;
				for (int i = 0; i < BookedList.size(); i++) {
					cout << "Hotel No." << i + 1 << " :" << BookedList[i]->Name << " #Room type:" << BookedList[i]->Kind;
					cout << " #Score:" << BookedList[i]->Score << " #Price:" << BookedList[i]->Price << endl;
					cout << "            #Phone number:" << BookedList[i]->Contact << " #Location:" << BookedList[i]->Location << endl;
					cout << "            #Estimated check-in time:" << BookedList[i]->Time << endl;
				}
			}
			cout << endl << "Please enter the appropriate selection to do the following£º" << endl;
			cout << "1.Back to the main menu 2.Check out a room 0.Exit system" << endl;
			cin >> ChooseMenu;
			if (ChooseMenu == 2) {
				if (BookedList.size() == 0) {
					cout << "Your booked list is empty!" << endl;
				}
				else
				{
					cout << endl << "Please enter the hotel number you want to check out:" << endl;
					int number;
					cin >> number;
					if (number<1 || number>BookedList.size()) {
						cout << "Input error!" << endl;
					}
					else {
						string checkname = BookedList[number - 1]->Name;
						CheckoutHotel(checkname);
						BookedList.erase(BookedList.begin() + (number - 1));
						cout << endl << "Please enter your score for this hotel:" << endl;
						cout << "Notice:Please enter a number between 0 and 5." << endl;
						double checkscore;
						cin >> checkscore;
						CheckScore(checkname, checkscore);
					}
				}
				ChooseMenu = 1;
			}
			break;
		}
		//Exit
		else if (choose == 0)
		{
			cout << "Thank you for using! Goodbye!" << endl;
			break;
		}
		else
		{
			cout << "Please enter the correct option£º" << endl;
			cin >> choose;
		}
	}

	if (ChooseMenu==1) {
		ToMainMenu();
	}
	else if(ChooseMenu==0)
	{
		cout << "Thank you for using! Goodbye!" << endl;
	}
	
}

//Initialize hotel data
void Initialise() {
	Hotel *hotel1 = new Hotel("Millennium Seoul Hilton", 1469, 5, "Deluxe Twin Room", 4.5, "822-753-7788", "Luxury hotel,Renovated in 2015, 22 floors, 680 rooms",
		"50,Sowol-ro,Jung-gu,Seoul,Korea", "wireless internet, parking, restaurant, hot shower, hair dryer, toiletries, wake up service, room service, credit card spending");
	Hotel *hotel2 = new Hotel("PJ Hotel", 816, 4, "Standard Double Room", 4.4, "822-2280-7000", "In the bustling city centre, easy access to shopping",
		"71,Mareunnae-ro,Jung-gu,Seoul,Korea", "wireless internet, parking, restaurant, hot shower, Meeting room, ATM, small fridge, desk, laundry service");
	Hotel *hotel3 = new Hotel("JW Marriott Dongdaemun Square Seoul", 1459, 5, "Deluxe Guest Room", 4.7, "82-2-22763000", "Enjoy the world tour from Marriott's courtesy",
		"279,Cheonggyecheon-ro,Jongno-gu,Seoul,Korea", "Spa, Indoor pool, gym, meeting room, smoking area, ATM, safe, garden, bar, laundry service");
	Hotel *hotel4 = new Hotel("Glad Hotel Mapo", 468, 3, "Standard Double Room", 4.8, "822-2197-5000", "Opened in 2018, with 378 rooms in Mapo, its prime location makes it a desirable accommodation option in Seoul",
		"92,Mapo-daero,Mapo-gu,Seoul,Korea", "free parking, Western food, gym, business center, shopping mall, private bathroom, wake up service, luggage storage");
	Hotel *hotel5 = new Hotel("Hotel Gracery Seoul", 543, 4, "Standard Twin Room", 4.6, "82-2-69360111", "Opened at 2011.09.01, we believe that Hotel Gracery Seoul is your best choice whether you are a day trip or a deep tour",
		"12,Sejong-daero 12-gil,Seoul,Korea", "paid parking, business center, elevator, smoking area, air conditioning, heating, complimentary toiletries, slippers, wake up service");
	Hotel *hotel6 = new Hotel("Lumia Hotel Myeong Dong Seoul", 956, 5, "Deluxe Twin Room", 4.6, "822-755-1300", "Comfortable, opened in 2015, 6 floors, 55 rooms",
		"31-9,toegye-ro 8-gil,jung-gu,Seoul,Korea", "free parking, business center, elevator, coffee shop, executive lounge, domestic long distance (charged), air conditioning, free wifi, heating, laundry service, room service");
	Hotel *hotel7 = new Hotel("Fairfield by Marriott Seoul", 448, 3, "Premier King", 4.8, "82-02-21089000", "Upscale, renovated in 2018, 572 rooms",
		"870,Gyeongin-ro,Yeongdeungpo-gu,Seoul,Korea", "meeting room, business center, elevator, ATM, internet access in public areas, laundry service, luggage storage, currency exchange");
	Hotel *hotel8 = new Hotel("Gald Live Gangnam Seoul", 501, 2, "Superior Double Room", 4.1, "82-2-61775000", "Opened in 2016, 210 rooms",
		"223,Bongeunsa-ro,Gangnam-gu,Seoul,Korea", "paid parking, outdoor pool, meeting room, elevator, coffee shop, ATM, infirmary, heating, ballroom, bar, wake up service");
	Hotel *hotel9 = new Hotel("Baiton Seoul Dongdaemun", 463, 4, "Twin Room", 4.8, "822-2269-2550", "Located in the center of Seoul's urban life",
		"346,Dongho-ro,Jung-gu,Seoul,Korea", "free parking, gym, meeting room, elevator, business center, heating, air conditioning, garden, support credit card, wake up service, laundry service, luggage storage");
	Hotel *hotel10 = new Hotel("Hotel BonBon Seoul", 330, 3, "Deluxe Room", 4.7, "82-2-7789900", "Opened in 2013, renovated in 2015, 4 floors, 20 rooms",
		"8 Namdaemunro 9-gil,Seoul,Korea", "Internet access in public areas, daily newspaper, heating, partial room coverage, wake up service, credit card support, dry cleaning, car service");
	Hotel *hotel11 = new Hotel("New Seoul Hotel", 338, 4, "Standard Double Room", 3.9, "82-2-7358800", "Comfortable, opened in 1969, renovated in 2014, 16 floors, 184 rooms",
		"16,Sejong-daero 22-gil,Jung-gu,Seoul,Korea", "Japanese restaurant, Western food, conference room, business center, 24-hour front desk, mini bar, bathrobe, air conditioning, hair dryer, credit card, wake up service, luggage storage");
	Hotel *hotel12 = new Hotel("Park Hyatt Seoul", 1758, 5, "Park Deluxe Room", 4.5, "82-2-20161234", "Stylish rooms and suites, opened in 2005, 24 floors, 185 rooms",
		"606 Teheran-ro(995-14 Daechi-dong),Gangnam-gu,Seoul,Korea", "paid parking, Japanese restaurant, smoking area, meeting room, elevator, lobby bar, infirmary, bar, sauna, credit card support, laundry service");
	AllHotel.push_back(hotel1);
	AllHotel.push_back(hotel2);
	AllHotel.push_back(hotel3);
	AllHotel.push_back(hotel4);
	AllHotel.push_back(hotel5);
	AllHotel.push_back(hotel6);
	AllHotel.push_back(hotel7);
	AllHotel.push_back(hotel8);
	AllHotel.push_back(hotel9);
	AllHotel.push_back(hotel10);
	AllHotel.push_back(hotel11);
	AllHotel.push_back(hotel12);
	WishList.push_back(hotel4);
	WishList.push_back(hotel6);
}

//Book hotels
void BookHotel(string name, string time) {
	for each (Hotel *hotel in AllHotel)
	{
		if (hotel->Name == name) {
			if (hotel->IfBook) {
				hotel->IfBook = false;
				hotel->Time = time;
				BookedList.insert(BookedList.begin(), hotel);
				cout << endl << "Book hotel success!" << endl;
			}
			else {
				cout << "Sorry,this hotel cannot be reserved!" << endl;
			}
		}
	}
}

//Sort function
vector<Hotel *> sort(vector<Hotel *> hotel) 
{
	for (int i = 0; i < hotel.size() - 1; i++) {
		for (int j = 0; j < hotel.size() - 1 - i; j++) {
			if (hotel[j]->Score < hotel[j + 1]->Score) {
				Hotel *temp = hotel[j];
				hotel[j] = hotel[j + 1];
				hotel[j + 1] = temp;
			}
		}
	}
	return hotel;
}

//Check out hotels
void CheckoutHotel(string name) {
	for each (Hotel *hotel in AllHotel)
	{
		if (hotel->Name == name) {
			hotel->IfBook = true;
			cout << "Check out hotel success!" << endl;
		}
	}
}

//Score at check-out
void CheckScore(string name, double score) {
	for each (Hotel *hotel in AllHotel)
	{
		if (hotel->Name == name) {
			hotel->Score = (hotel->Score + score) / 2;
			cout << "Give your score success!" << endl;
			cout << endl;
		}
	}
}