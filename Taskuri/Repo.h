#pragma once
#include <vector>
#include <string>
#include "Task.h"
#include <fstream>
using namespace std;


class Repository{

private:
	vector<Task> lista_taskuri;
	string fileName;
	void descarcaDinFisier();
	void incarcaInFisier();

public:

	Repository(const string fileName) : fileName{ fileName } {
		descarcaDinFisier();

	};

	void adaugareTask(Task& task);

	void update_status(Task& task);

	vector<Task>& getAll();




};