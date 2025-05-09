#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <string>
#include <string.h>
#include <conio.h>
#include <cstring>
#include "Account.h"
#include "DoctorH.h"
#include "PatientH.h"
#include "Person.h"
#include "BloodDonatorH.h"
#include "AdminH.h"
#include "Pharmacy.h"
#include "Medicine.h"
#include "DietPlan.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//global function prototypes
void readDoctorFile(Doctor(&d)[12]);
void writeDoctorFile(const Doctor d[12]);
void readAdminFile(Admin& a);
void readDietPlan(DietPlan(&d)[7], string fileName);
void writeReportFile(int, int, int, int, int);
void readReportFile(Patient& p);
void writeAccountFile(Account& a);
void readAccountFile(Account& accFile, Account& a, bool& userFound);
string BloodGroupInput();
int BloodGroupBottlesInput();
char chooseReviewType();
char askForFeedback();
int dietPlanMenu();
void signUpOrLogin(Admin& a, Patient& p);
int randomize();
void welcomeUser();
void systemPause();
void thankUser();

//template function
template <typename T>
T giveRating();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Functions of class Account:

//member functions

//taking input of username
void Account::inputForSignup() {
	cout << "Enter email:";
	cin >> email;
	cout << "Enter contact:";
	cin >> contact;
	cout << "Enter Username:";
	cin >> username;
	cout << "----------------------------------------------------------------------------------------" << endl;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 14);
	cout << "Enter Password, Such That it Contains 8 to 16 Characters.It Should Include:" << endl;
	cout << "Uppercase Characters;" << endl << "Lowercase Characters;" << endl;
	cout << "Numbers;" << endl << "& Special Symbols." << endl << "It should not include:" << endl;
	cout << "Tabs or" << endl << "Spaces:" << endl;
	mask(password);
}

void Account::inputForLogin() {
	cout << "Enter Username:";
	cin >> username;
	cout << "Enter Password:";
	mask(password);
}

//checking if conditions of password are satisfied or not
void Account::checkConditions(int length) {
	int i;
	int upper = 0, lower = 0, sym = 0, num = 0; //Upper:Uppercase Letter; Lower:lowercase letter;Sym:Symbol;Num=Number
	while (num == 0 || upper == 0 || sym == 0 || lower == 0) {    //Checking if Password Satisfies Conditions or Not
		for (i = 0; i < length; i++) {
			if (password[i] >= 'a' && password[i] <= 'z')
				lower = 1;
			else if (password[i] >= 'A' && password[i] <= 'Z')
				upper = 1;
			else if (password[i] >= '0' && password[i] <= '9')
				num = 1;
			else sym = 1;
			if (i == length - 1) {
				if (num == 0 || upper == 0 || sym == 0 || lower == 0) {
					cout << endl << "Conditions for Password Unsatisfied." << endl;
					if (num == 0)
						cout << endl << "You Did Not Include Any Numbers." << endl;
					else if (sym == 0)
						cout << endl << "You Did Not Include Any Symbols." << endl;
					else if (lower == 0)
						cout << endl << "You Did Not Include Any Lowercase Letters." << endl;
					else if (upper == 0)
						cout << endl << "You Did Not Include Any Uppercase Letters." << endl;
					cout << endl << "Re-Enter a Password which Fulfills the Conditions:" << endl;
					mask(password);
					length = strlen(password);
				}
			}
		}
	}
}

//checking password length
void Account::checkLength() {
	int length;
	length = strlen(password);
	while (length < 8 || length>16) {   //If Password is Not in Range, Then Input Password Again
		if (length < 8) {
			cout << endl << "Password too Short!Re-Enter:" << endl;
			mask(password);
		}
		else if (length > 16) {
			cout << endl << "Password too Long!Re-Enter:" << endl;
			mask(password);
		}
		length = strlen(password);
	}
	//once length is appropriate, checking other conditions
	checkConditions(length);
}

//verification of password
void Account::verifyingPassword(bool& verified) {
	static int attempts = 0;
	char verify[17];
	cout << endl << "Kindly Re - Enter Your Password for Confirmation:";
	mask(verify);
	if (strcmp(verify, password) != 0) {   //If the 2 Passwords are Different
		while (strcmp(verify, password) != 0) {
			attempts++;
			if (attempts <= 3) {
				cout << endl << "The 2 Passwords Do Not Match! Kindly Re-Enter Your Password:";
				mask(verify);
			}
			else {
				cout << endl << "You were unable to verify password in 3 attempts.";
				cout << "Account locked. Try Again later!";
				cout << "Exiting application...";
				verified = false;
				exit(1);
			}
		}
	}
	else {
		if (strcmp(verify, password) == 0) {   //If the 2 Passwords are matching
			cout << endl << "Account Created Successfully!" << endl;
			verified = true;
		}
	}
}

