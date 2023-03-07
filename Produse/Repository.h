#pragma once
#include <vector>
#include "Produs.h"
#include <fstream>

class Repository
{

private:
	string fileName;
	vector<Produs> lista_produse;
	void descarcaDinFisier();

public:
	Repository(string fileName) :fileName{ fileName } {
		descarcaDinFisier();
	}

	void incarcaInFisier();

	void addProdus(Produs produs);

	vector<Produs> getAll();



};

