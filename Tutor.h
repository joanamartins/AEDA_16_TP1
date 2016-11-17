#pragma once

#include <vector>
#include <string>
#include "Menus.h"
using namespace std;

extern vector<Curso *> feup;

class Curso;

class Tutor {

	string nome;
	string email;
	vector<string> estudantes;

public:
	Tutor() {};
	~Tutor() {};
	Tutor(string nome, string email);
	string getNome() const;
	string getEmail() const;
	vector<string> getEstudantes() const;


};
