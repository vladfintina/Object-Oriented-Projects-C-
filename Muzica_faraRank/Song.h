#pragma once
#include <string>

using namespace std;

class Song
{
private:
	int id;
	string titlu;
	string artist;
	string gen;

public:
	Song(int id, string titlu, string artist, string gen): id{id}, titlu{titlu}, artist{artist}, gen{gen}{}

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

	string get_gen()
	{
		return this->gen;
	}

	string toString() { return to_string(this->id) + "," + this->titlu + "," + this->artist + "," + this->gen; }

};

