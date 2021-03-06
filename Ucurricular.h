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
	int ano;
	int semestre;
public:
	Ucurricular() {};
	~Ucurricular() {};
	Ucurricular(string codigo, string sigla, string nome, float creditos, int ano, int semestre);
	string getCodigo() const;
	string getSigla() const;
	string getNome() const;
	float getCreditos() const;
	int getAno() const;
	int getSemestre() const;
	virtual string info(char c) const;
	bool operator=(Ucurricular that);
};

class Optativa : public Ucurricular {
	int vagas;
	string areaCientifica;
public:
	Optativa() {};
	~Optativa() {};
	Optativa(string codigo, string sigla, string nome, float creditos, int vagas, int ano, int semestre, string areaCientifica);
	int getVagas() const;
	string getArea() const;
	string info(char c) const;
	void increaseVacancy(int i);
};