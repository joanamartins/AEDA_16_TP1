#pragma once

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Date.h"
#include "Exceptions.h"
#include "Menus.h"
using namespace std;

extern vector<Curso *> feup;

//class Curso;
class Ucurricular;
class Docente;

class Estudante {
	string codigo;
	unsigned long password;
	string email;
	string nome;
	int estatuto;
	int turma;
	Date * dataInscricao;
	vector<pair<string, int>> resultados;
public:
	Estudante() {};
	~Estudante() {};
	Estudante(string cod) : codigo(cod) {};
	Estudante(string codigo, string password, string email, string nome, int estatuto);
	Estudante(string codigo, unsigned long password, string email, string nome, int estatuto);
	Estudante(string codigo, string password, string email, string nome, string estatuto);
	Estudante(string codigo, unsigned long password, string email, string nome, string estatuto);
	Estudante(string codigo, unsigned long password, string email, string nome, int estatuto, int turma, Date * data, vector<pair<string, int>> resultados);
	typedef map<int, string> Estatutos;
	static Estatutos estatutos;
	static int getEstatuto(string estatuto);
	static int newCodigo;
	string getCodigo() const;
	string getEmail() const;
	string getNome() const;
	unsigned long getPassword() const;
	vector<pair<string, int>> getResultados() const;
	int getAno() const;
	Docente * getDocente();
	int getTurma() const { return turma; };
	Date * getData() const { return dataInscricao; };
	int getEstatuto() const { return estatuto; };
	void setDate();
	void setEmail(string email);
	void setResultados(const vector <Ucurricular *> &ucs);
	void addUC(string codigo, int resultado);
	string info() const;
	virtual void menu();
	void menuVisualizar(); 
	void menuEditar();
	void menuInscrever();
	void finalizarCurso();
};

unsigned long hashing(string password);

bool compareByResult(pair<string, int> uc1, pair<string, int> uc2);

bool validEmail(string email);

void studentLogin();

class Acabado : public Estudante {
	string estado;
public:
	Acabado() {};
	~Acabado() {};
	Acabado(string codigo, unsigned long password, string email, string nome, int estatuto, int turma, Date * data, vector<pair<string, int>> resultados, string estado)
		: Estudante(codigo, password, email, nome, estatuto, turma, data, resultados) {
		this->estado = estado;
	};
	Acabado(string codigo) : Estudante(codigo) { estado = "tmp"; };
	void menu();
	void recomecarCurso();
};