#include "Ucurricular.h"

Ucurricular::Ucurricular(string codigo, string sigla, string nome, float creditos, int vagas, int ano, int semestre, string areaCientifica)
{
	this->codigo = codigo;
	this->sigla = sigla;
	this->nome = nome;
	this->creditos = creditos;
	this->vagas = vagas;
	this->ano = ano;
	this->semestre = semestre;
	this->areaCientifica = areaCientifica;
}

string Ucurricular::getCodigo() const
{
	return codigo;
}

string Ucurricular::getSigla() const
{
	return sigla;
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

void Ucurricular::decreaseVacancy()
{
	vagas--;
}

string Ucurricular::info() 
{
	stringstream ss;
	ss << codigo << "\t" << setw(9) << sigla << "\t" << nome;
	for (size_t i = 0; i < 72 - nome.length(); i += 1)
		ss << ' ';
	ss << creditos << "\t\t\t" << vagas << endl;
	return ss.str();
}