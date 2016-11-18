#pragma once

#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

class Ucurricular {
	string codigo;
	string sigla;
	string nome;
	float creditos;
	//int vagas;
	int ano;
	int semestre;
	//string areaCientifica;
public:
	Ucurricular() {};
	~Ucurricular() {};
	Ucurricular(string codigo, string sigla, string nome, float creditos, int ano, int semestre);
	string getCodigo() const;
	string getSigla() const;
	string getNome() const;
	//int getVagas() const;
	float getCreditos() const;
	int getAno() const;
	int getSemestre() const;
	void increaseVacancy(int i);
	string info() const;
	string info(int i) const;
	bool operator=(Ucurricular that);
};

class Optativa : private Ucurricular {
	int vagas;
	string areaCientifica;
public:
	Optativa() {};
	~Optativa() {};
	Optativa(string codigo, string sigla, string nome, float creditos, int vagas, int ano, int semestre, string areaCientifica);
	int getVagas() const;
	string getArea() const;
};