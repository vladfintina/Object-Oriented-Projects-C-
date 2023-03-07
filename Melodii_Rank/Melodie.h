#pragma once
#include <string>
using namespace std;


class Melodie
{

private:
	int id;
	string titlu;
	string artist;
	int rank;

public:

	Melodie(int id, string titlu, string artist, int rank):id{id}, titlu{titlu}, artist{artist}, rank{rank}{}

	int get_id()
	{
		return this->id;
	}

	string get_titlu()
	{
		return this->titlu;
	}

	string get_artist()
	{
		return this->artist;
	}

	int get_rank()
	{
		return this->rank;
	}

	void set_rank(int new_rank)
	{
		rank = new_rank;
	}

	void set_titlu(string new_title)
	{
		titlu = new_title;
	}

	string toString()
	{
		return to_string(this->id) + "," + this->titlu + "," + this->artist + "," + to_string(this->rank);
	}
};

