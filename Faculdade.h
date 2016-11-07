#pragma once

#include "Curso.h"

class Faculdade {
	vector <Curso *> cursos;
public:
	void addCurso(Curso * curso) { cursos.push_back(curso); };
	vector <Curso *> getCursos() { return cursos; };
};