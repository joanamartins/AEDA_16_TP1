#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Menus.h"
using namespace std;

extern vector<Curso *> feup;

class Curso;
class Ucurricular;

class Estudante {
	string codigo;
	unsigned long password;
	string email;
	string nome;
	int estatuto;
	vector<pair<string, int>> resultados;
public:
	Estudante() {};
	~Estudante() {};
	Estudante(string codigo, string password, string email, string nome, int estatuto);
	Estudante(string codigo, unsigned long password, string email, string nome, int estatuto);
	Estudante(string codigo, string password, string email, string nome, string estatuto);
	Estudante(string codigo, unsigned long password, string email, string nome, string estatuto);
	typedef map<int, string> Estatutos;
	static Estatutos estatutos;
	static int getEstatuto(string estatuto);
	string getCodigo() const;
	string getEmail() const;
	string getNome() const;
	unsigned long getPassword() const;
	vector<pair<string, int>> getResultados() const;
	int getAno() const;
	void setEmail(string email);
	void setResultados(const vector <Ucurricular *> &ucs);
	void addUC(string codigo, int resultado);
	string info() const;
	void menu();
	void menuVisualizar(); 
	void menuEditar();
	void menuInscrever();
};

class EstudanteInvalido {
	string nome;
public:
	EstudanteInvalido(string nome);
	void usernameInvalido();
};

class PasswordInvalida {
	unsigned long password;
public:
	PasswordInvalida(unsigned long password);
	void passwordInvalida();
};

unsigned long hashing(string password);

bool compareByResult(pair<string, int> uc1, pair<string, int> uc2);

bool validEmail(string email);

void login();