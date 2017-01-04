#pragma once

#include <vector>
#include <iostream>
#include "Ucurricular.h"

using namespace std;

class Turma {
	int id;
	int vagasMin;
	vector<pair<string,int>> vagas;
public:
	Turma() { id = idg; vagasMin = 100; idg++; };
	Turma(vector<pair<string, int>> vac) : vagas(vac) { id = idg; idg++; };
	static int idg;
	int getID() const { return id; };
	void addUC(string uc, int vac) { vagas.push_back(make_pair(uc, vac)); if (vac < getVac()) vagasMin = vac; };
	int getVac() const { return vagasMin; };
	vector<pair<string, int>> getVagas() const { return vagas; };
	void decVac();
	bool operator<(const Turma& that) const;
};