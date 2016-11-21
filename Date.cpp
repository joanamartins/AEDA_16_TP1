#include <iostream>
#include <iomanip>
#include "Date.h"

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

Date::~Date()
{
	//
}

string Date::getDate() const
{
	return to_string(day) + '/' + to_string(month) + '/' + to_string(year);
}

bool Date::operator<(Date that)
{
	return ((this->day + this->month * 100 + this->year * 10000) < (that.day + that.month * 100 + that.year * 10000));
}

bool Date::isLeap()
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int Date::daysInMonth()
{
	switch (month)
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
	if ((day < 1 || day > daysInMonth()) && (daysInMonth() != 0 || day > 31 || day < 0))
	{
		valid = false;
		cout << "Day out of range\n";
	}
	if (month < 1 || month > 12)
	{
		valid = false;
		cout << "Month out of range\n";
	}
	if (!valid)
		system("PAUSE");
	return valid;
}