#pragma once

#include <string>

using namespace std;

class Tractor
{

private:
	int id;
	string denumire;
	string tip;
	int nrRoti;



public:

	Tractor(int id, string denumire, string tip, int nrRoti) : id{ id }, denumire{ denumire }, tip{ tip }, nrRoti{ nrRoti } {}

	int get_id()
	{
		return this->id;
	}

	string get_denumire()
	{
		return this->denumire;
	}

	string get_tip()
	{
		return this->tip;
	}

	int get_nrRoti()
	{
		return this->nrRoti;

	}

	string toString()
	{
		return to_string(this->id) + "," + this->denumire + "," +this->tip + "," + to_string(this->nrRoti);
	}

};

