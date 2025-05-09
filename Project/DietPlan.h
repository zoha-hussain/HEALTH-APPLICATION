#pragma once
#include <iostream>
using namespace std;

class DietPlan {
private:
	//attributes
	char day[15];
	char time[3][15];
	char food[3][100];
public:
	DietPlan() {};
	DietPlan(char day[15], char food[3][100]) {
		int j;
		for (j = 0; day[j] != '\0'; j++)
			this->day[j] = day[j];
		this->day[j] = '\0';
		strcpy_s(time[0], "BreakFast");
		strcpy_s(time[1], "Lunch");
		strcpy_s(time[2], "Dinner");
		for (int i = 0; i < 7; i++) {
			for (j = 0; food[i][j] != '\0'; j++)
				this->food[i][j] = food[i][j];
			this->food[i][j] = '\0';
		}
	}
	//function for displaying Diet Plan Details
	void displayDetails();
};
