#include "Melodii_Rank.h"
#include <QtWidgets/QApplication>
#include "Teste.h"
#include <QDebug>
#include "Repository.h"
#include"Service.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    run_all();
    qDebug("Sfarsit teste\n");
    Repository repository("fisier.txt");
    Service service(repository);
    GUI w{service};
    w.show();
    return a.exec();
}
