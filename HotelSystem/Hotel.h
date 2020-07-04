#pragma once
#include <string>
using namespace std;
class Hotel
{
public:
	string Name;
	double Price;
	int Star;
	string Kind;
	double Score;
	string Contact;
	string Describe;
	string Location;
	string Facility;
	bool IfBook = true;
	string Time = "";
	Hotel(string inName, double inPrice, int inStar, string inKind, double inScore,
		string inContact, string inDescribe, string inLocation, string inFacility);
	~Hotel();
};

