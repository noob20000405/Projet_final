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

/* Q 5.1 *///determine les coordonneees minimales et maximales des points constituant les differentes chaines du reseau
void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax); /* Fonction qui determine les coordonnees minimales et maximales des points */

/* Q 5.2 *///creer une cellule de l’arbre quaternaire, de centre (xc, yc), de longueur coteX et de hauteur coteY. 
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY); /* Fonction qui permet de créer une cellule de l’arbre quaternaire */

/* Q 5.3 */// Inserer un Noeud du reseau dans un arbre quaternaire
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent);

/* Q 5.4 */// retourne un Noeud du reseau R correspondant au point de coordonnees (x,y) dans l’arbre quaternaire. Si le Noeud correspondant n'existe pas dans l'arbre, nous le creons et l'ajoutons dans l'arbre, ainsi que dans R.  
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y);

/* Q 5.5 */// reconstruit le reseau R a partir de la liste des chaines C et en utilisant l’arbre quaternaire.
Reseau* reconstitueReseauArbre(Chaines* C);

void libereArbreQuat(ArbreQuat * a);

#endif
