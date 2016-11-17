#include <iostream>
#include <fstream>
#include <algorithm>
//#include <stdlib.h>
#include "Curso.h"
#include "Ucurricular.h"
#include "Estudante.h"
#include "Menus.h"
using namespace std;
#include <time.h>


vector<Curso *> feup;

int main()
{
	Curso mieic, mieec;
	mieic.readData("mieic.txt");
	feup.push_back(&mieic);
	mieec.readData("mieec.txt");
	feup.push_back(&mieec);

	int mainMenu = -1;
	while (mainMenu != 3) {
		system("CLS");
		mainMenu = getMenu("Login,Registar,Sair,Sair e guardar alteracoes");
		switch (mainMenu) {
		case 1:
			try {
				//bypass login() for testing purposes
				feup[0]->getEstudantes()[0]->menu();
				//login(feup);
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
