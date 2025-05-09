#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "Doctorh.h"
#include "Account.h"
#include "AdminH.h"
#include "Pharmacy.h"
using namespace std;

class Doctor;
class Pharmacy;

class Patient :protected Person {
	friend class Admin;
private:
	double balance;
	Account acc;
	int chooseDoctor();
	bool checkValidity(double amount);
public:
	//getters/accessors
	const char* getAccountEmail()const;
	long long int getAccountContact()const;
	const char* getAccountUsername()const;
	Account getAccount()const;

	//setters/mutators
	void setAccountEmail(const char* e);
	void setAccountContact(const long long int c);

	//Member Fuctions 
	void input();
	int Patientmenu();
	void inputreport();
	bool makeAppointment(Doctor d[12], Admin a, int chosenDoc[3]);
	void displayDetails()const;
	bool operator+(Doctor& d);

	// default constructor
	Patient() {
		age = 0;
	}

	// parameterized constructor
	Patient(char fn[20], char ln[20], char g, int a, int id) :Person(fn, ln, g, a, id) {
		Patientmenu();
	}

};