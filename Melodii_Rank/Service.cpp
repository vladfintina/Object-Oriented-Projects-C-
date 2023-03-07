#include "Service.h"
#include "algorithm"

vector<Melodie> Service::get_All()
{
    auto lista_sortata = repository.get_All();
    sort(lista_sortata.begin(), lista_sortata.end(), [&](Melodie a, Melodie b) {
        return a.get_rank() < b.get_rank();
        });
    return lista_sortata;
}

int Service::filtrareRankEgal(Melodie& melodie)
{
    int nr = 0;
    auto lista = repository.get_All();
    for (auto &elem : lista)
    {
        if (elem.get_rank() == melodie.get_rank() && melodie.get_id() != elem.get_id())
            nr++;
    }
    return nr;
}

void Service::update(int id, string new_title, int new_rank)
{
    Melodie& melodie = repository.cautaMelodie(id);
    if (new_title != "")
        melodie.set_titlu(new_title);
    melodie.set_rank(new_rank);
    repository.incarcaInFisier();

}

int Service::nrMelodiiArtist(string& artist)
{
    int nr = 0;
    auto lista_cautare = repository.get_All();
    for (auto elem : lista_cautare)
    {
        if (elem.get_artist() == artist)
            nr++;
    }
    return nr;
}

void Service::stergeMelodie(int id)
{
    repository.stergeMelodie(id);
}

string Service::artistMelodie(int id)
{
    Melodie melodie = repository.cautaMelodie(id);
    return melodie.get_artist();
}


