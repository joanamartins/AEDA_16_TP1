#include "Exceptions.h"

EmailInvalido::EmailInvalido(string email)
{
	this->email = email;
}

void EmailInvalido::emailInvalido()
{
	cout << "Email invalido: ";
	if (email.find('@') == email.npos)
		cout << "falta a arroba\n";
	else
		cout << "falta o ponto\n";
	system("PAUSE");
}

EstudanteInvalido::EstudanteInvalido(string nome)
{
	this->nome = nome;
}

void EstudanteInvalido::usernameInvalido()
{
	cout << "Username nao existe: " << "\"" << nome << "\"" << endl;
	system("PAUSE");
}

DocenteInvalido::DocenteInvalido(string sigla)
{
	this->sigla = sigla;
}

void DocenteInvalido::siglaInvalida()
{
	cout << "Sigla nao existe: " << "\"" << sigla << "\"" << endl;
	system("PAUSE");
}

PasswordInvalida::PasswordInvalida(unsigned long password)
{
	this->password = password;
}

void PasswordInvalida::passwordInvalida()
{
	cout << "Invalid password." << endl;
	system("PAUSE");
}