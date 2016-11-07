#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Ucurricular.h"
#include "Estudante.h"
using namespace std;

class Curso {
	string sigla;
	string nome;
	vector <Ucurricular *> ucurriculares;
	vector <Estudante *> estudantes;
public:
	Curso() {};
	~Curso() {};
	Curso(string sigla, string nome);
	vector <Ucurricular *> getUCs() const;
	vector <Estudante *> getEstudantes() const;
	void addUC(Ucurricular *uc);
	void addEstudante(Estudante *est);
	void readData(string file);
	void saveData(string file) const;
};
