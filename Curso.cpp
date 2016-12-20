#include "Curso.h"

Curso::Curso()
{
	priority_queue<Turma *> ttmp;
	for (int i = 0; i < 5; i++)
	{
		turmas.push_back(ttmp);
	}
}

vector <Ucurricular *> Curso::getUCs() const 
{ 
	return ucurriculares; 
}

vector <Optativa *> Curso::getOpts() const
{
	return optativas;
}

vector <Estudante *> Curso::getEstudantes() const
{
	return estudantes;
}

vector <Docente *> Curso::getDocentes() const
{
	return docentes;
}

int Curso::getAno(string codigo)
{
	for (vector<Ucurricular *>::iterator i = ucurriculares.begin(); i < ucurriculares.end(); i++)
		if (codigo == (*i)->getCodigo())
			return (*i)->getAno();
	return -1;
}

int Curso::getSemestre(string codigo)
{
	for (vector<Ucurricular *>::iterator i = ucurriculares.begin(); i < ucurriculares.end(); i++)
		if (codigo == (*i)->getCodigo())
			return (*i)->getSemestre();
	return -1;
}


void Curso::addUC(Ucurricular *uc) 
{ 
	ucurriculares.push_back(uc); 
}

void Curso::addUCopt(Optativa *opt)
{
	optativas.push_back(opt);
}

void Curso::addEstudante(Estudante *est)
{
	estudantes.push_back(est);
}

void Curso::addDocente(Docente *doc)
{
	docentes.push_back(doc);
}

int Curso::getEstudanteAno(Estudante * est) const
{
	int id = sequentialSearch(getEstudantes(), est);
	int ret = 0;
	for (size_t i = 0; i < estudantes[id]->getResultados().size(); i++)
	{
		for (size_t j = 0; j < ucurriculares.size(); j++)
		{
			if (estudantes[id]->getResultados()[i].first == ucurriculares[j]->getCodigo() && ucurriculares[j]->getAno() > ret)
			{
				ret = ucurriculares[j]->getAno();
			}
		}
	}
	return ret + 1;
}

void Curso::setUCs(const vector <Ucurricular *> &ucs)
{
	for (size_t i = 0; i < ucurriculares.size(); i++)
	{
		for (size_t j = 0; j < ucs.size(); j++)
		{
			if (ucurriculares[i]->getCodigo() == ucs[j]->getCodigo())
			{
				ucurriculares[i] = ucs[j];
			}
		}
	}
}

