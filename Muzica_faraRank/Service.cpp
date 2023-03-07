#include "Service.h"

vector<Song> Service::getAll()
{
    vector<Song> lista_sortata = repository.getAll();
    sort(lista_sortata.begin(), lista_sortata.end(), [&](Song a, Song b) {
        return a.get_artist() < b.get_artist();
        });

    return lista_sortata;
}

int Service::nrSameArtist(Song song)
{
    int nr = 0;
    vector<Song> songs = repository.getAll();
    for (auto elem : songs)
    {
        if (elem.get_artist() == song.get_artist())
            nr++;

    }
    return nr - 1;
}

int Service::nrSameGenres(Song song)
{
    int nr = 0;
    vector<Song> songs = repository.getAll();
    for (auto elem : songs)
    {
        if (elem.get_gen() == song.get_gen())
            nr++;

    }
    return nr - 1;
}

void Service::addSong(string titlu, string artist, string gen)
{
    int ok = 1;
    while (ok == 1)
    {
        int id = rand() % 1000;
        try {
            Song song(id, titlu, artist, gen);
            repository.addSong(song);
            ok = 0;
        }
        catch(string ex){}
    }

}

void Service::deleteSong(int id)
{
    repository.deleteSong(id);
}
