#ifndef FENETREPRINCIPAKE_H
#define FENETREPRINCIPAKE_H

#include <QMainWindow>
#include <QFileDialog>
#include <qmessagebox.h>
#include "Automate/automate.h"
#include "Automate/analyseurSyntaxique.h"
#include <string>
using namespace std;

namespace Ui {
class fenetrePrincipake;
}

class fenetrePrincipake : public QMainWindow {

    Q_OBJECT
    AnalyseurSyntaxique analyseurSyntaxique;

public:
    explicit fenetrePrincipake(QWidget *parent = 0);
    ~fenetrePrincipake();

private:
    Ui::fenetrePrincipake *ui;
private slots :
    void slotChoisirUnFichierAutomate();
    void slotAfficherMessage(string texte);
};

#endif // FENETREPRINCIPAKE_H
