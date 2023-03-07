#include "Service.h"

vector<Produs> Service::getAll()
{
    auto lista_sortare = repository.getAll();
    sort(lista_sortare.begin(), lista_sortare.end(), [&](Produs a, Produs b) {
        return a.get_pret() < b.get_pret();
        });
    return lista_sortare;
}

int Service::nrVocale(Produs produs)
{
    int nr = 0;
    string nume = produs.get_nume();
    for (int i = 0;i < nume.size();i++)
        if (nume[i] == 'a' || nume[i] == 'e' || nume[i] == 'i' || nume[i] == 'o' || nume[i] == 'u')
            nr++;
    return nr;
}

void Service::addProdus(int id, string nume, string tip, double pret)
{
    string exceptie = "";
    if (nume == "")
        exceptie += "Nume invalid\n";
    if (pret < 1 || pret>100)
        exceptie += "Pret invalid!\n";

    if (exceptie != "")
        throw (exceptie);

    Produs produs{ id, nume, tip, pret };
    try {
        repository.addProdus(produs);
    }
    catch (string ex) {
        exceptie = ex;
    }
    if (exceptie != "")
        throw(exceptie);


}

set<string> Service::tipuriProdus()
{
    set<string> types;
    auto lista_prod = repository.getAll();

    for (auto elem : lista_prod)
        types.insert(elem.get_tip());

    return types;


}

int Service::typeNumber(string type)
{
    auto lista_prod = repository.getAll();
    int nr = 0;
    for (auto elem : lista_prod)
        if (elem.get_tip() == type)
            nr++;
    return nr;
}
