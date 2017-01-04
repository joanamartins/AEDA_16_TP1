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
	int menu = getMenu(s, "Escolha um estudante");
	menu--;

	cout << "Insira uma descricao: ";
	cin.ignore();
	getline(cin, desc);

	reunioes.insert(Reuniao(date, feup[0]->getEstudantes()[menu]->getCodigo(), desc));

}

void Docente::removeReuniao()
{
	string d;
	cout << "Introduza a data da reuniao a eliminar no formato dd/mm/aa\n\t>";
	cin.ignore();
	getline(cin, d);
	Date date(d);
	Reuniao r;
	r.setDate(date);
	cout << "\nReuniao a eliminar:\n" << reunioes.find(r);
	system("PAUSE");
	reunioes.remove(r);
}

void Docente::editReuniao()
{
	string d, s, desc;
	cout << "Introduza a data da reuniao a editar no formato dd/mm/aa\n\t>";
	cin.ignore();
	getline(cin, d);
	Date * date = new Date(d);
	Reuniao r;
	r.setDate(*date);
	r = reunioes.find(r);
	Reuniao r2 = r;

	system("CLS");
	cout << r;
	int menu = getMenu("Data,Estudante,Descricao,Cancelar", "Deseja alterar:"), menuS;
	switch (menu) {
	case 1:
		cout << "Introduza a nova data\n\t>";
		cin.ignore();
		getline(cin, d);
		date = new Date(d);
		reunioes.remove(r);
		r2.setDate(*date);
		reunioes.insert(r2);
		break;
	case 2:
		s = "";
		for (size_t i = 0; i < feup[0]->getEstudantes().size(); i++)
		{
			if (i > 0)
				s += ",";
			s += feup[0]->getEstudantes()[i]->getCodigo();
		}
		menuS = getMenu(s, "Escolha um estudante");
		menuS--;
		reunioes.remove(r);
		r2.setStu(feup[0]->getEstudantes()[menuS]->getCodigo());
		reunioes.insert(r2);
		break;
	case 3:
		cout << "Introduza a nova descricao: ";
		cin.ignore();
		getline(cin, desc);
		reunioes.remove(r);
		r2.setDesc(desc);
		reunioes.insert(r2);
		break;
	default:
		break;
	}
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

void Docente::menu()
{
	int menu = -1, menuStu = -1;
	vector<priority_queue<Turma>> turmas = feup[0]->getTurmas();
	while (menu != 4)
	{
		system("CLS");
		menu = getMenu("Visualizar turmas,Visualizar estudantes,Reunioes,Logout");
		switch (menu) {
		case 1:
			system("CLS");
			turmas = feup[0]->getTurmas();
			for (size_t i = 0; i < turmas.size()-1; i++)
			{
				cout << i + 1 << "o ano\n";
				for (size_t j = 0; j < 3; j++)
				{
					cout << "  Turma " << turmas[i].top().getID() << " (Vagas da UC mais ocupada: " << turmas[i].top().getVac() << ")\n    ";
					for (size_t k = 0; k < turmas[i].top().getVagas().size(); k++)
					{
						cout << turmas[i].top().getVagas()[k].first << " - " << turmas[i].top().getVagas()[k].second <<", ";
					}
					cout << endl;
					turmas[i].pop();
				}
			}
			system("PAUSE");
			break;
		case 2:
			while (menuStu != 3)
			{
				system("CLS");
				menuStu = getMenu("Estudantes atuais,Ex-estudantes,Voltar atras");
				switch (menuStu) {
				case 1:
					system("CLS");
					cout << "Codigo\t\tPassword (hashed)\tEmail\t\t\tNome\t\t\t\t\tEstatuto\t\tData de inscricao\n";
					for (size_t i = 0; i < feup[0]->getEstudantes().size(); i++)
					{
						cout << feup[0]->getEstudantes()[i]->info();
					}
					system("PAUSE");
					break;
				case 2:
					system("CLS");
					cout << "Codigo\t\tPassword (hashed)\tEmail\t\t\tNome\t\t\t\t\tEstatuto\t\tEstado\n";
					for (auto it = feup[0]->acabados.begin(); it != feup[0]->acabados.end(); it++)
					{
						cout << (*it)->info();
					}
					system("PAUSE");
					break;
				default:
					break;
				}
			}
			break;
		case 3:
			menuReunioes();
			break;
		default:
			break;
		}
	}
}
void Docente::menuReunioes()
{
	int menu = -1;
	string line;
	int totalReunioes, day, month, year, stu;
	Date *d = new Date();
	Reuniao *r = new Reuniao();
	while (menu != 7)
	{
		system("CLS");
		menu = getMenu("Nova reuniao,Cancelar reuniao,Alterar reuniao,Visualizar reunioes,Marcar reunioes automaticamente,Marcar reunioes aleatoriamente,Sair", "Reunioes");
		switch (menu) {
		case 1:
			addReuniao();
			break;
		case 2:
			removeReuniao();
			break;
		case 3:
			editReuniao();
			break;
		case 4:
			reunioes.printTree();
			system("PAUSE");
			break;
		case 5:
			cout << "Quantas?\n  >";
			cin.ignore();
			getline(cin, line);
			totalReunioes = stoi(line);
			for (int i = 0; i < totalReunioes; i++)
			{
				day = d->getDay();
				day++;
				month = d->getMonth();
				year = d->getYear();
				if (day > daysInMonth(month, year))
				{
					day = 1;
					month++;
				}
				if (month > 12)
				{
					month = 1;
					year++;
				}
				d = new Date(day, month, year);
				stu = i % feup[0]->getEstudantes().size();
				r = new Reuniao(*d, feup[0]->getEstudantes()[stu]->getCodigo(), to_string(i));
				reunioes.insert(*r);
			}
			break;
		case 6:
			cout << "Quantas?\n  >";
			cin.ignore();
			getline(cin, line);
			totalReunioes = stoi(line);
			for (int i = 0; i < totalReunioes; i++)
			{
				year = rand() % 10 + 2010;
				month = rand() % 12 + 1;
				day = rand() % daysInMonth(month, year) + 1;
				d = new Date(day, month, year);
				stu = rand() % feup[0]->getEstudantes().size();
				r = new Reuniao(*d, feup[0]->getEstudantes()[stu]->getCodigo(), to_string(i));
				reunioes.insert(*r);
			}
			break;
		default:
			break;
		};
	}
}

void docLogin()
{
	feup[0]->getDocentes()[0]->menu();
	
}
