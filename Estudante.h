#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

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
	typedef map<int, string> Estatutos;
	static Estatutos estatutos;
	string getCodigo() const;
	string getNome() const;
	unsigned long getPassword() const;
	vector<pair<string, int>> getResultados() const;
	void addUC(string codigo, int resultado);
	string info() const;
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