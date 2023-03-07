#pragma once
#include "Repository.h"
#include <algorithm>
#include <set>

class Observer {

public:
	virtual void update() = 0;
};

class Observable {

private:
	vector<Observer*> observers;

public:
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void removeObservers(Observer* obs) {
		observers.erase(remove(begin(observers), end(observers), obs));
	}

protected:
	void notify()
	{

		for (auto obs : observers)
		{
			obs->update();
		}
	}

};

class Service
{

private:
	Repository& repository;

public:
	Service(Repository& repository): repository{repository} {}

	vector<Produs> getAll();

	int nrVocale(Produs produs);

	void addProdus(int id, string nume, string tip, double pret);

	set<string> tipuriProdus();

	int typeNumber(string type);

};

