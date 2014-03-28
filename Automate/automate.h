#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "Automate/etat.h"
#include "Automate/transition.h"
/** a suprimer **/
#include <iostream>
#include <fstream>
using namespace std;

class Etat;
class Transition;
class Automate{
    /** *************************************************************************************** \
     * CLASSE DE L'OBJET AUTOMATE :
     * Permet de representer l'automate sous forme d'objet pour effecteur des traitement dessus
     * *****************************************************************************************/
    // Contient tous les etats
    list <Etat> listeDeTousLesEtats;
    // Contient tous les etats initiaux
    list <Etat*> listeDeTousLesEtatsInitiaux;
    // Contient tous les etats terminaux
    list <Etat*> listeDeTousLesEtatsTerminaux;
    list <Etat*> listeDeTousLesEtatsCourrant;


    list<Transition> listeDeTousLesTransitions;
public:
    Automate();

    list <Etat> &getListeDeTousLesEtats();
    list<Etat *> &getListeDeTousLesEtatsInitiaux();
    list<Etat *> &getListeDeTousLesEtatsTerminaux();
    list<Transition> &getListeDeTousLesTransitions();
    bool esQueLEtatExisteDeja(const string &nomDeLEtatARechercher);
    bool esQueLaTransitionExisteDeja(const Transition &transitionARechercher);

    void ajouterUnEtat(Etat &etat);
    void ajouterUnEtat(const string &nomEtat);

    void ajouterUneTransition(Transition &transition);

    bool rendreInitialUnEtat(Etat &etat);
    bool rendreInitialUnEtat(const string &nomEtat);

    bool rendreTerminalUnEtat(Etat &etat);
    bool rendreTerminalUnEtat(const string &nomEtat);

    Etat *rechercherEtat(const string &nomEtat);

    list<string> *getlistTransitionsName();
    list<string> *getlistEtatName();

    bool estStandard();
    bool estDeterministe();

};

#endif // AUTOMATE_H
