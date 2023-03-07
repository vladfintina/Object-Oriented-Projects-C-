#pragma once
#include "Repo.h"
#include "Task.h"
#include <string>

class Observer {

public:
	virtual void update() = 0;

};

class Observable {
private:
	std::vector<Observer*>observers;
public:

	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}
	void removeObserver(Observer* obs) {
		observers.erase(std::remove(begin(observers), end(observers), obs));
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



class Service :public Observable
{

private:
	Repository& repo;

public:
	Service(Repository& repo) : repo{repo}{}

	void adaugaTask(int id, string& descriere, string& prog1, string& prog2, string& prog3, string& prog4, string& stare);

	vector<Task> cautaTaskProg(string prog);

	void updateStatus(int id, string stare);

	vector<Task> filtrareStare(string& stare);

	vector<Task> getAll();
};