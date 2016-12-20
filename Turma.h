#pragma once

#include <vector>
#include "Ucurricular.h"

using namespace std;

class Turma {
	int id;
	int vagasTotal;
	vector<pair<string,int>> vagas;
public:
	Turma() { id = idg; vagasTotal = 0; idg++; };
	Turma(vector<pair<string, int>> vac) : vagas(vac) { id = idg; idg++; };
	static int idg;
	int getID() { return id; };
	void addUC(string uc, int vac) { vagas.push_back(make_pair(uc, vac)); vagasTotal += vac; };
	int getVac() { return vagasTotal; };
	void decVac() { for (size_t i = 0; i < vagas.size(); i++) { vagas[i].second--;	vagasTotal--; } };
	bool operator<(Turma that) { return this->vagasTotal < that.vagasTotal; };
};