#include "stdafx.h"
#include "Hotel.h"


Hotel::Hotel(string inName, double inPrice, int inStar, string inKind, double inScore,
	string inContact, string inDescribe, string inLocation, string inFacility)
{
	Name = inName;
	Price = inPrice;
	Star = inStar;
	Kind = inKind;
	Score = inScore;
	Contact = inContact;
	Describe = inDescribe;
	Location = inLocation;
	Facility = inFacility;
}


Hotel::~Hotel()
{
}
