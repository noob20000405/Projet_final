#ifndef __RESEAU_H__
#define __RESEAU_H__
#include "Chaine.h"

typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;               /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
};

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;

/* Q 2.1 */// Retourne le Noeud du reseau R correspondant au point (x,y) dans la liste chaînée noeuds de R. Si le Noeud correspondant n’est pas dans R, nous le créons et l’ajoutons à R. 
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);

/* Q 2.2 */// Reconstruit le reseau R a partir de l'ensemble de chaines C
Reseau* reconstitueReseauListe(Chaines *C);


/* Q 3.1 */
//compte le nombre de commodites du reseau R
int nbCommodites(Reseau *R);
//compte le nombre de liaisons (cables) du reseau R
int nbLiaisons(Reseau *R);

/* Q 3.2 */// Ecrit dans un fichier le contenu d’un reseau R.
void ecrireReseau(Reseau *R, FILE *f);

/* Q 3.3 *///permet de creer un fichier SVG en html pour visualiser un reseau.
void afficheReseauSVG(Reseau *R, char* nomInstance);

void libereReseauListe(Reseau * R);

// Fonction qui permet d'inserer un noeud dans une liste des voisins
void insereVoisin(CellNoeud ** L, Noeud * n);

#endif

