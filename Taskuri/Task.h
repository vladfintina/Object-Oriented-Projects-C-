#pragma once
#include <string>
#include <vector>
using namespace std;

class Task {

private:
	int id;
	string descriere;
	string stare;
	vector<string> programatori;

public:
	Task(int id, string& descriere, vector<string>& prog, string& stare) : id{ id }, descriere{ descriere }, programatori{ prog }, stare{ stare }{}
	
	//returneaza id
	int get_id()
	{
		return id;
	}

	string get_descriere()
	{
		return descriere;
	}

	string get_stare()
	{
		return stare;

	}

	vector<string> get_programatori()
	{
		return programatori;

	}

	void set_stare(string st)
	{
		 stare = st;
	}



};