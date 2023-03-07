#include "Repository.h"

void Repository::descarcaDinFisier()
{

	
	std::ifstream fin(fileName);
	lista_melodii.clear();
	int id, rank;
	string titlu, artist;

	string linie;
	while (std::getline(fin, linie))
	{
		size_t pozitie_delimitator = linie.find_first_of(",");
		id = stoi(linie.substr(0, pozitie_delimitator));
		linie = linie.substr(pozitie_delimitator + 1, linie.length());

		pozitie_delimitator = linie.find_first_of(",");
		titlu = linie.substr(0, pozitie_delimitator);
		linie = linie.substr(pozitie_delimitator + 1, linie.length());

		pozitie_delimitator = linie.find_first_of(",");
		artist = linie.substr(0, pozitie_delimitator);
		linie = linie.substr(pozitie_delimitator + 1, linie.length());

		pozitie_delimitator = linie.find_first_of(",");
		rank = stoi(linie.substr(0, pozitie_delimitator));
		linie = linie.substr(pozitie_delimitator + 1, linie.length());

		Melodie melodie{ id, titlu, artist, rank };

		adaugaMelodie(melodie);

	}

	fin.close();

}

void Repository::incarcaInFisier()
{

	std::ofstream fout(fileName);

	for (auto &melodie : lista_melodii)
	{
		fout << melodie.toString() << "\n";

	}
	fout.close();

}

void Repository::adaugaMelodie(Melodie& melodie)
{
	for (auto& elem : lista_melodii)
	{
		if (elem.get_id() == melodie.get_id())
			throw exception();
	}
	lista_melodii.push_back(melodie);
	incarcaInFisier();

}

Melodie& Repository::cautaMelodie(int id)
{
	for (auto& elem : lista_melodii)
	{
		if (elem.get_id() == id)
			return elem;
	}

}

void Repository::stergeMelodie(int id)
{
	int i = 0;
	for (auto& elem : lista_melodii)
	{
		if (elem.get_id() == id)
			lista_melodii.erase(lista_melodii.begin() + i);
		i++;
	}
	incarcaInFisier();

}

vector<Melodie>& Repository::get_All()
{
	return lista_melodii;
}
