#include "menus.h"
using namespace std;

string maskPassword()
{
	string password;
	char c;

	DWORD con_mode;
	DWORD dwRead;

	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hIn, &con_mode);
	SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	while (ReadConsoleA(hIn, &c, 1, &dwRead, NULL) && c != '\r')
	{
		if (c == '\b')
		{
			if (password.length() != 0)
			{
				cout << "\b \b";
				password.resize(password.length() - 1);
			}
		}
		else
		{
			password += c;
			cout << '*';
		}
	}
	cout << '\n';
	return password;
}

void showMenu(string menuList, string title, string chosenList)
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
	cout << chosenList << endl;
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
	showMenu(menuList, "", "");
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
	showMenu(menuList, title, "");
	return getInt(min, max);
}

int getMenu(string menuList, string title, string chosenList)
{
	//system("CLS");
	int min = 1, max = 1;
	for (size_t i = 0; i < menuList.length(); i++)
		if (menuList[i] == ',')
			max++;
	title += '\n';
	showMenu(menuList, title, chosenList);
	return getInt(min, max);
}