#include "fenetrePrincipake.h"
#include "ui_fenetrePrincipake.h"
////////////////////////////////////////////////////////////////////////////////////
fenetrePrincipake::fenetrePrincipake(QWidget *parent) : QMainWindow(parent),ui(new Ui::fenetrePrincipake){
    ui->setupUi(this);

    connect(ui->PBOuvrirFichierAutomate,SIGNAL(clicked()),this,SLOT(slotChoisirUnFichierAutomate()));
    connect(&analyseurSyntaxique,SIGNAL(signalInformation(string)),this,SLOT(slotAfficherMessage(string)));
}
////////////////////////////////////////////////////////////////////////////////////
fenetrePrincipake::~fenetrePrincipake(){
    delete ui;
}
////////////////////////////////////////////////////////////////////////////////////
void fenetrePrincipake::slotAfficherMessage(string texte){
    ui->log->append(texte.c_str());
}
////////////////////////////////////////////////////////////////////////////////////
void fenetrePrincipake::slotChoisirUnFichierAutomate(){

    // FENETRE POUR CHOISIR LE FICHIER DE L'AUTOMATE
    string lienFichierAutomate = QFileDialog::getOpenFileName(this,tr("Choisir le fichier de l'automate"),QDir::currentPath(),tr("text files (*.txt)")).toStdString();
    ui->LEFichierAutomate->setText(lienFichierAutomate.c_str());

    /// //////////////////////////////////
    /// EXECUTION DU CODE DE L'AUTOMATE
    /// //////////////////////////////////
    try {

        Automate automate=analyseurSyntaxique.genererUnAutomate(lienFichierAutomate);

        //afficherLaTableDeTransitionDeLAutomate(automate);
    }
    catch (string &erreur) {
        QMessageBox msgBox;
        msgBox.setText(QString::fromUtf8(erreur.c_str()));
        msgBox.exec();
    }
}
////////////////////////////////////////////////////////////////////////////////////
