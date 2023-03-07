#pragma once
#include "Repository.h"
#include <algorithm>

class Service
{
private:
	Repository& repository;;

public:
	Service(Repository& repository): repository{repository} {}

	vector<Song> getAll();

	int nrSameArtist(Song song);

	int nrSameGenres(Song song);

	void addSong(string titlu, string artist, string gen);

	void deleteSong(int id);
};