//For Masking Password
void Account::mask(char* array) {
	char ch;
	int i = 0;
	while (1) {
		ch = _getch(); // Getch() Reads a Key From Keyboard Without Displaying it on Screen and Returns it's ASCII Value
		if (ch == 13) { // If Enter Key
			if (i == 0)
				cout << endl << "Password Cannot be Empty";
			break;
		}
		else if (ch == 32 || ch == 9) { // If Space or Tab Key
			continue;
		}
		else if (ch == 8) { // If Backspace
			if (i > 0) {
				i--;
				array[i] = '\0';
				cout << "\b \b";
			}
		}
		else {
			if (i < 16) {
				array[i] = ch;
				i++;
				cout << "*";
			}
		}
	}
	array[i] = '\0';
}

//Signing Up/Creating an Account:
bool Account::signup() {
	bool verified = false;
	inputForSignup();
	checkLength();
	verifyingPassword(verified);
	return verified;
}

void Account::login(Account accFile, bool& userFound) {
	static int attempts = 0;
	if (strcmp(accFile.username, username) == 0) {
		if (strcmp(accFile.password, password) == 0) {
			cout << endl << "Logged in successfully!" << endl;
		}
		else {
			cout << endl << "Incorrect password!";
			attempts++;
			if (attempts <= 3)
			{
				cout << endl << "Enter password:";
				mask(password);
				login(accFile, userFound);
			}
			else {
				cout << endl << "Incorrect password entered too many times...Account locked." << endl;
				cout << "Try again later! Exiting Program..." << endl;
				exit(1);
			}
		}
		userFound = true;
	}
}

// getters/accessors of attributes
// no accessor for password, as it must not be accessible
const char* Account::getEmail()const {
	return email;
}

const char* Account::getUsername()const {
	return username;
}

long long int Account::getContact()const {
	return contact;
}

// setter/mutator functions
//no mutator for password, as it must not be changed
void Account::setEmail(const char* e) {
	int i;
	for (i = 0; email[i] != '\0'; i++)
		email[i] = e[i];
	email[i] = '\0';
}

void Account::setUsername(const char* un) {
	int i;
	for (i = 0; email[i] != '\0'; i++)
		cout << email[i];
	email[i] = '\0';
}


