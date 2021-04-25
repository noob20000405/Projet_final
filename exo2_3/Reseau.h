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

/* Q 2.1 */
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
/* Q 2.2 */
Reseau* reconstitueReseauListe(Chaines *C);
/* Q 3.2 */
void ecrireReseau(Reseau *R, FILE *f);
/* Q 3.1 */
int nbLiaisons(Reseau *R);
int nbCommodites(Reseau *R);
/* Q 3.3 */
void afficheReseauSVG(Reseau *R, char* nomInstance);

void libereReseauListe(Reseau * R);

/* Fonction permet d'inserer les voisins dans un noeud */
void insereVoisin(CellNoeud ** L, Noeud * n);

#endif

