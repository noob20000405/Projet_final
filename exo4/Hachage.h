#ifndef Hachage_h
#define Hachage_h

#include <stdio.h>
#include "Reseau.h"

typedef struct tableHachage {
    int nE; //nombre d'éléments contenus dans la table de hachage
    int m; //taille de la table de hachage
    CellNoeud ** tabN;
} TableHachage;

void libereTableHachage(TableHachage * H);

double fonctionClef(double x, double y);
int fonctionHachage(double k, int m);

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);

Reseau* reconstitueReseauHachage(Chaines *C, int M);

#endif /* Hachage_h */
