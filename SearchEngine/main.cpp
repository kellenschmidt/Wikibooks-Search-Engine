#include "guiuserinterface.h"
#include <QApplication>
#include <fstream>

int main(int argc, char *argv[])
{
    ofstream o("nagg.txt");
    o.close();
    QApplication a(argc, argv);
    GUIUserInterface w;

    w.show();


    return a.exec();
}
