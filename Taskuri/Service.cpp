#include "Service.h"
#include <algorithm>

void Service::adaugaTask(int id, string &descriere, string& prog1, string& prog2, string& prog3, string& prog4, string& stare) {
	vector<string> programatori;
	if (descriere == "")
		throw (1);
	if (prog1 != "")
		programatori.push_back(prog1);
	if (prog2 != "")
		programatori.push_back(prog2);
	if (prog3 != "")
		programatori.push_back(prog3);
	if (prog4 != "")
		programatori.push_back(prog4);
	if (programatori.size() == 0)
		throw (1);
	if (stare != "Open" && stare != "Inprogress" && stare != "Closed")
		throw (1);
	Task task{ id, descriere, programatori, stare };
	repo.adaugareTask(task);
	notify();

}

vector<Task> Service::cautaTaskProg(string prog) {
	vector<Task> rezultat;
	for (auto& elem : repo.getAll())
	{
		vector<string> programatori = elem.get_programatori();
		for (auto& p : programatori)
		{
			if (p == prog)
			{
				rezultat.push_back(elem);
				break;
			}
		}
	}
	return rezultat;

}

void Service::updateStatus(int id, string stare) {
	vector<string> programatori;
	string descriere = "";
	/*if (stare != "Open" && stare != "Inprogress" && stare != "Closed")
		throw (1);*/
	Task task{ id, descriere, programatori, stare };
	repo.update_status(task);
	notify();

}

vector<Task> Service::filtrareStare(string& stare)
{
	vector<Task> rezultat;
	for (auto& elem : repo.getAll())
	{
		if (elem.get_stare() == stare)
		{
			rezultat.push_back(elem);
		}
	}
	return rezultat;
}

vector<Task> Service::getAll() {

	vector<Task> tasks = repo.getAll();
	sort(tasks.begin(), tasks.end(), [&](Task a, Task b) {return a.get_stare() < b.get_stare(); });
	return tasks;

}