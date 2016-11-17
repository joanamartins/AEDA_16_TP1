#pragma once

#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include "Date.h"
#include "Utils.h"

using namespace std;

string maskPassword();
void showMenu(string menuList, string title, string chosenList);
int getInt(int min, int max);
int getMenu(string menuList);
int getMenu(string menuList, string title);
int getMenu(string menuList, string title, string chosenList);
