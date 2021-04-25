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

void libereTableHachage(TableHachage * H);

/* Q 4.2 */
double fonctionClef(double x, double y);
/* Q 4.3 */
int fonctionHachage(double k, int m);
/* Q 4.4 */
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
/* Q 4.5 */
Reseau* reconstitueReseauHachage(Chaines *C, int M);

#endif /* Hachage_h */
