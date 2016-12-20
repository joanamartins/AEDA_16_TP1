#pragma once

#include <ctime>
#include <string>
#include <sstream>

using namespace std;

class Date {
	int day;
	int month;
	int year;
public:
	Date();
	Date(int i) { day = 0; month = 0; year = 0; };
	Date(int d, int m, int y) { day = d; month = m; year = y; };
	Date(string &line);
	~Date();
	string getDate() const;
	int getDay() const { return day; };
	int getMonth() const { return month; };
	int getYear() const { return year; };
	bool operator<(Date that) const;
	bool operator==(Date that) const;
	bool dateValidate();
};

bool isLeap(int year);
int daysInMonth(int month, int year);