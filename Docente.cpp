#include "Docente.h"
#include "Curso.h"
#include "Estudante.h"

int Docente::id = 0;

Docente::Docente(string sigla, int codigo, string email, string nome) : reunioes(Reuniao())
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

void Docente::addReuniao()
{
	string d, s, desc;
	cout << "Introduza a data da reuniao no formato dd/mm/aa\n\t>";
	cin.ignore();
	getline(cin, d);
	Date date(d);

	s = "";
	for (size_t i = 0; i < feup[0]->getEstudantes().size(); i++)
	{
		if (i > 0)
			s += ",";
		s += feup[0]->getEstudantes()[i]->getCodigo();
	}
	int menu = getMenu(s, "Escolha um  estudante");
	menu--;

	cout << "Insira uma descricao: ";
	cin.ignore();
	getline(cin, desc);

	reunioes.insert(Reuniao(date, feup[0]->getEstudantes()[menu]->getCodigo(), desc));
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

void Docente::Menu()
{
	int menu = -1;
	while (menu != 5)
	{
		system("CLS");
		menu = getMenu("Nova reuniao,Cancelar reuniao,Alterar reuniao,Visualizar reunioes,Sair", "Reunioes");
		switch (menu) {
		case 1:
			addReuniao();
			break;
		case 2:
			//removeReuniao();
			break;
		case 4:
			reunioes.printTree();
			system("PAUSE");
			break;
		};
	}
}

void docLogin()
{
	feup[0]->getDocentes()[0]->Menu();
	
}
