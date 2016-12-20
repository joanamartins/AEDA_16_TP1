#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "BST.h"
#include "Reuniao.h"
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
	BST<Reuniao> reunioes;
public:
	static int id;
	Docente() : reunioes(Reuniao()) {};
	~Docente() {};
	Docente(string sigla, int codigo, string email, string nome);
	string getNome() const;
	string getEmail() const;
	vector<string> getEstudantes() const;
	void addEstudante(string codigo);
	void addReuniao();
	void removeReuniao();
	void editReuniao();
	string info() const;
	void Menu();
};

void docLogin();