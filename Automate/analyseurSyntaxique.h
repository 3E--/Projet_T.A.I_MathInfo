#ifndef ANALYSEURSYNTAXIQUE_H
#define ANALYSEURSYNTAXIQUE_H

#include "automate.h"
#include "string.h"
#include "queue"
#include <iostream>
#include <fstream>
#include <qobject.h>
using namespace std;

class AnalyseurSyntaxique : public QObject {

    Q_OBJECT
public:
    explicit AnalyseurSyntaxique(QObject *parent = 0);
    Automate &genererUnAutomate(const string &liensDuFichierTexte);
private :
    queue<string> lectureDuFichierTexte(const string & liensDuFichierTexte );
    queue<string> &splitToQueue(const string & texte,const string & delimiteur);
    vector<string> &splitToVector(const string & texte,const string & delimiteur);
    void suprimerLesCaracteres(string& texte,const string &aSupprimer);
signals:
    void signalInformation(string);
signals:

public slots:

};

#endif // ANALYSEURSYNTAXIQUE_H
