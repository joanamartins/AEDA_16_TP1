#include "Reuniao.h"
#include "Estudante.h"
#include "Curso.h"

Reuniao::Reuniao()
{
}

Reuniao::~Reuniao()
{
}

Reuniao::Reuniao(Date d, string s, string desc) : data(d), studentID(s), descritivo(desc)
{
}

Date Reuniao::getDate() const
{
	return data;
}

string Reuniao::getStudent() const
{
	return studentID;
}

string Reuniao::getDesc() const
{
	return descritivo;
}

void Reuniao::setDate(Date d)
{
	data = d;
}

void Reuniao::setStu(string s)
{
	studentID = s;
}

void Reuniao::setDesc(string desc)
{
	descritivo = desc;
}

bool Reuniao::operator<(const Reuniao &that) const
{
	return this->data < that.data;
}

bool Reuniao::operator==(const Reuniao &that) const
{
	return this->data == that.data;
}

ostream& operator<<(ostream& out, const Reuniao &r)
{
	out << r.getDate().getDate() << '\t' << r.getStudent() << "\n\tDescricao: " << r.getDesc() << endl;
	return out;
}