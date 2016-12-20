#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Ucurricular.h"
#include "Turma.h"
#include "Estudante.h"
#include "Docente.h"
#include "sequentialSearch.h"
using namespace std;

class Curso {
	string sigla;
	string nome;
	vector<Ucurricular *> ucurriculares;
	vector<Optativa *> optativas;
	vector<Estudante *> estudantes;
	vector<Docente *> docentes;
	vector<priority_queue<Turma *>> turmas;	//1 queue per year
public:
	Curso();
	~Curso() {};
	vector<Ucurricular *> getUCs() const;
	vector<Optativa *> getOpts() const;
	vector<Estudante *> getEstudantes() const;
	vector<Docente *> getDocentes() const;
	vector<priority_queue<Turma *>> getTurmas() const { return turmas; };
	int getAno(string codigo);
	int getSemestre(string codigo);
	void addUC(Ucurricular *uc);
	void addUCopt(Optativa *opt);
	void addEstudante(Estudante *est);
	void addDocente(Docente * doc);
	int getEstudanteAno(Estudante * est) const;		//useless function
	void setUCs(const vector <Ucurricular *> &ucs);
	void newStudent();
	void readData(string file);
	void saveData(string file) const;
};
