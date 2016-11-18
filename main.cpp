#include <iostream>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include "Curso.h"
#include "Ucurricular.h"
#include "Estudante.h"
#include "Menus.h"
using namespace std;

vector<Curso *> feup;

int main()
{
	Curso mieic, mieec;
	mieic.readData("mieic.txt");
	feup.push_back(&mieic);
	mieec.readData("mieec.txt");
	feup.push_back(&mieec);

	//system("mode 120,40");
	HWND console = GetConsoleWindow();
	MoveWindow(console, 100, 100, 1200, 700, TRUE);

	for (size_t i = 0; i < feup[0]->getEstudantes().size(); i++)
	{
		feup[0]->getEstudantes()[i]->getDocente();
	}

	int mainMenu = -1;
	while (mainMenu != 3) {
		system("CLS");
		mainMenu = getMenu("Login,Registar,Sair,Sair e guardar alteracoes");
		switch (mainMenu) {
		case 1:
			try {
				//bypass login() for testing purposes
				//feup[0]->getEstudantes()[1]->menu();
				login();
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
