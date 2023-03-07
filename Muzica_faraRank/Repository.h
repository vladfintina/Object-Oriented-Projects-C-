#pragma once
#include <vector>
#include <fstream>
#include "Song.h"

class Repository
{
private:
	string fileName;
	vector<Song> lista_melodii;
	void descarcaDinFisier();

public:
	Repository(string FileName) :fileName{ FileName } {
		descarcaDinFisier();
	}
	void incarcaInFisier();

	vector<Song> getAll();

	void addSong(Song& song);

	void deleteSong(int id);

};

