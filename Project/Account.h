#pragma once
#include <iostream>
#include <string>
using namespace std;

class Account {
private:

	//attributes
	char email[20];
	char username[20];
	long long int contact;
	char password[20];

public:
	//default constructor
	Account() {
		contact = 0;
	}
	//parameterized constructor
	Account(char e[20], char un[20], long long int c, char p[20]) {
		int i;
		for (i = 0; e[i] != '\0'; i++)
			email[i] = e[i];
		email[i] = '\0';
		for (i = 0; un[i] != '\0'; i++)
			username[i] = un[i];
		username[i] = '\0';
		for (i = 0; p[i] != '\0'; i++)
			password[i] = p[i];
		password[i] = '\0';
		contact = c;
	}
	//member functions
	void inputForSignup();
	void inputForLogin();
	void checkConditions(int);
	void checkLength();
	void verifyingPassword(bool&);
	void mask(char*);
	bool signup();
	void login(Account, bool&);
	void writeData();

	//accessors/getters
	const char* getEmail()const;
	const char* getUsername()const;
	long long int getContact()const;

	// setter/mutator functions
	void setEmail(const char* e);
	void setUsername(const char* un);
	void setContact(const long long int c);

};