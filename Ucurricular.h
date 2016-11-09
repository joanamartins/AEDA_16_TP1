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
	int vagas;
	int ano;
	int semestre;
	string areaCientifica;
public:
	Ucurricular() {};
	~Ucurricular() {};
	Ucurricular(string codigo, string sigla, string nome, float creditos, int vagas, int ano, int semestre, string areaCientifica);
	string getCodigo() const;
	string getSigla() const;
	string getNome() const;
	int getAno() const;
	int getSemestre() const;
	void decreaseVacancy();
	string info();
};

