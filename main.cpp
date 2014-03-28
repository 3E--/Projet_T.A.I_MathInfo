#include "Gui/fenetrePrincipake.h"
#include <QApplication>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    fenetrePrincipake w;
    w.show();

    return a.exec();
}
