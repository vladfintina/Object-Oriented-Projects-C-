#include "Repository.h"

void Repository::descarcaDinFisier()
{
	ifstream fin(fileName);
	lista_melodii.clear();
	int id;
	string titlu, artist, gen;

	string linie;

	while (getline(fin, linie))
	{
		size_t pozitieDelimitator = linie.find_first_of(",");
		id = stoi(linie.substr(0, pozitieDelimitator));
		linie = linie.substr(pozitieDelimitator + 1, linie.length());

		pozitieDelimitator = linie.find_first_of(",");
		titlu = linie.substr(0, pozitieDelimitator);
		linie = linie.substr(pozitieDelimitator + 1, linie.length());

		pozitieDelimitator = linie.find_first_of(",");
		artist = linie.substr(0, pozitieDelimitator);
		linie = linie.substr(pozitieDelimitator + 1, linie.length());

		pozitieDelimitator = linie.find_first_of(",");
		gen = linie.substr(0, pozitieDelimitator);
		linie = linie.substr(pozitieDelimitator + 1, linie.length());

		Song song(id, titlu, artist, gen);

		lista_melodii.push_back(song);

	}

	fin.close();
}

void Repository::incarcaInFisier()
{
	ofstream fout(fileName);

	for (auto elem : lista_melodii)
	{
		fout << elem.toString() << "\n";
	}

	fout.close();

}

vector<Song> Repository::getAll()
{
	return lista_melodii;
}

void Repository::addSong(Song& song)
{
	string eroare = "Id inexistent!";
	for (auto elem : lista_melodii)
	{
		if (elem.get_id() == song.get_id())
			throw eroare;
	}

	lista_melodii.push_back(song);
	incarcaInFisier();

}

void Repository::deleteSong(int id)
{
	for (int i = 0; i < lista_melodii.size();i++)
	{
		if (lista_melodii.at(i).get_id() == id)
		{
			lista_melodii.erase(lista_melodii.begin() + i);
		
		}
		

	}
	incarcaInFisier();

}



