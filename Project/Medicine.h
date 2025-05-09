#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Person.h"
#include "Account.h"
#include "AdminH.h"
#include "Pharmacy.h"
using namespace std;

class Medicine {
public:
	char name[20];
	char category[20];
	int stock;
	double price;

	Medicine() {}
	Medicine(char n[20], char c[20], int stock, double price) {
		int i;
		for (i = 0; n[i] != '\0'; i++)
			name[i] = n[i];
		name[i] = '\0';
		for (i = 0; c[i] != '\0'; i++)
			category[i] = c[i];
		category[i] = '\0';
		this->stock = stock;
		this->price = price;
	}
	//getters
	const char* getName()const;
	const char* getCategory()const;
	int getStock()const;
	double getPrice()const;
	//setters
	void setName(const char* n);
	void setCategory(const char* c);
	void setStock(const int s);
	void setPrice(const double p);

};