#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include <stdio.h>
#include <stdlib.h>

#include "Struct_File.h"
#include "Struct_Liste.h"
#include "Reseau.h"

typedef struct{
  int u,v;        /* Numeros des sommets extremité */
} Arete;


typedef struct cellule_arete{
  Arete * a;     /* pointeur sur l'arete */
  struct cellule_arete *suiv;
} Cellule_arete;


typedef struct {
  int num;                 /* Numero du sommet (le meme que dans T_som) */
  double x, y;
  Cellule_arete* L_voisin;  /* Liste chainee des voisins */
} Sommet;


typedef struct{
  int e1,e2;    /* Les deux extremites de la commodite */
} Commod;


typedef struct{
  int nbsom;        /* Nombre de sommets */
  Sommet ** T_som;    /* Tableau de pointeurs sur sommets */
  int gamma;     
  int nbcommod;     /* Nombre de commodites */
  Commod * T_commod; /* Tableau des commodites */
} Graphe;

/* Q 7.1 *///Nous creons un graphe a partir d'un reseau
Graphe * creerGraphe(Reseau * r);

/* Q 7.2 *///Nous calculons le plus petit nombre d'aretes d'une chaine entre 2 sommets u et v
int plusPetitNbAretes(Graphe * G, int r, int s);

/* Q 7.3 *///Nous retournons la plus courte chaine entre les sommets u et v
ListeEntier * plusCourteChaineUV(Graphe * G, int r, int s);

/* Q 7.4 *///Nous créons le graphe, pour chaque commodité nous cherchons sa plus courte chaîne et nous regardons si le nombre gamma est verifiee
int reorganiseReseau(Reseau * r);

/* Afficher le graphe, pour tester */
void afficherGraphe(Graphe * G);

//Liberer une matrice
void freeMAT(int ** matrice, int taille);

//Liberer un graphe
void libererGraphe(Graphe * g);

#endif
