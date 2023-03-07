#include "Repository.h"

void Repository::descarcaDinFisier()
{
	ifstream fin(fileName);
	lista_produse.clear();

	int id;
	string nume, tip;
	double pret;

	string linie;

	while (getline(fin, linie))
	{
		size_t pozitieDelimitator = linie.find_first_of(",");
		id = stoi(linie.substr(0, pozitieDelimitator));
		linie = linie.substr(pozitieDelimitator + 1,linie.length());

		pozitieDelimitator = linie.find_first_of(",");
		nume = linie.substr(0, pozitieDelimitator);
		linie = linie.substr(pozitieDelimitator + 1, linie.length());

		pozitieDelimitator = linie.find_first_of(",");
		tip = linie.substr(0, pozitieDelimitator);
		linie = linie.substr(pozitieDelimitator + 1, linie.length());

		pozitieDelimitator = linie.find_first_of(",");
		pret = stod(linie.substr(0, pozitieDelimitator));
		linie = linie.substr(pozitieDelimitator + 1, linie.length());
		
		Produs produs(id, nume, tip, pret);
		lista_produse.push_back(produs);

	}

	fin.close();

}

void Repository::incarcaInFisier()
{
	ofstream fout(fileName);
	for (auto elem : lista_produse)
	{
		fout << elem.toString() << "\n";
	}

	fout.close();
}

void Repository::addProdus(Produs produs)
{
	string exceptie = "Id inexistent";
	for (auto elem : lista_produse)
	{
		if (elem.get_id() == produs.get_id())
		{
			throw (exceptie);
		}
	}
	lista_produse.push_back(produs);
	incarcaInFisier();


}

vector<Produs> Repository::getAll()
{
	return lista_produse;
}


