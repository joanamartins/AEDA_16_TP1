#pragma once

#include <iostream>
#include <unordered_set>
//#include <tr1/unordered_set>
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

struct acabadoH
{
	int operator() (const Acabado * a) const
	{
		int i = 0;
		for (size_t j = 0; j < a->getCodigo().length(); j++)
		{
			i += a->getCodigo()[j];
		}
		return i;
	}
};

struct acabadoEq
{
	bool operator() (const Acabado * a1, const Acabado * a2) const
	{
		return a1->getCodigo() == a2->getCodigo();
	}
};

typedef tr1::unordered_set<Acabado *, acabadoH, acabadoEq> tabHAcabado;

class Curso {
	string sigla;
	string nome;
	vector<Ucurricular *> ucurriculares;
	vector<Optativa *> optativas;
	vector<Estudante *> estudantes;
	vector<Docente *> docentes;
	vector<priority_queue<Turma>> turmas;	//1 queue per year
	
public:
	tabHAcabado acabados;
	Curso();
	~Curso() {};
	vector<Ucurricular *> getUCs() const;
	vector<Optativa *> getOpts() const;
	vector<Estudante *> getEstudantes() const;
	vector<Docente *> getDocentes() const;
	vector<priority_queue<Turma>> getTurmas() { return turmas; };
	tabHAcabado getAcabados() { return acabados; };
	int getAno(string codigo);
	int getSemestre(string codigo);
	void addUC(Ucurricular *uc);
	void addUCopt(Optativa *opt);
	void addEstudante(Estudante *est);
	void addDocente(Docente * doc);
	void addAcabado(Acabado * ac) { acabados.insert(ac); };
	int getEstudanteAno(Estudante * est) const;		//useless function
	void setUCs(const vector <Ucurricular *> &ucs);
	void eraseStudent(Estudante * student);
	void newStudent();
	void swapClass(int i, const Turma &t);
	void readData(string file);
	void saveData(string file) const;
};
