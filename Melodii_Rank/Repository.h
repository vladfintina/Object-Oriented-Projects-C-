#pragma once
#include <string>
#include "Melodie.h"
#include <vector>
#include <fstream>

class Repository
{

private:
	string fileName;
	vector<Melodie> lista_melodii;
	
public:
	void descarcaDinFisier();
	void incarcaInFisier();

	Repository(string fileName):fileName{fileName}{
		descarcaDinFisier();
	}

	void adaugaMelodie(Melodie& melodie);

	Melodie& cautaMelodie(int id);

	void stergeMelodie(int id);

	vector<Melodie>& get_All();



};

