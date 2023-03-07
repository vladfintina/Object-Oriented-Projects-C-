#pragma once
#include "Repository.h"
#include "Melodie.h"
#include <string>


class Service
{
private:
	Repository& repository;

public:
     Service(Repository &repository): repository{repository} {}

	 vector<Melodie> get_All();

	 int filtrareRankEgal(Melodie& melodie);

	 void update(int id, string new_title, int new_rank);

	 int nrMelodiiArtist(string& artist);

	 void stergeMelodie(int id);

	 string artistMelodie(int id);

};

