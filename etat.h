#ifndef ETAT_H
#define ETAT_H

#include "list"
#include "transition.h"
#include "string"
using namespace std;
/** a suprimer **/
#include <iostream>
#include <fstream>


class Transition; // Evite les erreurs du compilateur, pour l'utilisation de la classe Transition dans la class Etat et vice versa

class Etat{
    /** *************************************************************************************** \
     * CLASSE DE L'OBJET ETAT :
     * Permet de representer l'état sous forme d'objet pour effecteur des traitements
     * *****************************************************************************************/

    /* *******************************************************\
     * ATRIBUTS
     * *******************************************************/
    string nom;// Contient le nom de l'etats
    list <Transition*> listeDeToutesLesTransition;// Contient toutes les transitions appartenant a l'état
    bool initial;// Permet de savoir si l'etat est initial
    bool terminal;// Permet de savoir si l'etat est terminal

public:
    Etat();
    Etat(const string &nomDeLEtat);
    /* ********************************************************\
     * METHODES
     * ********************************************************/
     void ajouterUneTransition(Transition &transition);

    /* ********************************************************\
     * ASSESSEURS
     * ********************************************************/
    string getNom() const;// Renvoi une reference sur le nom de l'état
    void setNom(const string &Nom);// Permet de changer le nom de l'etat;

    list <Transition*> getListeDesTransitions() const;// Renvoi une reference sur le nom de l'état


    bool isInitial() const; // Retourne vraix si l'etat est initial et faux si il ne l'es pas
    bool isTerminal() const; // Retourne vraix si l'etat est terminal et faux si il ne l'es pas
    void setInitial(const bool &b); // Permet de modifier l'etat initial en true ou false
    void setTerminal(const bool &b); // Permet de modifier l'etat terminal en true ou false

    /* ********************************************************\
     * SURCHARGE D'OPERATEUR
     * ********************************************************/
    bool operator==(Etat const& etat) const;
    bool operator==(string const& etat) const;

};

#endif // ETAT_H
