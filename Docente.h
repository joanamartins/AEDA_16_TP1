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
	unsigned password;
	vector<pair<string,string>> estudantes;
	BST<Reuniao> reunioes;
public:
	static int id;
	Docente() : reunioes(Reuniao()) {};
	~Docente() {};
	Docente(string sigla, int codigo, string email, string nome);
	string getNome() const;
	string getEmail() const;
	string getSigla() const { return sigla; };
	unsigned getPassword() const { return password; };
	vector<pair<string, string>> getEstudantes() const;
	void addEstudante(string codigo, string nome);
	void addReuniao();
	void removeReuniao();
	void editReuniao();
	string info() const;
	void menu();
	void menuReunioes();
};

void docLogin();