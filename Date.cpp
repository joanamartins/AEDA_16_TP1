#include <iostream>
#include <iomanip>
#include "Date.h"

//constructors-------------------------------------------------------------------------

Date::Date()
{
	time_t t;
	struct tm  date;
	time(&t);
	localtime_s(&date, &t);

	day = date.tm_mday;
	month = date.tm_mon + 1;
	year = date.tm_year + 1900;
}

Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

Date::Date(string &line)
{
	string stmp = line;
	line = stmp;
	line.erase(line.begin() + line.find('/'), line.end());
	day = stoi(line);

	line = stmp;
	line.erase(line.begin(), line.begin() + line.find('/') + 1);
	line.erase(line.begin() + line.find('/'), line.end());
	month = stoi(line);

	line = stmp;
	line.erase(line.begin(), line.begin() + line.find('/') + 1);
	line.erase(line.begin(), line.begin() + line.find('/') + 1);
	year = stoi(line);

	if (year < minYear - 1900)
		year += 2000;
	else if (year < 100)
		year += 1900;
}

Date::~Date()
{
	//
}

//get----------------------------------------------------------------------------------

int Date::getDay() const
{
	return day;
}

int Date::getMonth() const
{
	return month;
}

int Date::getYear() const
{
	return year;
}

//set----------------------------------------------------------------------------------

void Date::setDay(int day)
{
	this->day = day;
}

void Date::setMonth(int month)
{
	this->month = month;
}

void Date::setYear(int year)
{
	this->year = year;
}

//operators-and-comparators------------------------------------------------------------

bool operator==(Date d1, Date d2)
{
	return (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day);
}
bool operator>=(Date d1, Date d2)
{
	return ((d1.day + d1.month * 100 + d1.year * 10000) >= (d2.day + d2.month * 100 + d2.year * 10000));
}
bool operator<=(Date d1, Date d2)
{
	return ((d1.day + d1.month * 100 + d1.year * 10000) <= (d2.day + d2.month * 100 + d2.year * 10000));
}
bool operator<(Date d1, Date d2)
{
	return ((d1.day + d1.month * 100 + d1.year * 10000) < (d2.day + d2.month * 100 + d2.year * 10000));
}

ostream& operator<<(ostream& out, Date d1)
{
	return out << right << setw(2) << setfill('0') << d1.day << '/' << setw(2) << setfill('0') << d1.month << '/' << setw(4) << setfill('0') << d1.year << setfill(' ');
}

//-------------------------------------------------------------------------------------

bool Date::isLeap()
{
	return getYear() % 4 == 0 && getYear() % 100 != 0 || getYear() % 400 == 0;
}

int Date::daysInMonth()
{
	switch (getMonth())
	{
	case 1:
		return 31;
	case 2:
		if (isLeap())
			return 29;
		else
			return 28;
	case 3:
		return 31;
	case 4:
		return 30;
	case 5:
		return 31;
	case 6:
		return 30;
	case 7:
		return 31;
	case 8:
		return 31;
	case 9:
		return 30;
	case 10:
		return 31;
	case 11:
		return 30;
	case 12:
		return 31;
	default:
		return 0;
	}
}

bool Date::dateValidate()
{
	bool valid = true;
	if ((getDay() < 1 || getDay() > daysInMonth()) && (daysInMonth() != 0 || getDay() > 31 || getDay() < 0))
	{
		valid = false;
		cout << "Day out of range\n";
	}
	if (getMonth() < 1 || getMonth() > 12)
	{
		valid = false;
		cout << "Month out of range\n";
	}
	if (getYear() < minYear || getYear() >(minYear + 1000))
	{
		valid = false;
		cout << "Year out of range (" << minYear << ", " << minYear + 1000 << ")\n";
	}
	if (!valid)
		system("pause");
	return valid;
}

//-------------------------------------------------------------------------------------

void timeToString(time_t t)
{
	cout << setw(2) << setfill('0') << (t / 3600) % 24 << ':' << setw(2) << setfill('0') << (t / 60) % 60 << setfill(' ');
	cout << endl;
}