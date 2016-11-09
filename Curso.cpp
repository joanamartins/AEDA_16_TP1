#include "Curso.h"

Curso::Curso(string sigla, string nome)
{
	this->sigla = sigla;
	this->nome = nome;
}

vector <Ucurricular *> Curso::getUCs() const 
{ 
	return ucurriculares; 
}

vector <Estudante *> Curso::getEstudantes() const
{
	return estudantes;
}

int Curso::getAno(string codigo)
{
	for (vector<Ucurricular *>::iterator i = ucurriculares.begin(); i < ucurriculares.end(); i++)
		if (codigo == (*i)->getCodigo())
			return (*i)->getAno();
}

int Curso::getSemestre(string codigo)
{
	for (vector<Ucurricular *>::iterator i = ucurriculares.begin(); i < ucurriculares.end(); i++)
		if (codigo == (*i)->getCodigo())
			return (*i)->getSemestre();
}


void Curso::addUC(Ucurricular *uc) 
{ 
	ucurriculares.push_back(uc); 
}

void Curso::addEstudante(Estudante *est)
{
	estudantes.push_back(est);
}

void Curso::decreaseVacancy(string codigo)
{
	for (vector<Ucurricular *>::iterator i = ucurriculares.begin(); i < ucurriculares.end(); i++)
		if (codigo == (*i)->getCodigo())
			(*i)->decreaseVacancy();
}

void Curso::readData(string file)
{
	string line;
	string section;

	string curso_sigla;
	string curso_nome;

	string codigo;
	string sigla;
	string nome;
	string email;
	unsigned long password;
	int estatuto;
	int resultado;
	float creditos;
	int vagas;
	int ano = 0;
	int semestre = 2;
	string areaCientifica = "test area";
	Ucurricular *uc_tmp = new Ucurricular;
	Estudante *est_tmp = new Estudante;

	ifstream curso;
	curso.open(file);
	if (!(curso.is_open()))
	{
		cout << "Invalid file\n";
		return;
	}

	getline(curso, line);
	section = line;
	section.erase(section.begin() + section.find(' '), section.end());
	curso_sigla = section;

	section = line;
	section.erase(section.begin(), section.begin() + section.find(" - ") + 3);
	curso_nome = section;

	this->sigla = curso_sigla;
	this->nome = curso_nome;

	getline(curso, line);
	getline(curso, line);

	while (getline(curso, line) && line.length() > 0) {
		if (line.find("Ano") != string::npos)
		{
			ano++;
			semestre -= 2;
		}
		else if (line.find("Semestre") != string::npos)
		{
			semestre++;
		}
		else
		{
			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			codigo = section;
			line.erase(line.begin(), line.begin() + line.find("\t") + 1);

			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			sigla = section;
			line.erase(line.begin(), line.begin() + line.find("\t") + 1);

			section = line;
			section.erase(section.begin() + section.find("  "), section.end());
			nome = section;
			line.erase(line.begin(), line.begin() + line.find("  ") + 1);

			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			creditos = stof(section);
			line.erase(line.begin(), line.begin() + line.find("\t") + 1);

			section = line;
			vagas = stoi(section);
			
			uc_tmp = new Ucurricular(codigo, sigla, nome, creditos, vagas, ano, semestre, areaCientifica);
			addUC(uc_tmp);
		}
	}

	getline(curso, line);
	getline(curso, line);
	while (getline(curso, line)) {
		section = line;
		section.erase(section.begin() + section.find("\t"), section.end());
		codigo = section;
		line.erase(line.begin(), line.begin() + line.find("\t") + 2);
		
		section = line;
		section.erase(section.begin() + section.find("\t"), section.end());
		password = stoi(section);
		line.erase(line.begin(), line.begin() + line.find("\t") + 1);
		
		section = line;
		section.erase(section.begin() + section.find("\t"), section.end());
		email = section;
		line.erase(line.begin(), line.begin() + line.find("\t") + 1);
		
		section = line;
		section.erase(section.begin() + section.find("  "), section.end());
		nome = section;
		line.erase(line.begin(), line.begin() + line.find("  ") + 1);

		section = line;
		estatuto = stoi(section);

		est_tmp = new Estudante(codigo, password, email, nome, estatuto);

		getline(curso, line);
		getline(curso, line);
		while (line.find('\t') == 0) {
			line.erase(line.begin(), line.begin() + 1);
			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			codigo = section;
			decreaseVacancy(codigo);
			line.erase(line.begin(), line.begin() + line.find("\t") + 2);
			resultado = stoi(line);
			est_tmp->addUC(codigo, resultado);

			getline(curso, line);
		}
		addEstudante(est_tmp);
	}
	curso.close();
}

void Curso::saveData(string file) const
{
	ofstream output;
	output.open(file);
	int ano = 0;
	int semestre = 0;
	output << sigla << " - " << nome << "\n\n";
	output << "Codigo\t\tSigla\tNome\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tCreditos\tVagas\n";
	for (size_t i = 0; i < getUCs().size(); i++)
	{
		if (ano != getUCs()[i]->getAno())
		{
			ano = getUCs()[i]->getAno();
			semestre = 1;
			output << ano << (char)186 << " Ano\n" << semestre << (char)186 << " Semestre\n";
		}
		else if (semestre != getUCs()[i]->getSemestre())
		{
			semestre = 2;
			output << semestre << (char)186 << " Semestre\n";
		}
		output << getUCs()[i]->info();
	}
	if (getEstudantes().size() == 0)
		return;
	output << "\nEstudantes\nCodigo\t\t\tPassword\tEmail\t\t\t\t\tNome\t\t\t\t\t\t\t\t\tEstatuto\n";
	for (size_t i = 0; i < getEstudantes().size(); i++)
	{
		output << getEstudantes()[i]->info() << "Unidades curriculares frequentadas\n";
		vector<pair<string, int>> resultados = getEstudantes()[i]->getResultados();
		for (vector<pair<string, int>>::const_iterator j = resultados.begin(); j != resultados.end(); j++)
		{
			output << '\t' << (*j).first << "\t\t" << (*j).second << endl;
		}
		output << endl;
	}
}