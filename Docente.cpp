#include "Docente.h"
#include "Curso.h"
#include "Estudante.h"

int Docente::id = 0;

Docente::Docente(string sigla, int codigo, string email, string nome)
{
	this->sigla = sigla;
	this->codigo = codigo;
	this->email = "invalido";
	if (validEmail(email))
		this->email = email;
	else
	{
		transform(sigla.begin(), sigla.end(), sigla.begin(), ::tolower);
		sigla.append("@fe.up.pt");
		this->email = sigla;
	}
	this->nome = nome;
}

string Docente::getNome() const
{
	return nome;
}

string Docente::getEmail() const
{
	return email;
}

vector<string> Docente::getEstudantes() const
{
	return estudantes;
}

void Docente::addEstudante(string codigo)
{
	estudantes.push_back(codigo);
}

string Docente::info() const
{
	stringstream ss;
	ss << sigla << "\t" << codigo << "\t" << email;
	for (size_t i = 0; i < 20 - email.length(); i += 1)
		ss << ' ';
	ss << nome << '\n';
	return ss.str();
}