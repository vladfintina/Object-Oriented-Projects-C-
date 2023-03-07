#include "Repository.h"

void Repository::descarcaDinFisier()
{
	lista_tractoare.clear();
	ifstream fin(fileName);
	int id, nrRoti;
	string denumire, tip;
	string linie;
	while (getline(fin, linie))
	{
		size_t pozitieDelimitator = linie.find_first_of(",");
		id = stoi(linie.substr(0, pozitieDelimitator));
		linie = linie.substr(pozitieDelimitator + 1, linie.length());

		pozitieDelimitator = linie.find_first_of(",");
		denumire = linie.substr(0, pozitieDelimitator);
		linie = linie.substr(pozitieDelimitator + 1, linie.length());

		pozitieDelimitator = linie.find_first_of(",");
		tip = linie.substr(0, pozitieDelimitator);
		linie = linie.substr(pozitieDelimitator + 1, linie.length());

		pozitieDelimitator = linie.find_first_of(",");
		nrRoti = stoi(linie.substr(0, pozitieDelimitator));
		linie = linie.substr(pozitieDelimitator + 1, linie.length());

		Tractor tractor(id, denumire, tip, nrRoti);
		adaugaTractor(tractor);

	}

	fin.close();

}

void Repository::incarcaInFisier()
{
	ofstream fout(fileName);
	for(auto elem : lista_tractoare)
	{
		fout << elem.toString() << "\n";
	}

}

vector<Tractor>& Repository::getAll()
{
	return lista_tractoare;
}

void Repository::adaugaTractor(Tractor &tractor)
{
	for (auto elem : lista_tractoare)
	{
		if (elem.get_id() == tractor.get_id())
			throw exception("id existent!");
	}
	lista_tractoare.push_back(tractor);
	incarcaInFisier();

}

bool Repository::cautaTractor(int id)
{
	for (auto elem : lista_tractoare)
	{
		if (elem.get_id() == id)
			return true;
	}
	return false;
}



