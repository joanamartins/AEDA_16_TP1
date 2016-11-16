#include <iostream>
#include <fstream>
#include <windows.h>
#include <algorithm>
//#include <stdlib.h>
#include "Faculdade.h"
#include "Curso.h"
#include "Ucurricular.h"
#include "Estudante.h"
#include "Menus.h"
using namespace std;

Faculdade feup;

string maskPassword()
{
	string password;
	char c;

	DWORD con_mode;
	DWORD dwRead;

	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hIn, &con_mode);
	SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	while (ReadConsoleA(hIn, &c, 1, &dwRead, NULL) && c != '\r')
	{
		if (c == '\b')
		{
			if (password.length() != 0)
			{
				cout << "\b \b";
				password.resize(password.length() - 1);
			}
		}
		else
		{
			password += c;
			cout << '*';
		}
	}
	cout << '\n';
	return password;
}

void menuAluno(string username) {
	size_t i, j;
	
	bool found = false;
	for (i = 0; i < feup.getCursos().size(); i++)
	{
		for (j = 0; j < feup.getCursos()[i]->getEstudantes().size(); j++)
		{
			if (feup.getCursos()[i]->getEstudantes()[j]->getCodigo() == username)
			{
				found = true;
				break;
			}
		}
		if (found)
			break;
	}
	Estudante * currentStudent = feup.getCursos()[i]->getEstudantes()[j];
	vector<pair<string, int>> resultados = currentStudent->getResultados();

	int ano, semestre, resultado;
	float creditos;
	int estudanteAno = feup.getCursos()[i]->getEstudanteAno(j);
	string email, menuTitle, menuCredits, menuOptions;
	stringstream ss;
	bool noResult = true;
	bool isEmpty = true;
	vector <Ucurricular *> ucs = feup.getCursos()[i]->getUCs();
	vector <Ucurricular *> ucs_tmp = ucs;
	int menuAluno = -1, menuV, menuVUC, menuE, menuIUC, menuIUCmax;
	while (menuAluno != 4) {
		system("CLS");
		menuAluno = getMenu("Visualizar,Editar dados,Inscricao em UCs,Logout");
		switch (menuAluno) {
		case 1:
			menuV = -1;
			while (menuV != 3) {
				system("CLS");
				menuV = getMenu("Dados,Unidades curriculares,Voltar atras");
				switch (menuV) {
				case 1:
					menuV = 3;
					system("CLS");
					cout << "Codigo\t\t\tPassword\tEmail\t\t\tNome\t\t\t\t\tTrabalhador\n";
					cout << currentStudent->info();
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
							for (size_t k = 0; k < feup.getCursos()[i]->getUCs().size(); k++)
							{
								noResult = true;
								cout << endl << feup.getCursos()[i]->getUCs()[k]->getCodigo() << "\t\t" << feup.getCursos()[i]->getUCs()[k]->getNome();
								for (size_t m = 0; m < 82 - feup.getCursos()[i]->getUCs()[k]->getNome().length(); m += 1)
									cout << ' ';
								for (vector<pair<string, int>>::const_iterator l = resultados.begin(); l != resultados.end(); l++)
								{
									
									if (feup.getCursos()[i]->getUCs()[k]->getCodigo() == (*l).first)
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
							for (size_t k = 0; k < currentStudent->getResultados().size(); k++)
							{
								for (size_t l = 0; l < feup.getCursos()[i]->getUCs().size(); l++)
								{
									if (feup.getCursos()[i]->getUCs()[l]->getCodigo() == currentStudent->getResultados()[k].first)
									{
										if (feup.getCursos()[i]->getUCs()[l]->getAno() == ano && feup.getCursos()[i]->getUCs()[l]->getSemestre() == semestre)
										{
											cout << feup.getCursos()[i]->getUCs()[l]->getCodigo() << '\t' <<
												feup.getCursos()[i]->getUCs()[l]->getSigla() << '\t' <<
												feup.getCursos()[i]->getUCs()[l]->getNome();
											for (size_t m = 0; m < 80 - feup.getCursos()[i]->getUCs()[l]->getNome().length(); m += 1)
												cout << ' ';
											cout << currentStudent->getResultados()[k].second << endl;
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
									for (size_t l = 0; l < feup.getCursos()[i]->getUCs().size(); l++)
									{
										if ((*k).first == feup.getCursos()[i]->getUCs()[l]->getCodigo())
										{
											cout << feup.getCursos()[i]->getUCs()[l]->getNome();
											for (size_t m = 0; m < 72 - feup.getCursos()[i]->getUCs()[l]->getNome().length(); m += 1)
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
				break;
		case 2:
			menuE = -1;
			while (menuE != 4) {
				system("CLS");
				menuE = getMenu("Email,Password,Estatuto,Voltar atras");
				switch (menuE) {
				case 1:
					menuE = 4;
					cin.ignore();
					email = "";
					cout << "Email atual: " << currentStudent->getEmail() << endl;
					while (!(validEmail(email)))
					{
						cout << "Novo email: ";
						getline(cin, email);
						if (validEmail(email))
						{
							currentStudent->setEmail(email);
							cout << "Email alterado com sucesso\n";
						}
						else
							cout << "Email invalido\n";
						
					}
					system("PAUSE");
					break;
				}
			}
			break;
		case 3:
			system("CLS");
			ucs = feup.getCursos()[i]->getUCs();
			ucs_tmp.clear();
			for (size_t l = 0; l < ucs.size(); l++)
			{
				if (ucs[l]->getAno() > estudanteAno)
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
			menuIUC = -1;
			creditos = 0;
			for (size_t l = 0; l < ucs.size(); l++)
			{
				if (ucs[l]->getAno() <= estudanteAno - 1)
				{
					creditos += ucs[l]->getCreditos();
					ucs[l]->increaseVacancy(-1);
					ucs_tmp.push_back(ucs[l]);
					ucs.erase(ucs.begin() + l);
					l--;
				}
			}
			for (size_t l = 0; l < ucs.size(); l++)
			{
				ss << ucs[l]->getAno() << '\t' << ucs[l]->getSemestre() << '\t' << ucs[l]->info(0) << ',';
			}
			ss << "Finalizar";
			menuOptions = ss.str();
			menuTitle = "  Ano\tSemestre Codigo\t    Sigla\tNome\t\t\t\t\t\t\t\t\tCreditos\t\tVagas";
			menuIUCmax = 0;
			for (size_t i = 0; i < ss.str().length(); i++)
				if (ss.str()[i] == ',')
					menuIUCmax++;
			menuIUCmax++;
			while (menuIUC != menuIUCmax)
			{
				ss.str(string());
				ss << "Creditos: " << creditos << "/75\n";
				menuCredits = ss.str();
				menuCredits += menuTitle;
				ss.str(string());
				system("CLS");
				cout <<"Selecione uma cadeira nao inscrita para se inscrever, ou uma inscrita para anular a inscricao\n";
				if (ucs_tmp.size() > 0)
					cout << "Cadeiras inscritas:\n  Ano\tSemestre Codigo\t    Sigla\tNome\t\t\t\t\t\t\t\t\tCreditos\t\tVagas\n";;
				for (size_t l = 0; l < ucs_tmp.size(); l++)
				{
					cout << "   " << ucs_tmp[l]->getAno() << '\t' << ucs_tmp[l]->getSemestre() << '\t' << ucs_tmp[l]->info();
				}
				menuIUC = getMenu(menuOptions, menuCredits);
				if (menuIUC == menuIUCmax)
					break;
				found = false;
				for (size_t l = 0; l < ucs_tmp.size(); l++)
				{
					if (ucs[menuIUC-1] == ucs_tmp[l])
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
			
			feup.getCursos()[i]->setUCs(ucs);
			feup.getCursos()[i]->setResultados(j, ucs_tmp);
			system("PAUSE");
			break;
			}
		}
	}
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

	for (size_t i = 0; i < feup.getCursos().size(); i++)
	{
		for (size_t j = 0; j < feup.getCursos()[i]->getEstudantes().size(); j++)
		{
			if (feup.getCursos()[i]->getEstudantes()[j]->getCodigo() == username)
			{
				studentExists = true;
				if (feup.getCursos()[i]->getEstudantes()[j]->getPassword() == hashedPassword)
				{
					validPassword = true;
					nome = feup.getCursos()[i]->getEstudantes()[j]->getNome();
					break;
				}
			}
		}
	}

	if (studentExists && validPassword)
	{
		cout << "Bemvindo, " << nome << endl;
		system("PAUSE");
		menuAluno(username);
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

void newStudent()
{
	string codigo;
	string password;
	string email;
	string nome;
	string estatuto;
	int estatuto_int = -1;
	stringstream estatutos;
	Estudante * estudante_tmp;

	system("CLS");
	cin.ignore();
	cout << "Codigo: ";
	getline(cin, codigo);
	if (codigo.find("@") != string::npos)
		codigo.erase(codigo.begin() + codigo.find("@"), codigo.end());
	cout << "Password: ";
	getline(cin, password);
	cout << "Email: ";
	getline(cin, email);
	cout << "Nome: ";
	getline(cin, nome);
	cout << "Estatuto: ";
	system("PAUSE");

	for (Estudante::Estatutos::iterator i = Estudante::estatutos.begin(); i != Estudante::estatutos.end(); i++)
		{
			if (i == Estudante::estatutos.begin())
				estatutos << i->second;
			else
				estatutos << ',' << i->second;
		}
	estatuto_int = getMenu(estatutos.str());
	estatuto_int--;

	estudante_tmp = new Estudante(codigo, password, email, nome, estatuto_int);
	feup.getCursos()[0]->addEstudante(estudante_tmp);
	cout << "Estudante criado com sucesso\n";
	system("PAUSE");
}

int main()
{
	Curso mieic, mieec;
	mieic.readData("mieic.txt");
	feup.addCurso(&mieic);
	mieec.readData("mieec.txt");
	feup.addCurso(&mieec);

	//system("mode 120,40");
	HWND console = GetConsoleWindow();
	MoveWindow(console, 100, 100, 1200, 700, TRUE);

	int mainMenu = -1;
	while (mainMenu != 3) {
		system("CLS");
		mainMenu = getMenu("Login,Registar,Sair,Sair e guardar alteracoes");
		switch (mainMenu) {
		case 1:
			try {
				//bypass login() for testing purposes
				menuAluno("up201405308");
				//login();
			}
			catch (EstudanteInvalido &est) {
				est.usernameInvalido();
			}
			catch (PasswordInvalida &pass) {
				pass.passwordInvalida();
			}
			break;
		case 2:
			newStudent();
			break;
		case 4:
			mieic.saveData("mieic_out.txt");
			mieec.saveData("mieec_out.txt");
			mainMenu = 3;
			break;
		default:
			break;
		}
	}

	return 0;
}
