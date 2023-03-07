#include "Taskuri.h"
#include <QtWidgets/QApplication>
#include "Teste.h"
#include <iostream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
   // run_teste();
    Repository repository{ "fisier.txt" };
    Service s{ repository };
    GUI w{s};
    w.show();
    return a.exec();
}
