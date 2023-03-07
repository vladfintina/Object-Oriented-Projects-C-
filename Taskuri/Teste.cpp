#include "Teste.h"
#include <assert.h>
#include <string>
#include <vector>
#include <iostream>
#include <QtCore/qlogging.h>
#include <qdebug.h>

void testeaza_creare_task()
{
	const int id{ 1 };
	string descriere{ "a" };
	string stare{ "b" };
	vector<string>prog;
	prog.push_back("vlad");
	prog.push_back("flaviu");

	Task task(id, descriere, prog, stare);
	assert(id == task.get_id());
	assert(descriere == task.get_descriere());
	assert(stare == task.get_stare());
	vector<string> prog_verificare{ task.get_programatori() };
	assert("vlad" == prog_verificare[0]);
	
}

void test_repo()
{
	int id1{ 1 };
	int id2{ 3 };
	string descriere = "asdsa";
	string open = "Open";
	string inprogress = "Inprogress";
	string closed = "Closed";
	Repository repo("fisiertest.txt");
	auto lista_t = repo.getAll();
	assert(lista_t.size() == 2);
	assert(lista_t[0].get_stare() == "Open");
	assert(lista_t[1].get_id() == 2);

	vector<string>prog;
	prog.push_back("vlad");
	prog.push_back("flaviu");

	try {
		Task task{ id1,descriere, prog, closed };
		repo.adaugareTask(task);
		assert(false);
	}
	catch (int ex) {
		assert(true);
	}

	Task task2{ id2, descriere, prog, inprogress };
	repo.adaugareTask(task2);
	lista_t = repo.getAll();
	assert(lista_t.size() == 3);

	Task task3{ id2, descriere, prog, closed };
	repo.update_status(task3);

	lista_t = repo.getAll();
	assert(lista_t[2].get_stare() == "Closed");


}
void test_service()
{

	/*std::ofstream ofs;
	ofs.open("fisiertest.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();*/
	const int id{ 10 };
	string descriere{ "a" };
	string stare{ "Open" };
	//Task task(id, descriere, prog, stare);

	Repository repo{"fisiertest.txt"};
	Service service{ repo };
	string prog1 = "vlad";
	string prog2 = "flaviu";
	string prog3 = "";
	string prog4 = "";
	string descriere_empty = "";
	string stare_gresita = "ksd";
	service.adaugaTask(id,descriere, prog1, prog2, prog3, prog4, stare);

	assert(service.getAll().size() == 4);

	try {
		service.adaugaTask(2, descriere_empty, prog1, prog2, prog3, prog4, stare);
		assert(false);
	}
	catch (int a)
	{
		assert(true);
	}

	try {
		service.adaugaTask(2, descriere, prog4, prog3, prog3, prog4, stare);
		assert(false);
	}
	catch (int ex)
	{
		assert(true);
	}
	try {
		service.adaugaTask(2, descriere, prog1, prog2, prog3, prog4, stare_gresita);
		assert(false);
	}
	catch (int ex)
	{
		assert(true);
	}
	string Closed = "Closed";
	service.updateStatus(10, Closed);
	auto lista_elem = service.getAll();
	assert(lista_elem[0].get_stare() == "Closed");


}


void run_teste()
{
	testeaza_creare_task();
	test_repo();
	test_service();
	//cout << "Sfarsit teste...";

}
