#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Tractor.h"

class Repository
{
private:
	string fileName;
	vector<Tractor> lista_tractoare;
	void descarcaDinFisier();

public:

	Repository(string fileName): fileName{fileName} {
		descarcaDinFisier();
	}

	void incarcaInFisier();

	vector<Tractor>& getAll();

	void adaugaTractor(Tractor &tractor);

	bool cautaTractor(int id);


};

