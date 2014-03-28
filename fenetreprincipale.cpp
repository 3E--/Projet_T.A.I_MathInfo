#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

fenetrePrincipale::fenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fenetrePrincipale)
{
    ui->setupUi(this);
    try {
        AnalyseSyntaxique a;
        Automate automate=a.genererUnAutomate("Fichier Automate/test1.txt");

        if(automate.estStandard()){
            ui->lineEdit_Standard->setText("Automate Standard");
            ui->pushButton_Standardiser->setEnabled(false);
        }
        else ui->lineEdit_Standard->setText("Automate Non Standard");

        if(automate.estDeterministe()){
            ui->lineEdit_Deterministe->setText("Automate Deterministe");
            ui->pushButton_Deterministe->setEnabled(false);
        }
        else ui->lineEdit_Deterministe->setText("Automate Non Deterministe");

        afficherLaTableDeTransitionDeLAutomate(automate);
    }
    catch (string &erreur) {
        QMessageBox msgBox;
        msgBox.setText(QString::fromUtf8(erreur.c_str()));
        msgBox.exec();
    }


}

void fenetrePrincipale::afficherLaTableDeTransitionDeLAutomate( Automate &automate){
    /**
     * !! afaire !! => AFFICHER LA TABLE DE TRANSITION QUI CORESPOND SI L'AUTOMATE EST DETERMINISTE
     *
     */
    list<string> *transitionsName= automate.getlistTransitionsName();
    list<string> *etatsName= automate.getlistEtatName();
    QStandardItemModel *model = new QStandardItemModel(etatsName->size(), transitionsName->size());
    // BOUCLE POUR PARCOURIR LA LISTE DES NOM DES TRANSITIONS DU DEBUT JUSQU'A LA FIN POUR LES AJOUTER A LA TABLE
    for(list<string>::iterator index = transitionsName->begin(); index != transitionsName->end(); index++) {
        static unsigned int i=0;
        model->setHeaderData(i,Qt::Horizontal,index->c_str());
        i++;
    }
    // BOUCLE POUR PARCOURIR LA LISTE DES NOM DES TRANSITIONS DU DEBUT JUSQU'A LA FIN POUR LES AJOUTER A LA TABLE
    for(list<string>::iterator index = etatsName->begin(); index != etatsName->end(); index++) {
        static unsigned int i=0;
        model->setHeaderData(i,Qt::Vertical,index->c_str());
        i++;
    }
    //model->setItem(3, 1, new QStandardItem("Zéro !"));
    ui->tableView_TableDeTransition->setModel(model);
}

fenetrePrincipale::~fenetrePrincipale()
{
    delete ui;
}
