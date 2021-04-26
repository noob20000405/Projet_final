#ifndef Hachage_h
#define Hachage_h

#include <stdio.h>
#include "Reseau.h"

/* Q 4.1 */
typedef struct tableHachage {
    int nE; //nombre d'éléments contenus dans la table de hachage
    int m; //taille de la table de hachage
    CellNoeud ** tabN;
} TableHachage;

/* Q 4.2 */// Fonction Clef : Donne la valeur a stocker a partir des coordonnes (x,y) d'un point
double fonctionClef(double x, double y);

/* Q 4.3 */// Fonction de Hachage
int fonctionHachage(double k, int m);

/* Q 4.4 */// retourne un Noeud du reseau R correspondant au point (x,y) dans la table de hachage H. Si le Noeud correspondant n’est pas dans H, nous l’ajoutons dans H et aussi dans R.
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);

/* Q 4.5 */// reconstruit le reseau R a partir de la liste des chaînes C en utilisant une table de hachage H de taille M. 
Reseau* reconstitueReseauHachage(Chaines *C, int M);

void libereTableHachage(TableHachage * H);

#endif /* Hachage_h */
