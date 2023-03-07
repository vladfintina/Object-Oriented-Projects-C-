#include "Repo.h"

void Repository::descarcaDinFisier()
{
	ifstream fin(fileName);
	int id, nr, i;
	string descriere, stare;
	vector<string> programatori;
	string programator;
	while (fin >> id)
	{
		programatori.clear();
		fin >> descriere;
		fin >> nr;
		for (i = 0;i < nr;i++)
		{
			fin >> programator;
			programatori.push_back(programator);
		}
		fin >> stare;
		Task task(id, descriere, programatori, stare);
		lista_taskuri.push_back(task);

	}
	fin.close();

}

void Repository::incarcaInFisier()
{
	ofstream fout(fileName);
	for (auto task : lista_taskuri)
	{
		vector<string> lista_programatori{ task.get_programatori() };
		fout << task.get_id() << "\n";
		fout << task.get_descriere() << "\n";
		fout << lista_programatori.size() << "\n";
		for (auto programator : lista_programatori)
		{
			fout << programator << "\n";
		}
		fout << task.get_stare() << "\n";

	}
	fout.close();

}


void Repository::adaugareTask(Task& task)
{
	for (auto& elem : lista_taskuri)
	{
		if (elem.get_id() == task.get_id())
		{
			throw (1);
		}

	}
	lista_taskuri.push_back(task);
	incarcaInFisier();

}

void Repository::update_status(Task& task)
{
	for (auto &elem : lista_taskuri)
	{
		if (elem.get_id() == task.get_id())
		{
			elem.set_stare(task.get_stare());
			incarcaInFisier();
			return;
		}
	}
	

}

vector<Task>& Repository::getAll()
{
	
	return lista_taskuri;
}
