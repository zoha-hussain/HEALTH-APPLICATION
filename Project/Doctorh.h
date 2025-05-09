#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "Account.h"
#include "AdminH.h"
using namespace std;

class Doctor :protected Person {
	friend class Admin;
private:
	// attributes
	double balance;
	float fees;
	char specialist[20];
	int firstWorkHours[2];
	int secondWorkHours[2];
	bool availability[2];
public:
	// default constructor
	Doctor() {}
	// parameterized constructor
	Doctor(char fn[20], char ln[20], char g, int a, int id, char s[20], int sh1, int sh2, int eh1, int eh2,
		bool a1, bool a2, float f, double b) :
		Person(fn, ln, g, a, id) {
		int i;
		for (i = 0; s[i] != '\0'; i++)
			specialist[i] = s[i];
		specialist[i] = '\0';
		firstWorkHours[0] = sh1;
		firstWorkHours[1] = sh2;
		secondWorkHours[1] = eh2;
		secondWorkHours[0] = eh1;
		availability[0] = a1;
		availability[1] = a2;
		fees = f;
		balance = b;
	}

	//getter/accessor
	const char* getSpecialist()const;
	int getFirstStartingHour()const;
	int getFirstEndingHour()const;
	int getSecondStartingHour()const;
	int getSecondEndingHour()const;
	float getFees()const;
	bool getFirstAvailibility()const;
	bool getSecondAvailibility()const;

	//setter/mutator
	void setSpecialist(const char* s);
	void setFirstEndingHour(int eh);
	void setFirstStartingHour(int sh);
	void setSecondEndingHour(int eh);
	void setSecondStartingHour(int sh);
	void setFees(const float f);
	void setFirstAvailibility(const bool a);
	void setSecondAvailibility(const bool a);
	void setBalance(const double b);

	//member functions
	void Doctormenu();
	void displayDetails()const;
};