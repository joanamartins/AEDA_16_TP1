#include "Estudante.h"

Estudante::Estatutos Estudante::estatutos = {
	{ 0, "Ordinário" },
	{ 1, "Trabalhador Estudante" },
	{ 2, "Dirigente Associativo" },
	{ 3, "Praticante de Desporto de Alto Rendimento" },
	{ 4, "Pai e Mãe Estudante" },
	{ 5, "Necessidades Educativas Especiais" },
	{ 6, "Militar" },
	{ 7, "Bombeiro" },
	{ 8, "Praticante de Confissões Religiosas" },
	{ 9, "Estudante-atleta da U.Porto" }
};

Estudante::Estudante(string codigo, string password, string email, string nome, int estatuto) {
	this->codigo = codigo;
	this->email = email;
	this->nome = nome;
	this->estatuto = estatuto;
	this->password = hashing(password);
}

Estudante::Estudante(string codigo, unsigned long password, string email, string nome, int estatuto) {
	this->codigo = codigo;
	this->email = email;
	this->nome = nome;
	this->estatuto = estatuto;
	this->password = password;
}

int Estudante::getEstatuto(string estatuto)
{
	for (Estatutos::iterator i = estatutos.begin(); i != estatutos.end(); i++)
		if (i->second == estatuto)
			return i->first;
	return -1;
}

Estudante::Estudante(string codigo, string password, string email, string nome, string estatuto) {
	this->codigo = codigo;
	this->email = email;
	this->nome = nome;
	this->estatuto = getEstatuto(estatuto);
	this->password = hashing(password);
}

Estudante::Estudante(string codigo, unsigned long password, string email, string nome, string estatuto) {
	this->codigo = codigo;
	this->email = email;
	this->nome = nome;
	this->estatuto = getEstatuto(estatuto);
	this->password = password;
}

string Estudante::info() const {
	stringstream ss;
	ss << codigo << "\t\t" << password << "\t" << email << "\t" << nome;
	for (size_t i = 0; i < 40 - nome.length(); i += 1)
		ss << ' ';
	ss << estatutos[estatuto] << endl;
	return ss.str();
}

string Estudante::getCodigo() const
{
	return codigo;
}

string Estudante::getNome() const
{
	return nome;
}

unsigned long Estudante::getPassword() const
{
	return password;
}

vector<pair<string, int>> Estudante::getResultados() const
{
	return resultados;
}

void Estudante::addUC(string codigo, int resultado)
{
	pair<string, int> pair1(codigo, resultado);
	resultados.push_back(pair1);
}

EstudanteInvalido::EstudanteInvalido(string nome)
{
	this->nome = nome;
}

void EstudanteInvalido::usernameInvalido()
{
	cout << "Username does not exist: " << "\"" << nome << "\"" << endl;
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

unsigned long hashing(string password)
{
	int seed = 157;
	unsigned long hash = 0;
	for (size_t i = 0; i < password.length(); i++)
	{
		hash = (hash * seed) + password[i];
	}
	return hash;
}