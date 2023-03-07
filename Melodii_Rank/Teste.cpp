#include "Teste.h"
#include <string>
#include <assert.h>
#include <vector>

using namespace std;
void test_creeaza_melodie()
{
	int id = 1;
	string artist = "Azteca";
	string titlu = "VVS";
	int rank = 0;

	Melodie melodie(id, titlu, artist, rank);

	assert(melodie.get_id() == id);
	assert(melodie.get_titlu() == titlu);
	assert(melodie.get_artist() == artist);
	assert(melodie.get_rank() == rank);


}


void run_all()
{
	test_creeaza_melodie();

}