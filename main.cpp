#include <iostream>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include "Curso.h"
#include "Ucurricular.h"
#include "Estudante.h"
#include "Menus.h"
#include "Exceptions.h"
using namespace std;

vector<Curso *> feup;

int main()
{
	Curso mieic, mieec;
	mieic.readData("mieic.txt");
	feup.push_back(&mieic);
	mieec.readData("mieec.txt");
	feup.push_back(&mieec);

	system("mode 160,80");
	//HWND console = GetConsoleWindow();
	//MoveWindow(console, 100, 100, 1200, 700, TRUE);

	for (size_t i = 0; i < feup[0]->getEstudantes().size(); i++)
	{
		feup[0]->getEstudantes()[i]->getDocente();
	}

	int mainMenu = -1;
	while (mainMenu != 4) {
		system("CLS");
		mainMenu = getMenu("Login estudantes,Novo estudante,Login docentes,Sair,Sair e guardar alteracoes");
		switch (mainMenu) {
		case 1:
			try {
				//bypass studentLogin() for testing purposes
				//feup[0]->getEstudantes()[1]->menu();
				studentLogin();
			}
			catch (EstudanteInvalido &est) {
				est.usernameInvalido();
			}
			catch (PasswordInvalida &pass) {
				pass.passwordInvalida();
			}
			break;
		case 2:
			feup[0]->newStudent();
			break;
		case 3:
			try {
				docLogin();
			}
			catch (DocenteInvalido &doc) {
				doc.siglaInvalida();
			}
			catch (PasswordInvalida &pass) {
				pass.passwordInvalida();
			}
			break;
		case 5:
			mieic.saveData("mieic_out.txt");
			mieec.saveData("mieec_out.txt");
			mainMenu = 4;
			break;
		default:
			break;
		}
	}

	return 0;
}
