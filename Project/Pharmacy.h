#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Person.h"
#include "Account.h"
#include "AdminH.h"
#include "Medicine.h"
using namespace std;

class Pharmacy {
	friend class Admin;
	double balance;
public:
	Medicine m[10];

	Pharmacy() {}

	void readMedicineFile();

	//getter of medicine at required index
	Medicine getMedicine(int)const;

	//setter of balance
	void setBalance(const double b);
	//getter of balance
	double getbalance()const;

	//member functions
	void displaymedicine();
	void decrementStock(int);
	void incrementStock(int);
	int purchasingMed();

};