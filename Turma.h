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
	//void setVac(int v) { vagas = v; };
	//void decVacancy() { vagas--; };
	bool operator<(Turma that) { if (this->vagasTotal < that.vagasTotal) return true; else if (this->vagasTotal == that.vagasTotal && this->id < that.id) return true; return false; };
};