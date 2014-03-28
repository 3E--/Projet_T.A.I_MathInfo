#include "analyseurSyntaxique.h"

AnalyseurSyntaxique::AnalyseurSyntaxique(QObject *parent) : QObject(parent){

}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
Automate & AnalyseurSyntaxique::genererUnAutomate(const string &liensDuFichierTexte){
    /***********************************************************************************************************
      * CETTE METHODE PERMET DE GENERER UN AUTOMATE A PARTIR D'UN FICHIER TEXTE, SELON UNE SYNTAXTE PARTICULIERE
      * *********************************************************************************************************/

    /// CETTE OPERATION COMPLEXE EST SUCEPTIBLE DE GENERER DES ERREURS, DONC ON EFFECTUE UN TRY CATCH POUR GERE LES EXEPTIONS
    try{
        emit signalInformation("[Info] Lecture du fichier");
        // LECTURE DU FICHIER TEXTE DE L'AUTOMATE
        queue<string> queueFichierTexte=lectureDuFichierTexte(liensDuFichierTexte);

        // CREATION DE L'OBJET AUTOMATE
        Automate *automate=new Automate;

        // BOUCLE QUI PERMET DE PARCOURIR LA QUEUE, TANT QUE CELLE CI N'EST PAS VIDE
        while(!queueFichierTexte.empty()){

            string ligne=queueFichierTexte.front();

            unsigned int positionDuMarqeur=0;

            if(!(positionDuMarqeur=ligne.find("ETATS:"))){
                ////////////////////////////////////////////////////
                // * SI LA LIGNE CONTIENT LE MARQUEUR "ETATS:"  * //
                ////////////////////////////////////////////////////

                // SUPRIME LE MARQUEUR "ETAT:"
                ligne.erase(0,positionDuMarqeur+6);


                // ON SEPARE CHAQUE ETAT EN FONCTION DU DELIMITEUR ','
                queue<string> queueNomsEtats=splitToQueue(ligne,",");

                // BOUCLE QUI PERMET DE CREE DES ETATS DANS L'AUTOMATE
                while (!queueNomsEtats.empty()) {

                    automate->ajouterUnEtat(queueNomsEtats.front());

                    queueNomsEtats.pop();
                }

                // //////////////////////
                // AFICHAGE DU MESSAGE //
                // //////////////////////
                list<Etat> listEtatAutomate= automate->getListeDeTousLesEtats();
                for (list<Etat>::iterator it = listEtatAutomate.begin(); it != listEtatAutomate.end(); it++)
                    /// SI ON TROUVE UNE TRANSITION QUI POINTE SUR L'UNIQUE ETAT TERMINAL, L'AUTOMATE N'EST PAS STANDARD
                    emit signalInformation("[Info] Etat ajoute : \""+it->getNom()+"\"");


            }
            else if(!(positionDuMarqeur=ligne.find("ETATS INITIAUX:"))){
                ////////////////////////////////////////////////////////////
                // * SI LA LIGNE CONTIENT LE MARQUEUR "ETATS INITIAL:" * //
                ////////////////////////////////////////////////////////////

                // SUPRIME LE MARQUEUR "ETAT:"
                ligne.erase(0,positionDuMarqeur+15);

                // ON SEPARE CHAQUE ETAT INITIAL EN FONCTION DU DELIMITEUR ','
                queue<string> queueNomsEtats=splitToQueue(ligne,",");

                // BOUCLE QUI PERMET DE CREE DES ETATS DANS L'AUTOMATE
                while (!queueNomsEtats.empty()) {

                    // ON SUPPRIME LES EVENTUELLES ESPACES
                    suprimerLesCaracteres(queueNomsEtats.front()," ");

                    /// SI ON N'A PAS REUSSI A LE RENDRE TERMINAL, SELA VEUT DIRE QUE L'ETAT NA PAS ETE AJOUTER DANS LA LISTE DE TOUTS LES ETAT, DONC ON DECLENCHE UNE EXEPTION
                    /// CELA PEUT ETRE DU A UNE ETRREUR DE SYNTAXE DU FICHIER AUTOMATE
                    if(!automate->rendreInitialUnEtat(queueNomsEtats.front()))
                        throw "Erreur : Imposible de configurer en tant q'etat initial, l'etat '"+queueNomsEtats.front()+"' (Cela peut etre du a une erreur de syntaxe du fichier : '"+liensDuFichierTexte+"').";

                    queueNomsEtats.pop();
                }

                // //////////////////////
                // AFICHAGE DU MESSAGE //
                // //////////////////////
                list<Etat*> listEtatAutomate= automate->getListeDeTousLesEtatsInitiaux();
                for (list<Etat*>::iterator it = listEtatAutomate.begin(); it != listEtatAutomate.end(); it++)
                    /// SI ON TROUVE UNE TRANSITION QUI POINTE SUR L'UNIQUE ETAT TERMINAL, L'AUTOMATE N'EST PAS STANDARD
                    emit signalInformation("[Info] Etat Initial ajoute : \""+(*it)->getNom()+"\"");

            }
            else if(!(positionDuMarqeur=ligne.find("ETATS TERMINAUX:"))){
                /////////////////////////////////////////////////////////////
                // * SI LA LIGNE CONTIENT LE MARQUEUR "ETATS  TERMINAL:" * //
                /////////////////////////////////////////////////////////////

                // SUPRIME LE MARQUEUR "ETATS TERMINAL:"
                ligne.erase(0,positionDuMarqeur+16);

                // ON SEPARE CHAQUE ETAT INITIAL EN FONCTION DU DELIMITEUR ','
                queue<string> queueNomsEtats=splitToQueue(ligne,",");

                // BOUCLE QUI PERMET DE CREE DES ETATS DANS L'AUTOMATE
                while (!queueNomsEtats.empty()) {

                    // ON SUPPRIME LES EVENTUELLES ESPACES
                    suprimerLesCaracteres(queueNomsEtats.front()," ");

                    /// SI ON N'A PAS REUSSI A LE RENDRE TERMINAL, SELA VEUT DIRE QUE L'ETAT NA PAS ETE AJOUTER DANS LA LISTE DE TOUTS LES ETAT, DONC ON DECLENCHE UNE EXEPTION
                    /// CELA PEUT ETRE DU A UNE ETRREUR DE SYNTAXE DU FICHIER AUTOMATE
                    if(!automate->rendreTerminalUnEtat(queueNomsEtats.front()))
                        throw "Erreur : Imposible de configurer en tant q'etat terminal, l'etat '"+queueNomsEtats.front()+"' (Cela peut etre du à une erreur de syntaxe du fichier : '"+liensDuFichierTexte+"').";

                    queueNomsEtats.pop();
                }

                // //////////////////////
                // AFICHAGE DU MESSAGE //
                // //////////////////////
                list<Etat*> listEtatAutomate= automate->getListeDeTousLesEtatsTerminaux();
                for (list<Etat*>::iterator it = listEtatAutomate.begin(); it != listEtatAutomate.end(); it++)
                    /// SI ON TROUVE UNE TRANSITION QUI POINTE SUR L'UNIQUE ETAT TERMINAL, L'AUTOMATE N'EST PAS STANDARD
                    emit signalInformation("[Info] Etat Terminal ajoute : \""+(*it)->getNom()+"\"");
            }
            else if(!(positionDuMarqeur=ligne.find("TRANSITIONS:"))){
                /////////////////////////////////////////////////////////
                // * SI LA LIGNE CONTIENT LE MARQUEUR "TRANSITIONS:" * //
                /////////////////////////////////////////////////////////

                // SUPRIME LE MARQUEUR "TRANSITIONS:"
                ligne.erase(0,positionDuMarqeur+12);


                // ON SEPARE CHAQUE TRANSITION EN FONCTION DU DELIMITEUR ','
                queue<string> queueTransitions=splitToQueue(ligne,",");

                // BOUCLE QUI PERMET DE CREE DES ETATS DANS L'AUTOMATE
                while (!queueTransitions.empty()) {

                    vector<string> vectorTransition=splitToVector(queueTransitions.front(),"-");

                    /// SI L'ORSQUE L'ON A splitToQueueER LA TRANSITION ON NE SE RETROUVE PAS AVEC EXACTEMENT 3 OBJET DANS LA LISTE, ON DECLANCHE UNE EXEPTION
                    if(vectorTransition.size()!=3)throw "Erreur de syntaxe dans la declaration des transitions '"+queueTransitions.front()+"'.";

                    // ON RECHERCHE L'ETAT COURRANT DE LA TRANSITION DANS LA LISTE DES ETATS DE L'AUTOMATE
                    Etat *etatCourant=automate->rechercherEtat(vectorTransition.at(0));
                    /// SI LE POINTEUR EST NULL, CELA VEUX DIRE QUE L'ON A PAS TROUVER L'ETAT COURRANT DE LA TRANSITION DANS LA LISTE DES ETATS DE L'AUTOMATE
                    if(etatCourant==NULL) throw "Erreur : imposible d'ajouter la transition '"+vectorTransition.at(0)+"-"+vectorTransition.at(1)+"-"+vectorTransition.at(2)+"' car l'etat '"+vectorTransition.at(0)+"' n'a pas été ajouter dans la liste des états [ETATS:]";

                    // ON RECHERCHE L'ETAT SUIVANT DE LA TRANSITION DANS LA LISTE DES ETATS DE L'AUTOMATE
                    Etat *etatSuivant=automate->rechercherEtat(vectorTransition.at(2));
                    /// SI LE POINTEUR EST NULL, CELA VEUX DIRE QUE L'ON A PAS TROUVER L'ETAT COURRANT DE LA TRANSITION DANS LA LISTE DES ETATS DE L'AUTOMATE
                    if(etatSuivant==NULL) throw "Erreur : imposible d'ajouter la transition '"+vectorTransition.at(0)+"-"+vectorTransition.at(1)+"-"+vectorTransition.at(2)+"' car l'etat '"+vectorTransition.at(2)+"' n'a pas été ajouter dans la liste des états [ETATS:]";

                    // ON CREE LA TRANSITION EN FONCTION DES NOM QUI SE TROUVE DANS LE FICHIER TEXTE DE L'AUTOMATE
                    Transition transition(etatCourant,vectorTransition.at(1),etatSuivant);

                    // ON SUPRIMME LE VECTEUR
                    vectorTransition.clear();

                    // ON AJOUTE LA TRANSITION DANS L'AUTOMATE
                    automate->ajouterUneTransition(transition);

                    queueTransitions.pop();

                }
                // //////////////////////
                // AFICHAGE DU MESSAGE //
                // //////////////////////
                list<Transition> listTransitions= automate->getListeDeTousLesTransitions();
                for (list<Transition>::iterator it = listTransitions.begin(); it != listTransitions.end(); it++)
                    /// SI ON TROUVE UNE TRANSITION QUI POINTE SUR L'UNIQUE ETAT TERMINAL, L'AUTOMATE N'EST PAS STANDARD
                    emit signalInformation("[Info] Transition ajoute : \""+it->getEtatCourant()->getNom()+"--"+it->getNom()+"->"+it->getEtatSuivant()->getNom()+"\"");
            }
            // SUPPRIME LA LIGNE ( LA TETE DE LA QUEUE )
            queueFichierTexte.pop();
        }

        return *automate;
    }
    /// ON GERE TOUTES LES ERREURS QUI PEUVENT EVENTUELLEMENT SURVENIR DANS UN CATCH
    catch (string &erreur){
        throw "Erreur lors de la creation de l'etat dans l'automate pour le fichier '"+liensDuFichierTexte+"'. "+erreur;
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
queue<string> AnalyseurSyntaxique::lectureDuFichierTexte(const string &liensDuFichierTexte){
    /********************************************************************************
     * CETTE METHODE PERMET DE METRE CHAQUE LIGNE DU FICHIER TEXTE DANS UNE QUEUE
     * *****************************************************************************/

    // CREATION D'UN OBJET DE TYPE ifstream POUR LA LECTURE DU FICHIER TEXTE DE L'AUTOMATE
    ifstream fichierTexte(liensDuFichierTexte.c_str());

    /// SI ON N'A PAS REUSSI A LIRE LE FICHIER TEXTE, ON DECLENCHE UN EXEPTION
    if (!fichierTexte.is_open()) throw "Erreur l'ors de l'ouverture du fichier : '"+liensDuFichierTexte+"'.";
    /// SI LE FICHIER LE FICHIER TEXTE EST VIDE, ON DECLENCHE UN EXEPTION
    /// ne fonctionne pas !!! >>> if (!fichierTexte.tellg()==0) throw "Erreur le fichier : '"+liensDuFichierTexte+"', est vide.";

    // CREATION D'UN OBJET DE TYPE QUEUE <STRING> QUI VAS CONTENIR CHAQUE LIGNE DU FICHIER TEXTE DE L'AUTMATE
    queue<string> *queueFichierTexte=new queue<string>;

    // CREATION D'UN VARIABLE LINE QUI VAS CAONTENIR LA LIGNE DE CHAQUE ITERATION DE LA BOUCLE
    string ligne;

    // BOUCLE QUI PERMET DE PARCOURIR TOUT LE FICHIER TEXTE DE L'AUTOMATE LIGNE PAR LIGNE
    while (std::getline(fichierTexte,ligne)){
        // AJOUT DE LA LIGNE DANS LA QUEUE
        queueFichierTexte->push(ligne);
    }


    fichierTexte.close();

    return *queueFichierTexte;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
queue<string> &AnalyseurSyntaxique::splitToQueue(const string & texte,const string & delimiteur){
    /***********************************************************************************************************************************************
     * CETTE METHODE PERMET DE SEPARER PAR RAPORT A UN DELIMITEUR, UNE CHAINE DE CARACTERE EN SOUS CHAINNE DE DE CARACTERE CONTENUE DANS UNE QUEUE
     * ********************************************************************************************************************************************/

    /// SI LA CHAINE DE CARACTERE A SEPARER EST VIDE ON DECLENCHE UNE EXEPTION
    //if(texte.empty()) throw "Erreur : la chaine de caractere à 'speparer' est vide.";

    // CREATION DE LA QUEUE QUI VAS CONTENIR LES CHAINE DE CARACTERE SEPARER PAR LE DELIMITEUR
    queue<string> *queuesplitToQueueResult=new queue<string>;

    unsigned int marqeurFin;
    string texteTemporaire=texte;

    // BOUCLE QUI PERMET DE PARCOURIR TOUT LA CHAINE DE CARACTERE POUR ENSUITE LA SEPARER SELON LA POSITION DU DELIMITEUR
    while((marqeurFin=texteTemporaire.find(delimiteur))!=std::string::npos){

        // RECUPERER LA CHAINE DE CARACTERE QUI SE TROUVE AVANT LE DELIMITEUR
        string texteSepare=texteTemporaire.substr(0,marqeurFin);

        // ON SUPPRIME LES EVENTUELLES ESPACES
        suprimerLesCaracteres(texteSepare," ");

        // SUPPRIsME LA CHAINE DE CARACTERE DU TEXTE A TRAITER
        texteTemporaire.erase(0,marqeurFin+1);

        // AJOUTE DANS LA QUEUE LA SOUS CHAINE DE CARACTERE QUI CE TROUVE ANVANT LE DELIMITEUR
        queuesplitToQueueResult->push(texteSepare);
    }

    // AJOUTE LA FIN DANS LA QUEUE
    queuesplitToQueueResult->push(texteTemporaire);

    // REVOIE LE CONTENUE DU POINTEUR
    return *queuesplitToQueueResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> &AnalyseurSyntaxique::splitToVector(const string & texte,const string & delimiteur){
    /** ********************************************************************************************************************************************
     * CETTE METHODE PERMET DE SEPARER PAR RAPORT A UN DELIMITEUR, UNE CHAINE DE CARACTERE EN SOUS CHAINNE DE DE CARACTERE CONTENUE DANS UNE QUEUE
     * ********************************************************************************************************************************************/

    /// SI LA CHAINE DE CARACTERE A SEPARER EST VIDE ON DECLENCHE UNE EXEPTION
   // if(texte.empty()) throw "Erreur : la chaine de caractere à 'speparer' est vide.";

    // CREATION DE LE VECTOR QUI VAS CONTENIR LES CHAINE DE CARACTERE SEPARER PAR LE DELIMITEUR
    vector<string> *splitToVectorResult=new vector<string>;

    unsigned int marqeurFin;
    string texteTemporaire=texte;

    // BOUCLE QUI PERMET DE PARCOURIR TOUT LA CHAINE DE CARACTERE POUR ENSUITE LA SEPARER SELON LA POSITION DU DELIMITEUR
    while((marqeurFin=texteTemporaire.find(delimiteur))!=std::string::npos){
        // RECUPERER LA CHAINE DE CARACTERE QUI SE TROUVE AVANT LE DELIMITEUR
        string texteSepare=texteTemporaire.substr(0,marqeurFin);

        // ON SUPPRIME LES EVENTUELLES ESPACES
        suprimerLesCaracteres(texteSepare," ");

        // SUPPRME LA CHAINE DE CARACTERE DU TEXTE A TRAITER
        texteTemporaire.erase(0,marqeurFin+1);

        // AJOUTE DANS LE VECTOR LA SOUS CHAINE DE CARACTERE QUI CE TROUVE ANVANT LE DELIMITEUR
        splitToVectorResult->push_back(texteSepare);
    }

    // AJOUTE LA FIN DANS LE VECTOR
    splitToVectorResult->push_back(texteTemporaire);

    // REVOIE LE CONTENUE DU POINTEUR
    return *splitToVectorResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void AnalyseurSyntaxique::suprimerLesCaracteres(string& texte,const string &aSupprimer){
    /*******************************************************************************************
     * METHODE : PERMET DE SUPRIMER TOUS LES CARRACTERE DE LA VARIABLE 'texte'QUI SE TROUVENT DANS LA VARIABLE 'aSuprimer'
     * *****************************************************************************************/

    /// SI LA CHAINE DE CARACTERE EST VIDE ON SORT DE LA METHODE
    //if(texte.empty()) return;
    // ON RECUPERE LA POSITION DU CARACTERE A SUPPRIMER
    string::size_type pos = texte.find_last_not_of(aSupprimer);

    // SI ON A TROUVER LA POSITION
    if(pos != string::npos) {

        // ON EFFACE LE CARACTERE
        texte.erase(pos + 1);

        pos = texte.find_first_not_of(aSupprimer);
        if(pos != string::npos) texte.erase(0, pos);
    }
    else texte.erase(texte.begin(), texte.end());
}
