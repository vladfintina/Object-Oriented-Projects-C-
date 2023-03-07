#include "Service.h"

vector<Tractor> Service::getAll()
{
    auto lista_elemente = repository.getAll();
    sort(lista_elemente.begin(), lista_elemente.end(), [&](Tractor a, Tractor b) {
        return a.get_denumire() < b.get_denumire();
        });
    return lista_elemente;

}

int Service::sameType(Tractor& tractor)
{
    int nr = 0;
    auto lista = repository.getAll();
    for (auto elem : lista)
    {
        if (elem.get_tip() == tractor.get_tip())
            nr++;
    }
    return nr;
}

void Service::addTractor(int id, string denumire, string tip, int nrRoti)
{
    string exceptie = "";

    if (denumire == "")
        exceptie += "Denumirea nu poate fi vida!\n";
    if (tip == "")
        exceptie += "Tip nu poate fi vid\n";
    if (repository.cautaTractor(id) == true)
        exceptie += "Id existent!\n";

    if (exceptie != "")
        throw (exceptie);

    Tractor tractor{ id, denumire, tip, nrRoti };

    repository.adaugaTractor(tractor);


}

vector<string> Service::Types()
{
    auto lista = repository.getAll();
    vector<string> types;

    for (auto elem : lista)
    {
        if (find(types.begin(), types.end(), elem.get_tip()) == types.end())
            types.push_back(elem.get_tip());
    }
    return types;
}
