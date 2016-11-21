#pragma once

#include <ctime>
#include <string>

using namespace std;

class Date {
	int day;
	int month;
	int year;
public:
	Date();
	Date(int i) { day = 0; month = 0; year = 0; };
	~Date();
	string getDate() const;
	bool operator<(Date that);
	bool isLeap();
	int daysInMonth();
	bool dateValidate();
};