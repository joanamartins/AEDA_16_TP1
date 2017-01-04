#include "Turma.h"

int Turma::idg = 0;

bool Turma::operator<(const Turma& that) const {
	return this->getVac() < that.getVac(); 
}

void Turma::decVac()
{
	vagasMin--;
	for (size_t i = 0; i < vagas.size(); i++) 
	{ 
		vagas[i].second--; 
	}
}