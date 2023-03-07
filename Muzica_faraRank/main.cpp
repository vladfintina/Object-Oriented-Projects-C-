#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repository{ "fisier.txt" };
    Service service{ repository };
    GUI w{service};
    w.show();
    return a.exec();
}
