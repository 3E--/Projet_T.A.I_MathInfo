#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include "analysesyntaxique.h"
#include <QMessageBox>

#include <QStandardItemModel>

namespace Ui {
class fenetrePrincipale;
}

class fenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit fenetrePrincipale(QWidget *parent = 0);
    ~fenetrePrincipale();

private:
    void afficherLaTableDeTransitionDeLAutomate(Automate &automate);
    Ui::fenetrePrincipale *ui;
};

#endif // FENETREPRINCIPALE_H
