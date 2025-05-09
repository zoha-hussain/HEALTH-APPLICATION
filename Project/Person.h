#pragma once
#include <iostream>
#include <string>
#include "Account.h"
using namespace std;

class Person {
protected:
	//attributes
	char fname[20];
	char lname[20];
	char gender;
	int age;
	int id;

	//getters/accessors
	const char* getFName()const;
	const char* getLName()const;
	int getAge()const;
	char getGender()const;
	int getID()const;
	// setters/mutators
	void setFName(const char*);
	void setLName(const char*);
	void setGender(char);
	void setAge(int);
	void setID(int);
public:
	//default constructor
	Person() {
		age = 0;
	}
	// parameterized constructor
	Person(char fn[20], char ln[20], char g, int a, int id) {
		int i;
		for (i = 0; fn[i] != '\0'; i++)
			fname[i] = fn[i];
		fname[i] = '\0';
		for (i = 0; ln[i] != '\0'; i++)
			lname[i] = ln[i];
		lname[i] = '\0';
		age = a;
		gender = g;
		this->id = id;
	}
	//pure virtual function
	//function to display details of objects
	virtual void displayDetails()const = 0;
};