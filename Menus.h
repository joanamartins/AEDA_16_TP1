#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

void showMenu(string menuList);
int getInt(int min, int max);
int getMenu(string menuList, int min, int max);