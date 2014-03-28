#ifndef TRANSITION_H
#define TRANSITION_H

#include "Automate/etat.h"
#include "string"
using namespace std;
class Etat;// Evite les erreurs du compilateur, pour l'utilisation de la classe Etat dans la class Transition et vice versa
class Transition{
    /** *************************************************************************************** \
     * CLASSE DE L'OBJET ETAT :
     * Permet de representer l'état sous forme d'objet pour effecteur des traitements
     * *****************************************************************************************/
    // Contien le nom de la transition
    string nom;
    // Pointeur sur l'état courant
    Etat *etatCourant;
    // Pointeur sur l'état suivant
    Etat *etatSuivant;

public:

    Transition();
    Transition(Etat *etatCourantDeLaTransition,const string & nomDeLaTransition,Etat *etatSuivantDeLaTransition);
    Transition(const string &nomEtatCourantDeLaTransition,const string & nomDeLaTransition,const string &nomEtatSuivantDeLaTransition);

    /* ********************************************************\
     * ASSESSEURS
     * ********************************************************/

    //NOM
    void setNom(const string &Nom);
    string getNom() const;
    // ETAT COURRANT
    void setEtatCourant(const string &nomEtatCourrant);
    void setEtatCourant(Etat *_etatCourrant);
    Etat *getEtatCourant() const;
    // ETAT SUIVANT
    void setEtatSuivant(const string &nomEtatSuivant);
    void setEtatSuivant(Etat *_etatSuivant);
    Etat *getEtatSuivant() const;

    /* ********************************************************\
     * SURCHARGE D'OPERATEUR
     * ********************************************************/
    bool operator==(Transition const& transitiont) const;
    bool operator==(string const& nomTransition) const;
    bool operator!=(Transition const& transitiont) const;
    bool operator!=(string const& nomTransition) const;
};

#endif // TRANSITION_H
