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

Date::Date(string &line)
{
	string stmp = line;
	int count = 0;
	while (count != 2)
	{
		for (size_t i = 0; i < line.length(); i++)
		{
			if (line[i] == '/')
				count++;
			else if (line[i] < 48 || line[i] > 57)
			{
				count = 0;
				cout << "Insira apenas numeros e barras (dd/mm/aa)\n";
				break;
			}
		}

		if (count == 2)
		{
			stmp = line;
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

			if (year < 70)
				year += 2000;
			else if (year < 100)
				year += 1900;
			if (!(dateValidate()))
				count = 0;
		}
		else
		{
			cout << "Data invalida\n\t>";
			cin.ignore();
			getline(cin, line);
			count = 0;
			stmp = line;
		}
	}
}

Date::~Date()
{
	//
}

string Date::getDate() const
{
	stringstream ss;
	if (day < 10)
		ss << '0';
	ss << to_string(day) << '/';
	if (month < 10)
		ss << '0';
	ss << to_string(month) << '/' << to_string(year);
	return ss.str();
}

bool Date::operator<(Date that) const
{
	return ((this->day + this->month * 100 + this->year * 10000) < (that.day + that.month * 100 + that.year * 10000));
}

bool Date::operator==(Date that) const
{
	return (this->day == that.day && this->month == that.month && this->year == that.year);
}

bool Date::dateValidate()
{
	bool valid = true;
	if ((day < 1 || day > daysInMonth(month, year)) && (daysInMonth(month, year) != 0 || day > 31 || day < 0))
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


bool isLeap(int year)
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int daysInMonth(int month, int year)
{
	switch (month)
	{
	case 1:
		return 31;
	case 2:
		if (isLeap(year))
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