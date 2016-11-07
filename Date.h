#pragma once

#include <ctime>
#include <string>

#define minYear 1970

using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(int day, int month, int year);
	Date(string &line);
	~Date();
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	friend bool operator==(Date d1, Date d2);
	friend bool operator>=(Date d1, Date d2);
	friend bool operator<=(Date d1, Date d2);
	friend bool operator<(Date d1, Date d2);
	friend ostream& operator<<(ostream& out, Date d1);
	bool isLeap();
	int daysInMonth();
	bool dateValidate();
};

void timeToString(time_t t);