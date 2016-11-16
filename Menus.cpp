#include <iostream>
#include <iomanip>
#include "Date.h"
#include "Utils.h"
using namespace std;

void showMenu(string menuList, string title)
{
	Date now;
	timeToString(time(0));
	for (int i = 0; i < separatorLength; i++)
		cout << separatorChar;
	cout << endl;
	cout << title;
	int optionNum = 1;
	size_t findPos = menuList.find(',', 0);
	while (findPos != string::npos) {
		cout << optionNum << ". " << menuList.substr(0, findPos) << endl;
		menuList = menuList.substr(findPos + 1, 5000);
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

int getMenu(string menuList)
{
	//system("CLS");
	int min = 1, max = 1;
	for (size_t i = 0; i < menuList.length(); i++)
		if (menuList[i] == ',')
			max++;
	showMenu(menuList, "");
	return getInt(min, max);
}

int getMenu(string menuList, string title)
{
	//system("CLS");
	int min = 1, max = 1;
	for (size_t i = 0; i < menuList.length(); i++)
		if (menuList[i] == ',')
			max++;
	title += '\n';
	showMenu(menuList, title);
	return getInt(min, max);
}