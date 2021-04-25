#ifndef __ARBRE_QUAT_H__
#define __ARBRE_QUAT_H__

#include "Reseau.h"

/* Arbre quaternaire contenant les noeuds du reseau */
typedef struct arbreQuat{
    double xc, yc;          /* Coordonnees du centre de la cellule */	
    double coteX;           /* Longueur de la cellule */
    double coteY;           /* Hauteur de la cellule */
    Noeud* noeud;           /* Pointeur vers le noeud du reseau */
    struct arbreQuat *so;   /* Sous-arbre sud-ouest, pour x < xc et y < yc */
    struct arbreQuat *se;   /* Sous-arbre sud-est, pour x >= xc et y < yc */
    struct arbreQuat *no;   /* Sous-arbre nord-ouest, pour x < xc et y >= yc */
    struct arbreQuat *ne;   /* Sous-arbre nord-est, pour x >= xc et y >= yc */
} ArbreQuat;

/* Q 5.1 */
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax); /* Fonction qui determine les coordonnees minimales et maximales des points */
/* Q 5.2 */
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY); /* Fonction qui permet de créer une cellule de l’arbre quaternaire */
/* Q 5.3 */
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent);
/* Q 5.4 */
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y);
/* Q 5.5 */
Reseau* reconstitueReseauArbre(Chaines* C);

void libereArbreQuat(ArbreQuat * a);

#endif
