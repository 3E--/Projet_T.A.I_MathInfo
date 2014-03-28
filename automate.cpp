#include "automate.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
Automate::Automate(){

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void Automate::ajouterUnEtat(Etat &etat){
    /** ****************************************************************************************\
     * METHODE : Permet l'ajout d'un objet Etat dans la liste de tout les etats de l'automate
     * *****************************************************************************************/

    // VERIFIER SI LE NOM DE L'ETAT N'EXISTE PAS DEJA DANS LA LISTE DE TOUS LES ETATS DE L'AUTOMATE
    if(esQueLEtatExisteDeja(etat.getNom())) throw "l'état : '"+etat.getNom()+"' existe deja dans la liste des états ( erreur de syntaxe dans le fichier de l'automate )";
    // Ajoute l'etat dans en tête de la liste de tous les états de l'automate
    listeDeTousLesEtats.push_front(etat);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void Automate::ajouterUnEtat(const string &nomEtat){
    /** ****************************************************************************************\
     * METHODE : Permet l'ajout d'un objet Etat dans la liste de tout les etats de l'automate
     * *****************************************************************************************/
    Etat etat(nomEtat);
    ajouterUnEtat(etat);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void Automate::ajouterUneTransition(Transition &transition){
    /** ****************************************************************************************\
     * METHODE : Permet l'ajout d'un objet Etat dans la liste de tout les etats de l'automate
     * *****************************************************************************************/

    /// VERIFIE LA TRANSITION N'EXISTE PAS DEJA DANS LA LISTE DE TOUS LES TRANSITIONS DE L'AUTOMATE
    // BOUCLE POUR PARCOURIR LA LISTE DES TRANSITION DU DEBUT JUSQU'A LA FIN
    for(list<Transition>::iterator index = listeDeTousLesTransitions.begin(); index != listeDeTousLesTransitions.end(); index++)
        /// SI ON TROUVE LA TRANSITION A AJOUTER DANS LA LISTE DES STRANSITION ON DECLENCHE UNE EXEPTION
        if(*index==transition) throw "Erreur : imposible d'ajouter la transition '"+transition.getEtatCourant()->getNom()+"-"+transition.getNom()+"-"+transition.getEtatSuivant()->getNom()+"' car elle existe deja (erreur de syntaxe : doublon d'etats)";

    /*
    // VERIFIE SI LE NOM DE LA TRANSITION N'EXISTE PAS DEJA DANS LA LISTE DE TOUS LES ETATS DE L'AUTOMATE
    if(esQueLaTransitionExisteDeja(transition)) throw "la transition : '"+transition.getNom()+"' existe deja dans la liste des transitions ( erreur de syntaxe dans le fichier de l'automate )";

    // VERIFIE SI LE NOM DE L'ETAT COURRANT DE LA TRANSITION EXITE, SI L'ETAT N'EXISTE PAS DEJA DANS LA LISTE DE TOUS LES ETATS DE L'AUTOMATE ON DECLENCHE UNE EXEPTION
    if(!esQueLEtatExisteDeja(transition.getEtatCourant()->getNom())) throw "la transition : '"+transition.getNom()+"' contien l'etat courrant '"+transition.getEtatCourant()->getNom()+"' qui n'existe pas dans la declaration des etat a la ligne 'ETATS:'( erreur de syntaxe dans le fichier de l'automate )";

    // VERIFIE SI LE NOM DE L'ETAT SUIVANT DE LA TRANSITION EXITE, SI L'ETAT N'EXISTE PAS DEJA DANS LA LISTE DE TOUS LES ETATS DE L'AUTOMATE ON DECLENCHE UNE EXEPTION
    if(!esQueLEtatExisteDeja(transition.getEtatSuivant()->getNom())) throw "la transition : '"+transition.getNom()+"' contien l'etat suivant '"+transition.getEtatSuivant()->getNom()+"' qui n'existe pas dans la declaration des etat a la ligne 'ETATS:'( erreur de syntaxe dans le fichier de l'automate )";
    */

    // AJOUTE LA TRANSITION DANS LA TETE DE LA LISTE DE TOUTES LES TRANSITION DE L'AUTOMATE
    listeDeTousLesTransitions.push_front(transition);

    // RECHERCHE L'ETAT COURRANT POUR LUI AJOUTER LA TRANSITION
    // BOUCLE POUR PARCOURIR LA LISTE DES ETATS DU DEBUT JUSQU'A LA FIN
    for(list<Etat>::iterator index = listeDeTousLesEtats.begin(); index != listeDeTousLesEtats.end(); index++)
        /// SI ON TROUVE L'ETAT COURRANT ON LUI AJOUTE LA TRANSITION
        if(*index==transition.getEtatCourant()->getNom())
            index->ajouterUneTransition(transition);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Automate::rendreInitialUnEtat(Etat &etat){
    /** *****************************************************************************
     * METHODE :
     *  PERMET DE CHERCHER L'ETAT A RENDRE INITIAL DANS LA LISTE DES ETATS.
     * RESULTAT :
     *  SI L'ETAT EXISTE LA METHODE RENVOIE TRUE
     *  SI L'ETAT N'EXISTEPAS LA METHODE RENVOIE FALSE
     * *****************************************************************************/

    // BOUCLE POUR PARCOURIR LA LISTE DES ETATS DE DEBUT JUSQU'A LA FIN
    for(list<Etat>::iterator index = listeDeTousLesEtats.begin(); index != listeDeTousLesEtats.end(); index++) {

        /// SI UN ETATS DEJA PRESENT DANS LA LISTE A LE MEME NOM
        if(*index==etat.getNom()){

            // ON TRANSFORME L'ETAT EN ETAT TERMINAL
            index->setInitial(true);

            // ON AJOUTE A LA LISTE DES ETATS INITIAUX
            listeDeTousLesEtatsInitiaux.push_back(&*index);

            return true;
        }
    }
    return false;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Automate::rendreInitialUnEtat(const string &nomEtat){
    /** *****************************************************************************
     * METHODE :
     *  PERMET DE CHERCHER L'ETAT A RENDRE INITIAL DANS LA LISTE DES ETATS.
     * RESULTAT :
     *  SI L'ETAT EXISTE LA METHODE RENVOIE TRUE
     *  SI L'ETAT N'EXISTEPAS LA METHODE RENVOIE FALSE
     * *****************************************************************************/

    // BOUCLE POUR PARCOURIR LA LISTE DES ETATS DE DEBUT JUSQU'A LA FIN
    for(list<Etat>::iterator index = listeDeTousLesEtats.begin(); index != listeDeTousLesEtats.end(); index++) {
        /// SI UN ETATS DEJA PRESENT DANS LA LISTE A LE MEME NOM
        if(*index==nomEtat){

            // ON TRANSFORME L'ETAT EN ETAT TERMINAL
            index->setInitial(true);

            // ON AJOUTE A LA LISTE DES ETATS INITIAUX
            listeDeTousLesEtatsInitiaux.push_back(&*index);

            return true;
        }
    }
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Automate::rendreTerminalUnEtat(Etat &etat){
    /** *****************************************************************************
     * METHODE :
     *  PERMET DE CHERCHER L'ETAT A RENDRE TERMINAL DANS LA LISTE DES ETATS.
     * RESULTAT :
     *  SI L'ETAT EXISTE LA METHODE RENVOIE TRUE
     *  SI L'ETAT N'EXISTEPAS LA METHODE RENVOIE FALSE
     * *****************************************************************************/

    // BOUCLE POUR PARCOURIR LA LISTE DES ETATS DE DEBUT JUSQU'A LA FIN
    for(list<Etat>::iterator index = listeDeTousLesEtats.begin(); index != listeDeTousLesEtats.end(); index++) {

        /// SI UN ETATS DEJA PRESENT DANS LA LISTE A LE MEME NOM
        if(*index==etat){

            // ON TRANSFORME L'ETAT EN ETAT TERMINAL
            index->setTerminal(true);

            // ON AJOUTE A LA LISTE DES ETATS INITIAUX
            listeDeTousLesEtatsTerminaux.push_back(&*index);

            return true;
        }
    }
    return false;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Automate::rendreTerminalUnEtat(const string &nomEtat){
    /** *****************************************************************************
     * METHODE :
     *  PERMET DE CHERCHER L'ETAT A RENDRE TERMINAL DANS LA LISTE DES ETATS.
     * RESULTAT :
     *  SI L'ETAT EXISTE LA METHODE RENVOIE TRUE
     *  SI L'ETAT N'EXISTEPAS LA METHODE RENVOIE FALSE
     * *****************************************************************************/

    // BOUCLE POUR PARCOURIR LA LISTE DES ETATS DE DEBUT JUSQU'A LA FIN
    for(list<Etat>::iterator index = listeDeTousLesEtats.begin(); index != listeDeTousLesEtats.end(); index++) {

        /// SI UN ETATS DEJA PRESENT DANS LA LISTE A LE MEME NOM
        if(*index==nomEtat){

            // ON TRANSFORME L'ETAT EN ETAT TERMINAL
            index->setTerminal(true);

            // ON AJOUTE A LA LISTE DES ETATS INITIAUX
            listeDeTousLesEtatsTerminaux.push_back(&*index);

            return true;
        }
    }
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Automate::esQueLEtatExisteDeja(const string &nomDeLEtatARechercher){
    /** *****************************************************************************
     * METHODE :
     *  PERMET DE RECHERCHER L'ETAT DANS LA LISTE, POUR SAVOIR SI IL EXISTE DEJA
     * RESULTAT :
     *  SI L'ETAT EXISTE LA METHODE RENVOIE TRUE
     *  SI L'ETAT N'EXISTEPAS LA METHODE RENVOIE FALSE
     * *****************************************************************************/

    // BOUCLE POUR PARCOURIR LA LISTE DES ETATS DU DEBUT JUSQU'A LA FIN
    for(list<Etat>::iterator index = listeDeTousLesEtats.begin(); index != listeDeTousLesEtats.end(); index++) {
        /// SI UN ETATS EST DEJA PRESENT DANS LA LISTE ( IL A LE MEME NOM )
        if(*index==nomDeLEtatARechercher) return true;

    }
    /// ON NA PARCOURUE LA LISTE SANS TROUVER L'ETAT, DONC IL N'EXISTE PAS
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Automate::esQueLaTransitionExisteDeja(const Transition &transitionARechercher){
    /** *****************************************************************************
     * METHODE :
     *  PERMET DE RECHERCHER LA TRANSITION DANS LA LISTE, POUR SAVOIR SI IL EXISTE DEJA
     * RESULTAT :
     *  SI LA TRANSITION EXISTE LA METHODE RENVOIE TRUE
     *  SI LA TRANSITION N'EXISTEPAS LA METHODE RENVOIE FALSE
     * *****************************************************************************/

    // BOUCLE POUR PARCOURIR LA LISTE DES TRANSITIONS DU DEBUT JUSQU'A LA FIN
    for(list<Transition>::iterator index = listeDeTousLesTransitions.begin(); index != listeDeTousLesTransitions.end(); index++) {
        /// SI UN ETATS EST DEJA PRESENT DANS LA LISTE ( IL A LE MEME NOM )
        if(*index==transitionARechercher) {
            return true;
        }

    }
    /// ON NA PARCOURUE LA LISTE SANS TROUVER L'ETAT, DONC IL N'EXISTE PAS
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
Etat *Automate::rechercherEtat(const string &nomEtat){
    /** *****************************************************************************
     * METHODE :
     *  PERMET DE RECHERCHER UN ETAT DANS LA LISTE DES ETATS DE L'AUTOMATE
     * RESULTAT :
     *  SI ON A TROUVER L'ETAT, LA METHODE RENVOIE UN POINTEUR SUR L'ETAT TROUVE
     *  SI ON N'A PAS TROUVER L'ETAT, LA METHODE RENVOI UN POINTEUR NULL
     * *****************************************************************************/
    // BOUCLE POUR PARCOURIR LA LISTE DES ETATS DU DEBUT JUSQU'A LA FIN
    for(list<Etat>::iterator index = listeDeTousLesEtats.begin(); index != listeDeTousLesEtats.end(); index++) {
        /// SI UN ETATS EST DEJA PRESENT DANS LA LISTE ( IL A LE MEME NOM )
        if(*index==nomEtat) return &*index;
    }
    return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
list<string> *Automate::getlistTransitionsName(){
    /** *******
     * METHODE :    PERMET DE RETOURNER LE NOM DE TOUTES LES TRANSITIONS SANS DOUBLON DE L'AUTOMATE
     * RESUALTAT:   LISTE DES NOM DE TOUTES LES TRANSITIONS DE L'AUTOMATE
     ********************/
    if(listeDeTousLesTransitions.empty())return NULL;
    list<string> *listeDesNomDesTransitions = new list<string>;
    //listeDesNomDesTransitions=NULL;

    // BOUCLE POUR PARCOURIR LA LISTE DES TRANSITIONS DU DEBUT JUSQU'A LA FIN
    for(list<Transition>::iterator iteratorListeDeTousLesTransitions = listeDeTousLesTransitions.begin(); iteratorListeDeTousLesTransitions != listeDeTousLesTransitions.end(); iteratorListeDeTousLesTransitions++) {

        if(listeDesNomDesTransitions->empty())
            // ON AJOUTE LE NOM DE LA TRANSITION DANS LA LISTE
            listeDesNomDesTransitions->push_front(iteratorListeDeTousLesTransitions->getNom());
        else{
            bool find=false;
            // BOUCLE POUR PARCOURIR LA LISTE DES NOM DES TRANSITIONS DU DEBUT JUSQU'A LA FIN POUR LES COMPARER
            for(list<string>::iterator index = listeDesNomDesTransitions->begin(); (index != listeDesNomDesTransitions->end())&&(!find); index++) {
                cout << *index<<"!="<<iteratorListeDeTousLesTransitions->getNom()<<endl;
                /// SI IL NE SONT PAS EGAUX SELA VEUT DIRE QUE LE NOM DE LA TRANSITION N'EXISTE PAS DANS LA LISTE
                if(*index==iteratorListeDeTousLesTransitions->getNom())find=true;
            }
            // ON AJOUTE LE NOM DE LA TRANSITION DANS LA LISTE
            if(!find)listeDesNomDesTransitions->push_front(iteratorListeDeTousLesTransitions->getNom());
    }
    }
    if(listeDesNomDesTransitions==NULL)throw "Erreur : aucune transition trouve";
    return listeDesNomDesTransitions;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
list<string> *Automate::getlistEtatName(){
    /** *******
     * METHODE :    PERMET DE RETOURNER LE NOM DE TOUTES LES TRANSITIONS SANS DOUBLON DE L'AUTOMATE
     * RESUALTAT:   LISTE DES NOM DE TOUTES LES TRANSITIONS DE L'AUTOMATE
     ********************/
    if(listeDeTousLesTransitions.empty())return NULL;
    list<string> *listeDesNomDesEtats = new list<string>;
    // BOUCLE POUR PARCOURIR LA LISTE DES TRANSITIONS DU DEBUT JUSQU'A LA FIN
    for(list<Etat>::iterator unEtat = listeDeTousLesEtats.begin(); unEtat != listeDeTousLesEtats.end(); unEtat++) {
        if(!unEtat->isInitial()&& !unEtat->isTerminal())
        listeDesNomDesEtats->push_front("          "+unEtat->getNom());
        else if(unEtat->isInitial()&& !unEtat->isTerminal())
        listeDesNomDesEtats->push_front("Initial:  "+unEtat->getNom());
        else if(!unEtat->isInitial()&& unEtat->isTerminal())
        listeDesNomDesEtats->push_front("Terminal: "+unEtat->getNom());
        else
        listeDesNomDesEtats->push_front("Entre/Sortie :"+ unEtat->getNom());
    }
    return listeDesNomDesEtats;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Automate::estStandard(){
    /** ****************************************************************************************\
     *  METHODE     :   PERMET DE SAVOIR SI L'AUTOMATE EST STANDAR OU NON
     *  RESULTAT    :   TRUE SI L'AUTOMATE EST STANDARD, FALSE SI L'AUTOMATE N'EST PAS STANDARD
     * *****************************************************************************************/

    /// SI IL Y A PLUS D'UN ETAT INITIAL, L'AUTOMATE N'EST PAS STANDARD
    if(listeDeTousLesEtatsInitiaux.size()!=1)return false;

    /// SINON SI IL Y A PAS AU MOINS UN ETAT TERMINAL, L'AUTOMATE N'EST PAS STANDARD
    if(listeDeTousLesEtatsTerminaux.size()==0)return false;

    // BOUCLE POUR PARCOURIR LA LISTE DES TRANSITIONS DU DEBUT JUSQU'A LA FIN, AVEC UN ITERATOR
    for(list<Transition>::iterator iteratorListeDeTousLesTransitions = listeDeTousLesTransitions.begin(); iteratorListeDeTousLesTransitions != listeDeTousLesTransitions.end(); iteratorListeDeTousLesTransitions++) {
        /// SI ON TROUVE UNE TRANSITION QUI POINTE SUR L'UNIQUE ETAT TERMINAL, L'AUTOMATE N'EST PAS STANDARD
        if(iteratorListeDeTousLesTransitions->getEtatSuivant()==listeDeTousLesEtatsInitiaux.front())return false;
    }

    return true;
}///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Automate::estDeterministe(){
    /** ****************************************************************************************\
     *  METHODE     :   PERMET DE SAVOIR SI L'AUTOMATE EST STANDAR OU NON
     *  RESULTAT    :   TRUE SI L'AUTOMATE EST STANDARD, FALSE SI L'AUTOMATE N'EST PAS STANDARD
     * *****************************************************************************************/
    // UN AUTOMATE DETERMINISTE C'EST UN AUTOMATE DON UN ETAT N'A PAS DE TRANSITION AVECVEC LE MËME NOM MENAN A 2 ETAT DIFERENT

    /// SI IL Y A PLUS D'UN ETAT INITIAL, L'AUTOMATE N'EST PAS DETERMINISTE
    if(listeDeTousLesEtatsInitiaux.size()!=1)return false;

    // BOUCLE POUR PARCOURIR LA LISTE DES TRANSITIONS DU DEBUT JUSQU'A LA FIN, AVEC UN ITERATOR
    for(list<Etat>::iterator unEtat = listeDeTousLesEtats.begin(); unEtat != listeDeTousLesEtats.end(); unEtat++) {
        /// SI ON TROUVE UNE TRANSITION QUI POINTE SUR L'UNIQUE ETAT TERMINAL, L'AUTOMATE N'EST PAS STANDARD

        // BOUCLE POUR PARCOURIR LA LISTE DES TRANSITIONS DU DEBUT JUSQU'A LA FIN, AVEC UN ITERATOR
        for(list<Transition*>::iterator uneTransitionDeLEtat = unEtat->getListeDesTransitions().begin(); *uneTransitionDeLEtat != *unEtat->getListeDesTransitions().end(); uneTransitionDeLEtat++) {
            /// SI UN ETAT DE LA LISTE DE L'AUTOMATE CONTIENT 2 TRANSITION AYEN LE MÊME NOM, SELA VEUT DIRE QUE CE N'EST PAS UN AUTOMATE DETERMINISTE
            /// CAR POUR UNE MÊME TRANSITION SUR UN ETAT ON SE RETROUVE DANS 2 ETAT
            // BOUCLE POUR PARCOURIR LA LISTE DES TRANSITIONS DU DEBUT JUSQU'A LA FIN, AVEC UN ITERATOR
            for(list<Transition*>::iterator uneTransitionDeLEtatAComparer = unEtat->getListeDesTransitions().begin()++; *uneTransitionDeLEtatAComparer != *unEtat->getListeDesTransitions().end(); uneTransitionDeLEtatAComparer++) {
                //cout<<**uneTransitionDeLEtat->getNom()<<"=="<<**uneTransitionDeLEtatAComparer->getNom();
                if(**uneTransitionDeLEtat==**uneTransitionDeLEtatAComparer)return false;

            }
        }
    }
    return true;
}
