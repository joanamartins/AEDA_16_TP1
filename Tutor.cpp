#include "Tutor.h"
#include "Curso.h"


Tutor::Tutor(string nome, string email)
{
	this->nome = nome;
	this->email = email;
}

string Tutor::getNome() const
{
	return nome;
}

string Tutor::getEmail() const
{
	return email;
}

vector<string> Tutor::getEstudantes() const
{
	return estudantes;
}