void Account::setContact(const long long int c) {
	contact = c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Functions of class Person:

// getter/accessor functions

const char* Person::getFName()const {
	return fname;
}

const char* Person::getLName()const {
	return lname;
}

int Person::getAge()const {
	return age;
}

char Person::getGender()const {
	return gender;
}

int Person::getID()const {
	return id;
}

// setter/mutator functions

void Person::setFName(const char fn[20]) {
	int i;
	for (i = 0; fn[i] != '\0'; i++)
		fname[i] = fn[i];
	fname[i] = '\0';
}

void Person::setLName(const char ln[20]) {
	int i;
	for (i = 0; ln[i] != '\0'; i++)
		lname[i] = ln[i];
	lname[i] = '\0';
}

void Person::setGender(const char g) {
	gender = g;
}

void Person::setAge(const int a) {
	age = a;
}

void Person::setID(const int i) {
	id = i;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Functions of class Doctor

//getter/accessor
const char* Doctor::getSpecialist()const {
	return specialist;
}

int Doctor::getFirstStartingHour()const {
	return firstWorkHours[0];
}

int Doctor::getFirstEndingHour()const {
	return firstWorkHours[1];
}

int Doctor::getSecondStartingHour()const {
	return secondWorkHours[0];
}

int Doctor::getSecondEndingHour()const {
	return secondWorkHours[1];
}

float Doctor::getFees()const {
	return fees;
}

bool Doctor::getFirstAvailibility()const {
	return availability[0];
}

bool Doctor::getSecondAvailibility()const {
	return availability[1];
}

//setter/mutator
void Doctor::setSpecialist(const char* s) {
	int i;
	for (i = 0; s[i] != '\0'; i++)
		specialist[i] = s[i];
	specialist[i] = '\0';
}

void Doctor::setFirstStartingHour(const int sh) {
	firstWorkHours[0] = sh;
}

void Doctor::setFirstEndingHour(const int eh) {
	firstWorkHours[1] = eh;
}

void Doctor::setSecondStartingHour(const int sh) {
	secondWorkHours[0] = sh;
}

void Doctor::setSecondEndingHour(const int eh) {
	secondWorkHours[1] = eh;
}

void Doctor::setFees(const float f) {
	fees = f;
}

void Doctor::setFirstAvailibility(const bool a) {
	availability[0] = a;
}

void Doctor::setSecondAvailibility(const bool a) {
	availability[1] = a;
}

void Doctor::setBalance(const double b) {
	balance += b;
}

void Doctor::displayDetails()const {
	for (int i = 0; fname[i] != '\0'; i++)
		cout << fname[i];
	cout << " ";
	for (int i = 0; lname[i] != '\0'; i++)
		cout << lname[i];
	cout << "\t\t";
	for (int i = 0; specialist[i] != '\0'; i++)
		cout << specialist[i];
	cout << "\t\t";
	cout << firstWorkHours[0] << " to " << firstWorkHours[1] << " and ";
	cout << secondWorkHours[0] << " to " << secondWorkHours[1] << "\t\t";
	cout << fees << endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//getters/accessors
Account Patient::getAccount()const {
	return acc;
}
const char* Patient::getAccountEmail()const {
	return acc.getEmail();
}

long long int Patient::getAccountContact()const {
	return acc.getContact();
}

const char* Patient::getAccountUsername()const {
	return acc.getUsername();
}

//setter/mutator

void Patient::setAccountEmail(const char* e) {
	acc.setEmail(e);
}

void Patient::setAccountContact(const long long int c) {
	acc.setContact(c);
}


//Functions of class Patient

void Patient::input() {
	systemPause();
	system("CLS");
	cout << endl << "Enter Your First Name: ";
	cin >> fname;
	cout << "Enter Your Last Name: ";
	cin >> lname;
	cout << "Enter Your Gender (M/F): ";
	cin >> gender;
	while (gender != 'f' && gender != 'F' && gender != 'M' && gender != 'm') {
		cout << "Invali Gender! Kindly enter 'm' or 'f':";
		cin >> gender;
	}
	cout << "Enter Your Age: ";
	cin >> age;
	if (age < 0) {
		cout << "Age cannot be less than zero...Re-enter:";
		cin >> age;
	}
	cout << "Enter Your Balance: ";
	cin >> balance;
	id = randomize();
	cout << "ID assigned to you is " << id << "!" << endl;
}

int Patient::Patientmenu() {
	system("CLS");
	int option;
	cout << endl << "PLEASE TELL US HOW WE CAN HELP YOU??????" << endl << endl;
	cout << "Select What Do You  Want To Do (Choose the Respective Number of the Desired Function): " << endl;
	cout << "1. Blood Donation" << endl << "2. Medical Items Purchasing" << endl << "3. Appointment Booking " << endl;
	cout << "4. View Diet Plans" << endl;
	cin >> option;
	return option;
}

void Patient::inputreport() {
	system("CLS");
	cout << endl << "Now, the Doctor Requires Your Medical Report to Proceed Further!" << endl;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 6);
	cout << endl << "\t\t\t\t\t** MEDICAL REPORT **" << endl << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	int c1, c2, c3, c4, c5;

	cout << "Describe Your Problem (Enter the Correct Option Number): " << endl;
	cout << "1.Respiratory Problems" << endl
		<< "2.Dermatological Problems" << endl
		<< "3.Cardiological Problems" << endl
		<< "4.Digestive Problems" << endl
		<< "5.Dental Problems" << endl
		<< "6.ENT Problems" << endl;
	cin >> c1;
	system("CLS");
	cout << "Cause of Current Problem (Select the Respective Number of the Following Causes): " << endl
		<< "1.Car Accident" << endl
		<< "2.Work Injury" << endl
		<< "3.Other" << endl;
	cin >> c2;
	system("CLS");
	cout << "Past Medical History (Do you have a History of the Following Problems): " << endl;
	cout << "1.Breathing Problem" << endl
		<< "2.Skin Problem" << endl
		<< "3.Heart Problem" << endl
		<< "4.Kidney Problem" << endl
		<< "5.Stomach/Liver Problem" << endl
		<< "6.Hepatitis" << endl
		<< "7.Typhoid" << endl
		<< "8.Dengue" << endl
		<< "9.Malaria" << endl
		<< "10.ChickenPox" << endl
		<< "11.Jaundice" << endl
		<< "12.COVID-19" << endl
		<< "13.Other: " << endl;
	cin >> c3;
	system("CLS");
	cout << "Please Select Medications that you Have Been Taking Recently: " << endl;
	cout << "1.Homeopatheic" << endl
		<< "2.Inhalers" << endl
		<< "3.Tablets/Capsules" << endl
		<< "4.Injections" << endl
		<< "5.IV Infusions" << endl
		<< "6.Antibiotics" << endl
		<< "7.Other: " << endl;
	cin >> c4;
	system("CLS");
	cout << "If you have any Allergy, Please Select the Allergy From the List: " << endl;
	cout << "1.Dust" << endl
		<< "2.Food" << endl
		<< "3.Pollen" << endl
		<< "4.Environmental" << endl
		<< "5.Drug" << endl
		<< "6.Pet" << endl
		<< "7.Dairy Products" << endl
		<< "8.Other: " << endl;
	cin >> c5;
	system("CLS");
	writeReportFile(c1, c2, c3, c4, c5);
}

int Patient::chooseDoctor() {
	int choice;
	cout << "1-Dermatologist" << endl;
	cout << "2-Cardiologist" << endl;
	cout << "3-Gastroentrologist" << endl;
	cout << "4-ENT Specialist" << endl;
	cout << "5-Pulmonologist" << endl;
	cout << "6-Dentist" << endl;
	cin >> choice;
	return choice;
}

bool Patient::makeAppointment(Doctor d[12], Admin a, int chosenDoc[3]) {
	cout << endl << "Which doctor do you want to consult? Enter respective number:" << endl;
	int choice = chooseDoctor();
	chosenDoc[0] = choice;
	bool isFound = false;
	while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6) {
		cout << endl << "Kindly enter valid choice(a number from 1 to 6):" << endl;
		choice = chooseDoctor();
	}
	if (choice == 1) {
		char specialist[20] = "Dermatologist";
		return a.findDoctor(specialist, d, chosenDoc);
	}
	if (choice == 2) {
		char specialist[20] = "Cardiologist";
		return a.findDoctor(specialist, d, chosenDoc);
	}
	if (choice == 3) {
		char specialist[20] = "Gastroentrologist";
		return a.findDoctor(specialist, d, chosenDoc);
	}
	if (choice == 4) {
		char specialist[20] = "ENT Specialist";
		return a.findDoctor(specialist, d, chosenDoc);
	}
	if (choice == 5) {
		char specialist[20] = "Pulmonologist";
		return a.findDoctor(specialist, d, chosenDoc);
	}
	if (choice == 6) {
		char specialist[20] = "Dentist";
		return a.findDoctor(specialist, d, chosenDoc);
	}
}

bool Patient::checkValidity(double amount) {
	if (amount > balance)
		return false;
	else return true;
}

bool Patient::operator+(Doctor& d) {
	double transferAmount = d.getFees();
	bool check = checkValidity(transferAmount);
	if (check) {
		balance -= transferAmount;
		d.setBalance(transferAmount);
		cout << endl << "Balance succesfully transferred!" << endl;
		return true;
	}
	else {
		cout << endl << "Amount to be transferred exceeds balance...transfer insuccessful." << endl;
		return false;
	}
}

//function for displaying Patient's data
void Patient::displayDetails()const {
	cout << "First Name: ";
	for (int i = 0; i < strlen(fname); i++) {
		cout << fname[i];
	}
	cout << endl << "Last Name: ";
	for (int i = 0; i < strlen(lname); i++) {
		cout << lname[i];
	}
	cout << endl << "Gender: " << gender << endl << "Age: " << age << endl << "ID: " << id << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Functions of class BloodDonator
//Functions
int BloodDonator::BloodCollectionCheck(string bloodGroup, int noOfbottles, bool& validNoOfBottles, bool& isValidBloodGroup) {
	int indexOfBloodGroup;
	do {
		for (int i = 0; i < 8; i++) {
			if (bloodGroup == BGroups[i]) {
				isValidBloodGroup = true;
				indexOfBloodGroup = i;
				if (noOfbottles <= TB_Bottles[i]) {
					validNoOfBottles = true;
					TB_Bottles[i] -= noOfbottles; // decrement the number of bottles available
				}
				else {
					cout << "Number of Bottles for Blood Collection Exceeded the Limit...Blood Not Available " << endl;
					validNoOfBottles = false;
				}
				break; // exit the loop since we found a matching blood group
			}
		}
		if (!isValidBloodGroup) {
			cout << "Invalid Blood Group Type Entered... Please enter a valid blood group." << endl;
			cin >> bloodGroup;
		}
	} while (!isValidBloodGroup);
	return indexOfBloodGroup;
}


void BloodDonator::DecrementNoOfBottles(string bloodGroup, int noOfbottles) { //Decrementing if BloodCollectionCheck is True
	bool validNoOfBottles = false;
	bool isValidBloodGroup = false;
	int indexOfBloodGroup = BloodCollectionCheck(bloodGroup, noOfbottles, validNoOfBottles, isValidBloodGroup);
	if (validNoOfBottles && isValidBloodGroup)
		TB_Bottles[indexOfBloodGroup] = TB_Bottles[indexOfBloodGroup] - noOfbottles;

}

//function for displaying blood donator's data
void BloodDonator::displayDetails()const {
	cout << "Blood Groups Available: " << endl;
	for (int i = 0; i < 8; i++) {
		cout << BGroups[i] << endl;
		cout << "Total Bottles available for this Blood Group: " << TB_Bottles[i] << endl;
		cout << "----------------------------------------------------------------" << endl;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Functions of class Medicine
//getter

const char* Medicine::getName()const {
	return name;
}
const char* Medicine::getCategory()const {
	return category;
}
int Medicine::getStock()const {
	return stock;
}
double Medicine::getPrice()const {
	return price;
}

//setters
void Medicine::setName(const char* n) {
	int i;
	for (i = 0; n[i] != '\0'; i++)
		name[i] = n[i];
	name[i] = '\0';
}
void Medicine::setCategory(const char* c) {
	int i;
	for (i = 0; c[i] != '\0'; i++)
		category[i] = c[i];
	category[i] = '\0';
}
void Medicine::setStock(const int s) {
	stock = s;
}
void Medicine::setPrice(const double p) {
	price = p;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Functions of class Pharmacy
//getter

Medicine Pharmacy::getMedicine(int index)const {
	return m[index - 1];
}

//setter
void Pharmacy::setBalance(const double b) {
	balance += b;
}

//member function
void Pharmacy::displaymedicine() {

	cout << "NAME\t\tCATEGORY\tSTOCK\tPRICE" << endl;
	cout << "------------------------------------------------------------------" << endl;
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << ". ";
		for (int j = 0; j < strlen(m[i].name); j++) {
			cout << m[i].name[j];
		}
		cout << "\t";
		for (int j = 0; j < strlen(m[i].category); j++) {
			cout << m[i].category[j];
		}
		cout << "\t";
		cout << m[i].stock << "\t" << m[i].price << endl;
	}
}

void Pharmacy::decrementStock(int choice) {
	if (choice == 1)       m[0].stock -= 1;
	else if (choice == 2)  m[1].stock -= 1;
	else if (choice == 3)  m[2].stock -= 1;
	else if (choice == 4)  m[3].stock -= 1;
	else if (choice == 5)  m[4].stock -= 1;
	else if (choice == 6)  m[5].stock -= 1;
	else if (choice == 7)  m[6].stock -= 1;
	else if (choice == 8)  m[7].stock -= 1;
	else if (choice == 9)  m[8].stock -= 1;
	else if (choice == 10) m[9].stock -= 1;

	cout << "Medicine Purchased Successfully !!!" << endl;

	//Writing the Updated file
	ofstream fout;
	fout.open("Med.bin", ios::binary);
	if (!fout)
		cout << "Error!";
	else {
		fout.write(reinterpret_cast <char*> (&m), sizeof(m));
	}
	fout.close();
}

void Pharmacy::incrementStock(int choice) {
	if (choice == 1)       m[0].stock += 1;
	else if (choice == 2)  m[1].stock += 1;
	else if (choice == 3)  m[2].stock += 1;
	else if (choice == 4)  m[3].stock += 1;
	else if (choice == 5)  m[4].stock += 1;
	else if (choice == 6)  m[5].stock += 1;
	else if (choice == 7)  m[6].stock += 1;
	else if (choice == 8)  m[7].stock += 1;
	else if (choice == 9)  m[8].stock += 1;
	else if (choice == 10) m[9].stock += 1;

	//Writing the Updated file
	ofstream fout;
	fout.open("Med.bin", ios::binary);
	if (!fout)
		cout << "Error!";
	else {
		fout.write(reinterpret_cast <char*> (&m), sizeof(m));
	}
	fout.close();

}

int Pharmacy::purchasingMed() {
	readMedicineFile();

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 11);
	system("CLS");
	displaymedicine();
	int choice;
	cout << endl << "Which medicine you want to buy (Enter the respective number of your choice)?" << endl;
	cin >> choice;
	decrementStock(choice);
	return choice;
}


void Pharmacy::readMedicineFile() {
	ifstream fin;
	fin.open("Med.bin");
	if (!fin)
		cout << "error!";
	else
		fin.read(reinterpret_cast <char*> (&m), sizeof(m));
	fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Functions of class Admin

bool Admin::findDoctor(char specialization[20], Doctor doctorsList[2], int chosenDoc[3]) {
	Doctor requiredDoctor[2];   //at most there are 2 doctors for each specialization 
	int choice, j = 0;
	bool available;
	system("CLS");
	cout << endl << "Doctors with your requested specialization are:" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl << "NUMBER\tNAME\t\t\tSPECIALIZATION\t\tWORKING HOURS\t\t\t\tFEES" << endl;
	for (int i = 0; i < 12; i++) {
		if (strcmp(specialization, doctorsList[i].getSpecialist()) == 0) {
			cout << j + 1 << "\t";
			requiredDoctor[j] = doctorsList[i];
			requiredDoctor[j].displayDetails();
			j++;
		}
	}
	cout << endl << "Enter number of your choice:";
	cin >> choice;
	while (choice != 1 && choice != 2) {
		cout << endl << "Kindly enter valid choice(1 or 2):" << endl;
		cin >> choice;
	}
	if (choice == 1)
		available = scheduleAppointment(requiredDoctor, 1, chosenDoc);
	else if (choice == 2)
		available = scheduleAppointment(requiredDoctor, 2, chosenDoc);
	return available;
}

bool Admin::checkAvailability(Doctor d, char time) {
	if (time == 'f') {
		if (d.availability[0])
			return true;
		else return false;
	}
	else {
		if (d.availability[1])
			return true;
		else return false;
	}
}

bool Admin::scheduleAppointment(Doctor requiredDoctor[2], int choice, int chosenDoc[3]) {
	static int count; //this variable is to check that the availibility of each doctor is checked once, not repeatedly
	bool available;
	available = checkAvailability(requiredDoctor[choice - 1], 'f');
	if (!available) {
		cout << endl << "Doctor is unavailable in first slot... checking second slot!" << endl;
		available = checkAvailability(requiredDoctor[choice - 1], 's');
		if (available) {
			cout << endl << "Doctor was available in second slot!" << endl;
			cout << endl << "Appointment Scheduled!" << endl;
			requiredDoctor[choice - 1].availability[1] = false;
			chosenDoc[2] = 1;
			//now, doctor has an appointment is this slot and will
			//be unavailable for other patients.
		}
	}
	else {
		cout << "Appointment Scheduled in first slot!" << endl;
		requiredDoctor[choice - 1].availability[0] = false;
		chosenDoc[2] = 0;
	}
	if (!available) {
		count++;
		char option;
		cout << "Appointment could not be scheduled!" << endl;
		if (count == 1) {
			cout << "Do you want to schedule appointment with the other doctor ? y / n : " << endl;
			cin >> option;
			while (option != 'y' && option != 'Y' && option != 'n' && option != 'N') {
				cout << endl << "Kindly enter valid choice(y-yes, n-no):" << endl;
				cin >> option;
			}
			if (option == 'y' || option == 'Y') {
				cout << endl << "Checking doctor availibility..." << endl;
				if (choice == 1)
					scheduleAppointment(requiredDoctor, 2, chosenDoc);
				else if (choice == 2)
					scheduleAppointment(requiredDoctor, 1, chosenDoc);
			}
		}
		else if (count == 2) {
			cout << endl << "Both doctors are unavailable!" << endl;
		}
	}
	chosenDoc[1] = choice;
	systemPause();
	return available;
}

void Admin::patientBilling(Patient& p, Doctor& d, int time) {
	bool transferSuccess = p + d;    //transfer money
	if (!transferSuccess) {
		//if money cannot be transferred, appointmwnt is cancelled, and doctor is again available at that time
		cout << endl << "Appointment cancelled!" << endl;
		if (time == 0)
			d.setFirstAvailibility(true);
		else d.setSecondAvailibility(true);
	}
}

void Admin::medicineBilling(Patient& p, Pharmacy& ph, int medN) {
	Medicine m = ph.getMedicine(medN);
	double transferAmount = m.getPrice();
	bool check = p.checkValidity(transferAmount);
	if (check) {
		p.balance -= transferAmount;
		ph.setBalance(transferAmount);
		cout << endl << "Balance succesfully transferred!" << endl;
	}
	else {
		cout << endl << "Amount to be transferred exceeds balance...transfer insuccessful." << endl;
		//if money cannot be transferred, medicine is not purchased
		cout << endl << "Medicine could not be purchased!" << endl;
		ph.incrementStock(medN);
	}
}

void Admin::acceptDonation(BloodDonator& b1) {
	system("CLS");
	b1.displayDetails();
	systemPause();
	string bloodGroup = BloodGroupInput();
	int nOfBottles = BloodGroupBottlesInput();
	b1.DecrementNoOfBottles(bloodGroup, nOfBottles);
	cout << "Blood Donation Successful!" << endl;
}

void Admin::displayDietPlanDetails(DietPlan d[7], string diseaseName) {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 10);
	cout << endl << endl << "\t***7 DAYS DIET PLAN FOR " << diseaseName << "***";
	cout << endl << "________________________________________________________________________________________________________________________" << endl;
	cout << "DAY\t|TIME\t\t|FOOD";
	cout << endl << "________________________________________________________________________________________________________________________" << endl;
	for (int i = 0; i < 7; i++) {
		d[i].displayDetails();
	}

}

void Admin::createAccount(Patient& p) {
	cout << endl << "Creating a new account for user..." << endl;
	cout << "----------------------------------------------------" << endl;
	bool verification = p.acc.signup();
	if (verification) {
		writeAccountFile(p.acc);
	}
}

void Admin::loginToAccount(Patient& p) {
	bool userFound = false;
	cout << endl << "Logging in..." << endl;
	p.acc.inputForLogin();
	//creating an account that stores data from file
	Account accFile;
	readAccountFile(accFile, p.acc, userFound);
	if (!userFound) {
		cout << endl << "User not found!";
		createAccount(p);
	}
	else {
		p.acc = accFile;
	}
}

//function for displaying Admin's data
void Admin::displayDetails()const {
	cout << "First Name: ";
	for (int i = 0; fname[i] != '\0'; i++)
		cout << fname[i];
	cout << endl << "Last Name: ";
	for (int i = 0; lname[i] != '\0'; i++)
		cout << lname[i];
	cout << endl << "Gender: ";
	if (gender == 'f' || gender == 'F')
		cout << "Female";
	else cout << "Male";
	cout << endl << "Age: " << age;
	cout << endl << "ID: " << id << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Functions of class DietPlan

void DietPlan::displayDetails() {
	//printing day
	for (int i = 0; day[i] != '\0'; i++)
		cout << day[i];
	//printing all three times and respective foods of the day
	for (int i = 0; i < 3; i++) {
		cout << "\t|";
		for (int j = 0; time[i][j] != '\0'; j++)
			cout << time[i][j];
		if (i != 0)
			cout << "\t\t|";
		else cout << "\t|";
		for (int j = 0; food[i][j] != '\0'; j++)
			cout << food[i][j];
		cout << endl;
	}
	cout << "________________________________________________________________________________________________________________________" << endl;

}


//global functions
void readDoctorFile(Doctor(&d)[12]) {
	ifstream fin;
	fin.open("doc.bin");
	if (!fin)
		cout << "error!";
	else fin.read(reinterpret_cast <char*> (&d), sizeof(d));
	fin.close();
}

void writeDoctorFile(Doctor(&d)[12]) {
	ofstream fout;
	fout.open("doc.bin", ios::binary);
	if (!fout)
		cout << "Error!";
	else {
		fout.write(reinterpret_cast <char*> (&d), sizeof(d));
	}
	fout.close();
}

void readAdminFile(Admin& a) {
	ifstream fin;
	fin.open("admin.bin");
	if (!fin)
		cout << "error!";
	else fin.read(reinterpret_cast <char*> (&a), sizeof(a));
	fin.close();
}

void readDietPlan(DietPlan(&d)[7], string fileName) {
	ifstream fin;
	fin.open(fileName);
	if (!fin)
		cout << "error!";
	else
		fin.read(reinterpret_cast <char*> (&d), sizeof(d));
	fin.close();
}

//Report File Created
void writeReportFile(int c1, int c2, int c3, int c4, int c5) {
	fstream fout;
	fout.open("ReportPatient.txt", ios::out);

	if (!fout) {
		cout << "File can not Open!!!" << endl;
	}
	else {
		fout << "Patient Report: " << endl;
		fout << "Problem (Option No): " << c1 << endl;
		fout << "Cause of Problem (Option No): " << c2 << endl;
		fout << "Past Medical History (Option No): " << c3 << endl;
		fout << "Medications Currently in Use (Option No): " << c4 << endl;
		fout << "Allergy (Option No): " << c5 << endl;
	}
	fout.close();
}

//To Read Report File
void readReportFile() {
	fstream fin;
	fin.open("ReportPatient.txt");
	if (!fin) {
		cout << "error!";
	}
	else {
		int ans1, ans2, ans3, ans4, ans5;
		while (!fin.eof()) {
			fin >> ans1;
			cout << "Problem (Option No): " << ans1 << endl;
			fin >> ans2;
			cout << "Cause of Problem (Option No): " << ans2 << endl;
			fin >> ans3;
			cout << "Past Medical History (Option No): " << ans3 << endl;
			fin >> ans4;
			cout << "Medications Currently in Use (Option No): " << ans4 << endl;
			fin >> ans5;
			cout << "Allergy (Option No): " << ans5 << endl;
		}
	}
	fin.close();
}

//write account file
void writeAccountFile(Account& a) {
	ofstream fout;
	fout.open("accounts.txt", ios::binary | ios::app);
	if (!fout)
		cout << "error!";
	else {
		fout.write(reinterpret_cast <char*> (&a), sizeof(a));
	}
	fout.close();
}

//read account file
void readAccountFile(Account& accFile, Account& a, bool& userFound) {
	ifstream fin;
	fin.open("accounts.txt");
	if (!fin)
		cout << "error!";
	else {
		while (!fin.eof() && userFound != true) {
			fin.read(reinterpret_cast <char*> (&accFile), sizeof(accFile));
			a.login(accFile, userFound);
		}
	}
	fin.close();
}

int randomize() {
	return rand() % 1000;
}

string BloodGroupInput() {
	string bloodGroup;

	cout << "Enter the Blood Group: " << endl;
	cin >> bloodGroup;

	return bloodGroup;
}

int BloodGroupBottlesInput() {
	int bottles;

	cout << "Enter the Number of Bottles you want to purchase of this Blood Group: " << endl;
	cin >> bottles;

	return bottles;
}

char chooseReviewType() {
	char choice;
	cout << endl << "Do you want to give textual feedback? Or do you want to rate out of 5 stars?" << endl;
	cout << "Enter 't' for text, 's' for stars:";
	cin >> choice;
	while (choice != 't' && choice != 'T' && choice != 'S' && choice != 's') {
		cout << "Kindly enter a valid choice :";
		cin >> choice;
	}
	return choice;
}

void Feedback() {
	char giveFeedback;
	giveFeedback = askForFeedback();
	if (giveFeedback == 'y' || giveFeedback == 'Y') {
		char option = chooseReviewType();
		if (option == 't' || option == 'T') {
			string rating = giveRating<string>();
			cout << "Thank You for giving us your valuable Feedback !" << endl << endl;
		}
		if (option == 's' || option == 's') {
			int rating = giveRating<int>();
			cout << "Thank You for giving us your valuable Feedback !" << endl << endl;
		}
	}
}

char askForFeedback() {
	system("CLS");
	char giveFeedback;
	cout << endl << "Do you want to leave a review for this application? y/n:";
	cin >> giveFeedback;
	while (giveFeedback != 'n' && giveFeedback != 'N' && giveFeedback != 'Y' && giveFeedback != 'y') {
		cout << "Kindly enter y for yes and n for no! :";
		cin >> giveFeedback;
	}
	return giveFeedback;
}

template <typename T>
T giveRating() {
	T rating;
	cout << "---------------------------------------" << endl;
	cout << endl << "Give rating:";
	cin >> rating;
	return rating;
}

int dietPlanMenu() {
	int option;
	cout << endl << "We have Diet Plans for 3 diseases:" << endl;
	cout << "1. Covid" << endl;
	cout << "2. Diabetes" << endl;
	cout << "3. Dengue" << endl;
	cout << "Which diet plan do you want to view? Enter number of your choice:";
	cin >> option;
	return option;
}

void menu(Admin& a, Patient& p, Doctor(&d)[12], BloodDonator& b, Pharmacy& ph) {
	systemPause();
	//providing patient with menu
	int choice = p.Patientmenu();
	if (choice == 1) {
		a.acceptDonation(b);
	}
	else if (choice == 2) {
		char option = 'y';
		while (option == 'y' || option == 'Y') {
			int choice = ph.purchasingMed();
			a.medicineBilling(p, ph, choice);
			cout << "Do you want to buy more medicines (Enter (y/Y) for YES and (n/N) for NO)?";
			cin >> option;
		}
	}
	else if (choice == 3) {
		int chosenDoc[3];
		//the first index selects specialization, and second selects one doctor in the 2 specializations
		//the third index indicates which time of doctor was selected

		/* Note: The doctors list is arranged in a way that 2 doctors with the same specialization WILL be
		   placed consecutively. Additionally, the order in whcih specialization is fixed-therefore by the 2 numbers
		   stored in "chosenDoc" array, we can determine the doctor chosen by the patient, by the following eq
		   chosenDoc[0] - 2 chosenDoc[1] */
		bool isFound = p.makeAppointment(d, a, chosenDoc);
		if (isFound) {
			//if appointment is successful, then billing
			int option = chosenDoc[0] - 2 + chosenDoc[1];
			a.patientBilling(p, d[option], chosenDoc[2]);
			p.inputreport();
		}
	}
	else if (choice == 4) {
		int option = dietPlanMenu();
		if (option == 1) {
			DietPlan covid[7];
			readDietPlan(covid, "covidDietPlan.bin");
			a.displayDietPlanDetails(covid, "COVID");
		}
		else if (option == 2) {
			DietPlan diabetes[7];
			readDietPlan(diabetes, "diabetesDietPlan.bin");
			a.displayDietPlanDetails(diabetes, "DIABETES");
		}
		else if (option == 3) {
			DietPlan dengue[7];
			readDietPlan(dengue, "dengueDietPlan.bin");
			a.displayDietPlanDetails(dengue, "DENGUE");
		}
	}
	char exitMenu;
	cout << endl << "Do you want to do anything else? Enter 'y' for yes and 'n' for no:";
	cin >> exitMenu;
	while (exitMenu != 'y' && exitMenu != 'Y' && exitMenu != 'n' && exitMenu != 'N') {
		cout << "Invalid choice. Enter 'y' or 'n': ";
		cin >> exitMenu;
	}
	if (exitMenu == 'y' || exitMenu == 'Y')
		menu(a, p, d, b, ph);
	else return;
}

void signUpOrLogin(Admin& a, Patient& p) {
	char choice;
	cout << "Do you want to Signup (Enter 's') Or Login (Enter 'l'):";
	cin >> choice;
	if (choice == 's' || choice == 'S')
		a.createAccount(p);
	else if (choice == 'l' || choice == 'L')
		a.loginToAccount(p);
}

void welcomeUser() {
	cout << "\t\t\t\t************************ WELCOME TO OUR HEALTH APPLICATION ******************************" << endl << endl;
}

void thankUser() {
	cout << endl << endl << "\t\t\t\t\t***** THANK YOU FOR USING THIS APPLICATION *****" << endl;
}

void systemPause() {
	cout << endl;
	system("pause");
	cout << endl;
}

int main() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 1);
	welcomeUser();
	//creating objects
	// data of doctor, admin, pharmacy and medicines is read from file
	//admin
	Admin a;
	readAdminFile(a);
	//doctor
	Doctor d[12];
	readDoctorFile(d);
	//patient
	Patient p;
	SetConsoleTextAttribute(h, 2);
	signUpOrLogin(a, p);
	SetConsoleTextAttribute(h, 3);
	p.input();
	//pharmacy
	Pharmacy ph;
	//Blood Donator 
	BloodDonator b;

	//calling menu
	SetConsoleTextAttribute(h, 13);
	menu(a, p, d, b, ph);

	//ask user for feedback of application
	SetConsoleTextAttribute(h, 5);
	Feedback();
	SetConsoleTextAttribute(h, 6);
	thankUser();
	//writing data to files as there have been updations
	writeDoctorFile(d);
}