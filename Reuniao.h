#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Date.h"
#include "Menus.h"

using namespace std;

extern vector<Curso *> feup;

class Reuniao {
	Date data;
	string studentID;
	//agenda???
	string descritivo;
public:
	Reuniao();
	Reuniao(Date d, string s, string desc);
	~Reuniao();
	Date getDate() const;
	string getStudent() const;
	string getDesc() const;
	void setDate(Date d);
	void setStu(string s);
	void setDesc(string desc);
	bool operator<(const Reuniao &that) const;
	bool operator==(const Reuniao &that) const;
};

ostream& operator<<(ostream& out, const Reuniao &r);