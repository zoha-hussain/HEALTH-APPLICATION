#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "Account.h"
#include "Doctorh.h"
#include "Patienth.h"
#include "Pharmacy.h"
#include "BloodDonatorH.h"
#include "DietPlan.h"
using namespace std;

class Doctor;
class Patient;
class Pharmacy;
class BloodDonator;
class DietPlan;

class Admin :protected Person {
private:
	//attributes  
public:
	//Member Fuctions
	void createAccount(Patient& p);
	void loginToAccount(Patient& p);
	bool findDoctor(char[20], Doctor d[12], int chosenDoc[3]);
	bool checkAvailability(Doctor d, char);
	string selectTime();
	bool scheduleAppointment(Doctor d[2], int, int chosenDoc[3]);
	void displayDetails()const;
	void patientBilling(Patient& p, Doctor& d, int);
	void medicineBilling(Patient& p, Pharmacy& ph, int);
	void acceptDonation(BloodDonator& b1);
	void displayDietPlanDetails(DietPlan d[7], string);

	// default constructor
	Admin() {}

	// parameterized constructor
	Admin(char fn[20], char ln[20], char g, int a, int id) :Person(fn, ln, g, a, id) {}
};