#include "Ucurricular.h"

Ucurricular::Ucurricular(string codigo, string sigla, string nome, float creditos, int ano, int semestre, string areaCientifica)
{
	this->codigo = codigo;
	this->sigla = sigla;
	this->nome = nome;
	this->creditos = creditos;
	this->ano = ano;
	this->semestre = semestre;
	this->areaCientifica = areaCientifica;
}

string Ucurricular::getCodigo() const
{
	return codigo;
}

string Ucurricular::getNome() const
{
	return nome;
}

int Ucurricular::getAno() const
{
	return ano;
}

int Ucurricular::getSemestre() const
{
	return semestre;
}

string Ucurricular::info() 
{
	stringstream ss;
	ss << codigo << "\t" << setw(9) << sigla << "\t" << nome;
	for (int i = 0; i < 72 - nome.length(); i += 1)
		ss << ' ';
	ss << creditos << endl;
	return ss.str();
}