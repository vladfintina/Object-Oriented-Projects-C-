#pragma once
#include <algorithm>
#include "Repository.h"


class Service
{
private:
	Repository& repository;


public:
	Service(Repository& repository): repository{repository} {}

	vector<Tractor> getAll();

	int sameType(Tractor& tractor);

	void addTractor(int id, string denumire, string tip, int nrRoti);

	vector<string> Types();

};

