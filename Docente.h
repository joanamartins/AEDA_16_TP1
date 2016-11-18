#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "Utils.h"
using namespace std;

extern vector<Curso *> feup;

//class Curso;

class Docente {
	string sigla;
	int codigo;
	string email;
	string nome;
	vector<string> estudantes;
public:
	static int id;
	Docente() {};
	~Docente() {};
	Docente(string sigla, int codigo, string email, string nome);
	string getNome() const;
	string getEmail() const;
	vector<string> getEstudantes() const;
	void addEstudante(string codigo);
	string info() const;
};