void Curso::newStudent()
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
	codigo = "up";
	codigo.append(to_string(Estudante::newCodigo));
	Estudante::newCodigo++;
	cout << "Email: ";
	getline(cin, email);
	try
	{
		validEmail(email);
	}
	catch (EmailInvalido &ema) {
		ema.emailInvalido();
		return;
	}

	cout << "Password: ";
	getline(cin, password);
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
	estudante_tmp->getDocente();
	addEstudante(estudante_tmp);
	cout << "Estudante criado com sucesso:\n";
	cout << "Codigo\t\t\tPassword\tEmail\t\t\tNome\t\t\t\t\tEstatuto\n";
	cout << estudante_tmp->info();
	system("PAUSE");
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
	int i = 0;
	string areaCientifica;
	Ucurricular *uc_tmp = new Ucurricular;
	Optativa *opt_tmp = new Optativa;
	Estudante *est_tmp = new Estudante;
	Docente *doc_tmp = new Docente;
	vector<Turma *> ttmp;
	for (size_t i = 0; i < 8; i++)
	{
		ttmp.push_back(new Turma());
	}

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
		if (line == "Optativas")
			break;
		else if (line.find("Ano") < 7)
		{
			if (ano > 0) 
			{
				for (size_t i = 0; i < ttmp.size(); i++)
				{
					turmas[ano - 1].push(ttmp[i]);
				}
				ttmp.clear();
				for (size_t i = 0; i < 8; i++)
				{
					ttmp.push_back(new Turma());
				}
			}
			ano++;
			semestre -= 2;
		}
		else if (line.find("Semestre") < 7)
		{
			semestre++;
		}
		else
		{
			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			codigo = section;
			for (size_t i = 0; i < ttmp.size(); i++)
			{
				ttmp[i]->addUC(codigo, 20);
			}
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
			//section.erase(section.begin() + section.find("\t"), section.end());
			creditos = stof(section);
			//line.erase(line.begin(), line.begin() + line.find("\t") + 1);

			//section = line;
			//vagas = stoi(section);

			uc_tmp = new Ucurricular(codigo, sigla, nome, creditos, ano, semestre);
			addUC(uc_tmp);
		}
	}

	for (size_t i = 0; i < ttmp.size(); i++)
	{
		turmas[ano - 1].push(ttmp[i]);
	}

	getline(curso, line);
	getline(curso, line);
	ano = 3;
	semestre = 3;
	while (getline(curso, line) && line.length() > 0) {
		if (line == "Docentes")
			break;
		else if (line.find("Ano") < 7)
		{
			ano++;
			semestre -= 2;
		}
		else if (line.find("Semestre") < 7)
		{
			semestre++;
		}
		else
		{
			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			codigo = section;
			line.erase(line.begin(), line.begin() + line.find("\t") + 2);

			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			sigla = section;
			line.erase(line.begin(), line.begin() + line.find("\t") + 1);

			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			areaCientifica = section;
			line.erase(line.begin(), line.begin() + line.find("\t") + 1);

			while (line[0] == '\t')
				line.erase(line.begin(), line.begin() + 1);

			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			nome = section;
			line.erase(line.begin(), line.begin() + line.find("\t") + 1);

			while (line[0] == '\t')
				line.erase(line.begin(), line.begin() + 1);

			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			creditos = stof(section);
			line.erase(line.begin(), line.begin() + line.find("\t") + 1);

			section = line;
			vagas = stoi(section);

			opt_tmp = new Optativa(codigo, sigla, nome, creditos, vagas, ano, semestre, areaCientifica);
			addUCopt(opt_tmp);
		}
	}

	getline(curso, line);
	getline(curso, line);
	while (getline(curso, line) && line.length() > 0)
	{
		if (line == "Estudantes")
			break;
		else
		{
			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			sigla = section;
			line.erase(line.begin(), line.begin() + line.find("\t") + 2);

			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			codigo = section;
			line.erase(line.begin(), line.begin() + line.find("\t") + 2);

			section = line;
			section.erase(section.begin() + section.find("\t"), section.end());
			email = section;
			line.erase(line.begin(), line.begin() + line.find("\t") + 1);

			section = line;
			i = 0;
			while (section[i] == '\t')
				section.erase(section.begin() + i);
			//section.pop_back();
			nome = section;

			doc_tmp = new Docente(sigla, stoi(codigo), email, nome);
			addDocente(doc_tmp);
		}
	}

	getline(curso, line);
	getline(curso, line);
	while (getline(curso, line) && line.length() > 0) {
		section = line;
		section.erase(section.begin() + section.find("\t"), section.end());
		codigo = section;
		section.erase(section.begin(), section.begin() + 2);
		if (stoi(section) >= Estudante::newCodigo)
			Estudante::newCodigo = stoi(section) + 1;
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
			line.erase(line.begin(), line.begin() + line.find("\t") + 2);
			resultado = stoi(line);
			est_tmp->addUC(codigo, resultado);

			getline(curso, line);
		}
		//est_tmp->getDocente();
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
	if (getUCs().size() >= 0)
	{
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
			output << getUCs()[i]->info('\n');
		}
	}
	if (getDocentes().size() > 0)
	{
		output << "\nDocentes\nSigla\tCodigo\tEmail\t\t    Nome\n";
		for (size_t i = 0; i < getDocentes().size(); i++)
		{
			output << getDocentes()[i]->info();
		}
	}
	if (getEstudantes().size() > 0)
	{
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
}