#include "Estudante.h"
#include "Curso.h"
#include "Ucurricular.h"

Estudante::Estatutos Estudante::estatutos = {
	{ 0, "Ordinario" },
	{ 1, "Trabalhador Estudante" },
	{ 2, "Dirigente Associativo" },
	{ 3, "Praticante de Desporto de Alto Rendimento" },
	{ 4, "Pai e Mae Estudante" },
	{ 5, "Necessidades Educativas Especiais" },
	{ 6, "Militar" },
	{ 7, "Bombeiro" },
	{ 8, "Praticante de Confissoes Religiosas" },
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

string Estudante::getEmail() const
{
	return email;
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

int Estudante::getAno() const
{
	int ret = 0;
	for (size_t i = 0; i < getResultados().size(); i++)
	{
		for (size_t j = 0; j < feup[0]->getUCs().size(); j++)
		{
			if (getResultados()[i].first == feup[0]->getUCs()[j]->getCodigo() && feup[0]->getUCs()[j]->getAno() > ret)
			{
				ret = feup[0]->getUCs()[j]->getAno();
			}
		}
	}
	return ret + 1;
}

void Estudante::setEmail(string email)
{
	this->email = email;
}

void Estudante::setResultados(const vector <Ucurricular *> &ucs)
{
	bool notFound = true;
	for (size_t i = 0; i < ucs.size(); i++)
	{
		notFound = true;
		for (size_t j = 0; j < getResultados().size(); j++)
		{
			if (ucs[i]->getCodigo() == getResultados()[j].first)
			{
				notFound = false;
				break;
			}
		}
		if (notFound)
			addUC(ucs[i]->getCodigo(), -1);
	}
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

bool compareByResult(pair<string, int> uc1, pair<string, int> uc2)
{
	return uc1.second < uc2.second;
}

bool validEmail(string email)
{
	int at = email.find((char)64);
	size_t pt;
	if (at != email.npos)
	{
		email.erase(email.begin(), email.begin() + at);
		pt = email.find('.');
		if (pt != email.npos && pt < email.length())
			return true;
	}
	return false;
}

void Estudante::menu() {
	int menuAluno = -1;
	while (menuAluno != 4) {
		system("CLS");
		menuAluno = getMenu("Visualizar,Editar dados,Inscricao em UCs,Logout");
		switch (menuAluno) {
		case 1:
			menuVisualizar();
			break;
		case 2:
			menuEditar();
			break;
		case 3:
			menuInscrever();
			break;
		}
	}
}

void Estudante::menuVisualizar()
{
	int i = 0;
	int menuV = -1, menuVUC = -1;
	int ano, semestre, resultado;
	bool noResult = true;
	bool isEmpty = true;
	while (menuV != 3) {
		system("CLS");
		menuV = getMenu("Dados,Unidades curriculares,Voltar atras");
		switch (menuV) {
		case 1:
			menuV = 3;
			system("CLS");
			cout << "Codigo\t\t\tPassword\tEmail\t\t\tNome\t\t\t\t\tTrabalhador\n";
			cout << info();
			system("PAUSE");
			break;
		case 2:
			menuVUC = -1;
			while (menuVUC != 4) {
				system("CLS");
				menuVUC = getMenu("Todas,Por ano/semestre,Por resultado,Voltar atras");
				switch (menuVUC) {
				case 1:
					menuVUC = 4;
					system("CLS");
					cout << "Codigo da UC\tNome\t\t\t\t\t\t\t\t\t\tResultado";
					for (size_t k = 0; k < feup[i]->getUCs().size(); k++)
					{
						noResult = true;
						cout << endl << feup[i]->getUCs()[k]->getCodigo() << "\t\t" << feup[i]->getUCs()[k]->getNome();
						for (size_t m = 0; m < 82 - feup[i]->getUCs()[k]->getNome().length(); m += 1)
							cout << ' ';
						for (vector<pair<string, int>>::const_iterator l = resultados.begin(); l != resultados.end(); l++)
						{

							if (feup[i]->getUCs()[k]->getCodigo() == (*l).first)
							{
								noResult = false;
								cout << (*l).second;
							}
						}
						if (noResult)
							cout << "Sem resultado";
					}
					cout << endl;
					system("PAUSE");
					break;
				case 2:
					menuVUC = 4;
					system("CLS");
					cout << "Ano";
					ano = getInt(1, 5);
					cout << "Semestre";
					semestre = getInt(1, 2);
					system("CLS");
					cout << "Codigo      Sigla\tNome\t\t\t\t\t\t\t\t\t\tResultado\n";
					isEmpty = true;
					for (size_t k = 0; k < getResultados().size(); k++)
					{
						for (size_t l = 0; l < feup[i]->getUCs().size(); l++)
						{
							if (feup[i]->getUCs()[l]->getCodigo() == getResultados()[k].first)
							{
								if (feup[i]->getUCs()[l]->getAno() == ano && feup[i]->getUCs()[l]->getSemestre() == semestre)
								{
									cout << feup[i]->getUCs()[l]->getCodigo() << '\t' <<
										feup[i]->getUCs()[l]->getSigla() << '\t' <<
										feup[i]->getUCs()[l]->getNome();
									for (size_t m = 0; m < 80 - feup[i]->getUCs()[l]->getNome().length(); m += 1)
										cout << ' ';
									cout << getResultados()[k].second << endl;
									isEmpty = false;
								}
							}
						}
					}
					if (isEmpty)
					{
						system("CLS");
						cout << "Nenhuma cadeira no ano/semestre especificado\n";
					}
					system("PAUSE");
					break;
				case 3:
					menuVUC = 4;
					system("CLS");
					cout << "Resultado minimo";
					resultado = getInt(0, 20);
					sort(resultados.begin(), resultados.end(), compareByResult);
					system("CLS");
					cout << "Codigo da UC\tNome\t\t\t\t\t\t\t\t\tResultado\n";
					for (vector<pair<string, int>>::const_iterator k = resultados.begin(); k != resultados.end(); k++)
					{
						if ((*k).second >= resultado)
						{
							cout << (*k).first << "\t\t";
							for (size_t l = 0; l < feup[i]->getUCs().size(); l++)
							{
								if ((*k).first == feup[i]->getUCs()[l]->getCodigo())
								{
									cout << feup[i]->getUCs()[l]->getNome();
									for (size_t m = 0; m < 72 - feup[i]->getUCs()[l]->getNome().length(); m += 1)
										cout << ' ';
									break;
								}
							}
							cout << (*k).second << endl;
						}
					}
					system("PAUSE");
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}
}

void Estudante::menuEditar()
{
	int menuE = -1;
	while (menuE != 4) {
		system("CLS");
		menuE = getMenu("Email,Password,Estatuto,Voltar atras");
		switch (menuE) {
		case 1:
			menuE = 4;
			cin.ignore();
			email = "";
			cout << "Email atual: " << getEmail() << endl;
			while (!(validEmail(email)))
			{
				cout << "Novo email: ";
				getline(cin, email);
				if (validEmail(email))
				{
					setEmail(email);
					cout << "Email alterado com sucesso\n";
				}
				else
					cout << "Email invalido\n";

			}
			system("PAUSE");
			break;
		}
	}
}

void Estudante::menuInscrever()
{
	system("CLS");
	int i = 0;
	vector <Ucurricular *> ucs = feup[i]->getUCs();
	vector <Ucurricular *> ucs_tmp;
	ucs_tmp.clear();
	for (size_t l = 0; l < ucs.size(); l++)
	{
		if (ucs[l]->getAno() > getAno())
		{
			ucs.erase(ucs.begin() + l);
			l--;
		}
	}
	for (size_t k = 0; k < resultados.size(); k++)
	{
		for (size_t l = 0; l < ucs.size(); l++)
		{
			if (resultados[k].first == ucs[l]->getCodigo())
			{
				ucs.erase(ucs.begin() + l);
				l--;
			}
		}
	}
	int menuIUC = -1;
	float creditos = 0;
	for (size_t l = 0; l < ucs.size(); l++)
	{
		if (ucs[l]->getAno() <= getAno() - 1)
		{
			creditos += ucs[l]->getCreditos();
			ucs[l]->increaseVacancy(-1);
			ucs_tmp.push_back(ucs[l]);
			ucs.erase(ucs.begin() + l);
			l--;
		}
	}
	stringstream ss;
	for (size_t l = 0; l < ucs.size(); l++)
	{
		ss << ucs[l]->getAno() << '\t' << ucs[l]->getSemestre() << '\t' << ucs[l]->info(0) << ',';
	}
	ss << "Finalizar";
	string menuOptions = ss.str();
	string menuTitle = "  Ano\tSemestre Codigo\t    Sigla\tNome\t\t\t\t\t\t\t\t\tCreditos\t\tVagas";
	int menuIUCmax = 0;
	for (size_t i = 0; i < ss.str().length(); i++)
		if (ss.str()[i] == ',')
			menuIUCmax++;
	menuIUCmax++;
	string menuCredits;
	bool found;
	while (menuIUC != menuIUCmax)
	{
		ss.str(string());
		ss << "Creditos: " << creditos << "/75\n";
		menuCredits = ss.str();
		menuCredits += menuTitle;
		ss.str(string());
		system("CLS");
		cout << "Selecione uma cadeira nao inscrita para se inscrever, ou uma inscrita para anular a inscricao\n";
		if (ucs_tmp.size() > 0)
			ss << "Cadeiras inscritas:\n  Ano\tSemestre Codigo\t    Sigla\tNome\t\t\t\t\t\t\t\t\tCreditos\t\tVagas\n";;
		for (size_t l = 0; l < ucs_tmp.size(); l++)
		{
			ss << "   " << ucs_tmp[l]->getAno() << '\t' << ucs_tmp[l]->getSemestre() << '\t' << ucs_tmp[l]->info();
		}
		string cadeirasEscolhidas = ss.str();
		ss.str(string());
		menuIUC = getMenu(menuOptions, menuCredits, cadeirasEscolhidas);
		if (menuIUC == menuIUCmax)
			break;
		found = false;
		for (size_t l = 0; l < ucs_tmp.size(); l++)
		{
			if (ucs[menuIUC - 1] == ucs_tmp[l])
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			creditos += ucs[menuIUC - 1]->getCreditos();
			if (creditos > 75)
			{
				creditos -= ucs[menuIUC - 1]->getCreditos();
				system("CLS");
				cout << "Nao pode ultrapassar 75 creditos por ano!\n";
				system("PAUSE");
			}
			else if (ucs[menuIUC - 1]->getVagas() <= 0)
			{
				creditos -= ucs[menuIUC - 1]->getCreditos();
				system("CLS");
				cout << "A cadeira " << ucs[menuIUC - 1]->getSigla() << " nao tem vagas.\n";
				system("PAUSE");
			}
			else
			{
				ucs[menuIUC - 1]->increaseVacancy(-1);
				ucs_tmp.push_back(ucs[menuIUC - 1]);
			}
		}
		else
		{
			ucs[menuIUC - 1]->increaseVacancy(1);
			creditos -= ucs[menuIUC - 1]->getCreditos();
			for (size_t l = 0; l < ucs_tmp.size(); l++)
			{
				if (ucs[menuIUC - 1] == ucs_tmp[l])
				{
					ucs_tmp.erase(ucs_tmp.begin() + l);
					l--;
					break;
				}
			}
		}
		for (size_t l = 0; l < ucs.size(); l++)
		{
			ss << ucs[l]->getAno() << '\t' << ucs[l]->getSemestre() << '\t' << ucs[l]->info(0) << ',';
		}
		ss << "Finalizar";
		menuOptions = ss.str();
	}

	feup[i]->setUCs(ucs);
	setResultados(ucs_tmp);
	system("PAUSE");
}

void login()
{
	string username;
	string nome;
	string password;
	unsigned long hashedPassword;
	bool studentExists = false;
	bool validPassword = false;

	system("CLS");
	cin.ignore();
	cout << "Username: ";
	getline(cin, username);
	if (username.find("@") != string::npos)
		username.erase(username.begin() + username.find("@"), username.end());
	cout << "Password: ";
	password = maskPassword();
	hashedPassword = hashing(password);

	studentExists = false;
	validPassword = false;
	size_t i, j;
	for (size_t i1 = 0; i1 < feup.size(); i1++)
	{
		for (size_t j1 = 0; j1 < feup[i1]->getEstudantes().size(); j1++)
		{
			if (feup[i1]->getEstudantes()[j1]->getCodigo() == username && !(studentExists))
			{
				studentExists = true;
				i = i1;
				j = j1;
				if (feup[i1]->getEstudantes()[j1]->getPassword() == hashedPassword)
				{
					validPassword = true;
					nome = feup[i1]->getEstudantes()[j1]->getNome();
					break;
				}
				break;
			}
		}
	}

	if (studentExists && validPassword)
	{
		cout << "Bemvindo, " << nome << endl;
		system("PAUSE");
		feup[i]->getEstudantes()[j]->menu();
	}
	else if (studentExists)
	{
		throw PasswordInvalida(hashedPassword);
	}
	else
	{
		throw EstudanteInvalido(username);
	}
}
