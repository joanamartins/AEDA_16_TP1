#include <iostream>
#include <fstream>
#include <windows.h>
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
	vector<pair<string, int>> resultados = feup.getCursos()[i]->getEstudantes()[j]->getResultados();

	int ano, semestre;
	int menuAluno = -1, menuV, menuVUC;
	while (menuAluno != 4) {
		menuAluno = getMenu("Visualizar,Editar dados,Inscricao em UCs,Logout", 1, 4);
		switch (menuAluno) {
		case 1:
			menuV = -1;
			while (menuV != 3) {
				menuV = getMenu("Dados,Unidades curriculares,Voltar atras", 1, 3);
				switch (menuV) {
				case 1:
					menuV = 3;
					system("CLS");
					cout << "Codigo\t\t\tPassword\tEmail\t\t\tNome\t\t\t\t\tTrabalhador\n";
					cout << feup.getCursos()[i]->getEstudantes()[j]->info();
					system("PAUSE");
					break;
				case 2:
					menuV = 3;
					menuVUC = -1;
					while (menuVUC != 5) {
						menuVUC = getMenu("Todas,Por ano/semestre,Por nome,Por resultado,Voltar atras", 1, 5);
						switch (menuVUC) {
						case 1:
							menuVUC = 5;
							system("CLS");
							cout << "Codigo da UC\tNome\t\t\t\t\t\t\t\t\tResultado\n";
							for (vector<pair<string, int>>::const_iterator k = resultados.begin(); k != resultados.end(); k++)
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
							system("PAUSE");
							break;
						case 2:
							menuVUC = 5;
							cout << "Ano: ";
							ano = getInt(1, 5);
							cout << "Semestre: ";
							semestre = getInt(1, 2);
							cout << "Codigo\tSigla\tNome\t\tResultado\n"; //falta formatar
							for (int k = 0; k < feup.getCursos()[i]->getEstudantes()[j]->getResultados().size(); k++)
							{
								for (int l = 0; l < feup.getCursos()[i]->getUCs().size(); l++)
								{
									if (feup.getCursos()[i]->getUCs()[l]->getCodigo() == feup.getCursos()[i]->getEstudantes()[j]->getResultados()[k].first)
									{
										if (feup.getCursos()[i]->getUCs()[l]->getAno() == ano && feup.getCursos()[i]->getUCs()[l]->getSemestre() == semestre)
										{
											cout << feup.getCursos()[i]->getUCs()[l]->getCodigo() << '\t' <<
												feup.getCursos()[i]->getUCs()[l]->getSigla() << '\t' <<
												feup.getCursos()[i]->getUCs()[l]->getNome() << '\t' <<
												feup.getCursos()[i]->getEstudantes()[j]->getResultados()[k].second << endl;
										}
									}
								}
							}
							system("PAUSE");
							break;
						case 3:
							menuVUC = 5;
							break;
						case 4:
							menuVUC = 5;
							break;
						}
					}
					break;
				}
		case 2:
			break;
		case 3:
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

	for (Estudante::Estatutos::iterator i = Estudante::estatutos.begin(); i != Estudante::estatutos.end(); i++)
		{
			if (i == Estudante::estatutos.begin())
				estatutos << i->second;
			else
				estatutos << ',' << i->second;
		}
	estatuto_int = getMenu(estatutos.str(), 1, 10);
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

	system("mode 120,40");

	int mainMenu = -1;
	while (mainMenu != 3) {
		mainMenu = getMenu("Login,Registar,Sair,Sair e guardar alteracoes", 1, 4);
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
