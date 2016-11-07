#include <iostream>
#include <iomanip>
#include "Date.h"
#include "Utils.h"
using namespace std;

void showMenu(string menuList)
{
	Date now;
	timeToString(time(0));
	for (int i = 0; i < separatorLength; i++)
		cout << separatorChar;
	cout << endl;
	int optionNum = 1;
	size_t findPos = menuList.find(',', 0);
	while (findPos != string::npos) {
		cout << optionNum << ". " << menuList.substr(0, findPos) << endl;
		menuList = menuList.substr(findPos + 1, 1000);
		findPos = menuList.find(',', 0);
		optionNum++;
	}
	cout << optionNum << ". " << menuList << endl;
	for (int i = 0; i < separatorLength; i++)
		cout << separatorChar;
	cout << endl;
}

int getInt(int min, int max)
{
	int ret = min;
	do {
		if (cin.fail() || ret < min || ret > max)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl << "[ERROR] Invalid number!";
		}
		cout << " > ";
	} while (!(cin >> ret) || ret < min || ret > max);
	cout << endl;
	return ret;
}

int getMenu(string menuList, int min, int max)
{
	system("CLS");
	showMenu(menuList);
	return getInt(min, max);
}