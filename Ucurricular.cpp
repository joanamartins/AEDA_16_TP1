#include "Ucurricular.h"

Ucurricular::Ucurricular(string codigo, string sigla, string nome, float creditos, int ano, int semestre)
{
	this->codigo = codigo;
	this->sigla = sigla;
	this->nome = nome;
	this->creditos = creditos;
	this->ano = ano;
	this->semestre = semestre;
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

float Ucurricular::getCreditos() const
{
	return creditos;
}

int Ucurricular::getAno() const
{
	return ano;
}

int Ucurricular::getSemestre() const
{
	return semestre;
}

string Ucurricular::info(char c) const
{
	stringstream ss;
	ss << codigo << "\t" << setw(9) << sigla << "\t" << nome;
	for (size_t i = 0; i < 72 - nome.length(); i += 1)
		ss << ' ';
	ss << creditos << c;
	return ss.str();
}

bool Ucurricular::operator=(Ucurricular that)
{
	return (this->codigo == that.getCodigo() && this->sigla == that.getSigla() && this->creditos == that.getCreditos());
}

Optativa::Optativa(string codigo, string sigla, string nome, float creditos, int vagas, int ano, int semestre, string areaCientifica) : Ucurricular(codigo, sigla, nome, creditos, ano, semestre)
{
	this->vagas = vagas;
	this->areaCientifica = areaCientifica;
}

int Optativa::getVagas() const
{
	return vagas;
}

string Optativa::getArea() const
{
	return areaCientifica;
}

string Optativa::info(char c) const
{
	return Ucurricular::info(0) + "\t\t" + to_string(getVagas()) + c;
}

void Optativa::increaseVacancy(int i)
{
	vagas += i;
}