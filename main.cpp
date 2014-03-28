#include "fenetreprincipale.h"
#include <QApplication>
#include "automate.h"

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    fenetrePrincipale w;
    w.show();

    return a.exec();
}
