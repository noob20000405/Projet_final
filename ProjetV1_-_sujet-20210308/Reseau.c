#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "SVGwriter.h"

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y) {
  if (!R) return NULL;
  
  CellNoeud * cn = R -> noeuds;
  while (cn) {
    if (x == cn -> nd -> x && y == cn -> nd -> y) return cn -> nd;
    cn = cn -> suiv;
  }
  /* Si on ne l'a pas trouve dans la liste, on l'ajoute */
  Noeud * nAjoute = (Noeud *)malloc(sizeof(Noeud));
  nAjoute -> num = (R -> nbNoeuds + 1);
  nAjoute -> x = x;
  nAjoute -> y = y;
  nAjoute -> voisins = NULL;
  
  CellNoeud * cnAjoute = (CellNoeud *)malloc(sizeof(CellNoeud));
  cnAjoute -> nd = nAjoute;
  cnAjoute -> suiv = R -> noeuds;
  R -> noeuds = cnAjoute;
  R -> nbNoeuds++;
  
  return cnAjoute -> nd;
}


Reseau* reconstitueReseauListe(Chaines *C) {
  if (!C) return NULL;

  /* Creer le reseau */
  Reseau * r = (Reseau *)malloc(sizeof(Reseau));
  r -> nbNoeuds = 0;
  r -> gamma = C -> gamma;
  r -> commodites = NULL;
  
  CellCommodite * ccommo = NULL;
  Noeud * n  = NULL;
  Noeud * nPrec = NULL;
  /* CellNoeud pour conserver les voisins */
  CellNoeud * cn = NULL;
  /* CellNoeud pour parcourir les voisins */
  CellNoeud * voisin = NULL;
  /* Un entier qui represente si un noeud est deja un voisin de l'autre */
  int estDejaVoisin = 0;
	
  CellChaine * cc = C -> chaines;
  CellPoint * cp = NULL;
  
  int num = 0;
  int numP = 0; // Numero de points dans chaque chaine

  while (cc) {
    cp = cc -> points;
    numP = 0;
    nPrec = NULL;
    n = NULL;
    /* On cree une commodite chaque fois au debut d'un parcourt d'une chaine */
    ccommo = (CellCommodite *)malloc(sizeof(CellCommodite));
    while (cp) {
      /* On conserve le noeud precedent */
      nPrec = n;
      /* On cree un noeud et l'ajoute dans le reseau */
      n = rechercheCreeNoeudListe(r, cp -> x, cp -> y);
      /* On ajoute les voisins */
      if (nPrec) {
        /* Teste si ce noeud est deja un voisin de l'autre */
        estDejaVoisin = 0;
        voisin = nPrec -> voisins;
        while (voisin) {
          if (n == voisin -> nd) estDejaVoisin = 1;
          voisin = voisin -> suiv;
        }
        if (!estDejaVoisin) {
          /* 1. Ajouter nPrec comme un voisin de n */
          cn = (CellNoeud *)malloc(sizeof(CellNoeud));
          cn -> nd = nPrec;
          cn -> suiv = n -> voisins;
          n -> voisins = cn;
          /* 2. Ajouter n comme un voisins de nPrec */
          cn = (CellNoeud *)malloc(sizeof(CellNoeud));
          cn -> nd = n;
          cn -> suiv = nPrec -> voisins;
          nPrec -> voisins = cn;
        }
      }
      /* On teste si ce noeud est l'extrA */
      if (numP == 0) {
        ccommo -> extrA = n;
      } 
      numP++;
      cp = cp -> suiv;
    }
    /* On ajoute le commodite dans la liste */
    ccommo -> extrB = n;
    ccommo -> suiv = r -> commodites;
    r -> commodites = ccommo;
    
    cc = cc -> suiv;
  }
  
  return r;
}


int nbCommodites(Reseau *R){
    
    if(!R) return 0;
    
    CellCommodite* k = R -> commodites;
    
    int res = 0;
    while (k != NULL){
        res++;
        k = k -> suiv;
    }
    
    return res;
}


int nbLiaisons(Reseau * R){
    
    if(!R) return 0;
    
    CellNoeud * n = R -> noeuds;
    CellNoeud * v = NULL;
    
    int res = 0;
    while(n != NULL){
        v = n -> nd -> voisins;
        while(v != NULL){
            if( (v -> nd -> num) < (n -> nd -> num)){
                res++;
            }
            v = v -> suiv;
        }
        n = n -> suiv;
    }
    return res;
    
}


void ecrireReseau(Reseau *R, FILE *f){
    if(R == NULL) return;
    
    fprintf(f, "NbNoeuds : %d\n", R -> nbNoeuds);
    fprintf(f, "NbLiaisons : %d\n", nbLiaisons(R));
    fprintf(f, "NbCommodites : %d\n", nbCommodites(R));
    fprintf(f, "Gamma : %d\n\n", R -> gamma);
    
    CellNoeud * cn = R -> noeuds;
    Noeud * n = NULL;
    while (cn != NULL) {
        n = cn -> nd;
        fprintf(f, "v %d %.6f %.6f\n", n -> num, n -> x, n -> y);
        cn = cn -> suiv;
    }
    fprintf(f, "\n");
    
    cn = R -> noeuds;
    CellNoeud * voisins = NULL;
    n = NULL;
    Noeud * nv = NULL;
    while (cn != NULL) {
        n = cn -> nd;
        voisins = n -> voisins;
        while(voisins != NULL){
            nv = voisins -> nd;
            if(nv -> num < n -> num){
                fprintf(f, "l %d %d\n", nv -> num, n -> num);
            }
            voisins = voisins -> suiv;
        }
        cn = cn -> suiv;
    }
    fprintf(f, "\n");
    
    CellCommodite * k = R -> commodites;
    Noeud * ndA = NULL;
    Noeud * ndB = NULL;
    while (k != NULL) {
        ndA = k -> extrA;
        ndB = k -> extrB;
        fprintf(f, "k %d %d \n", ndA -> num, ndB -> num);
        k = k -> suiv;
    }
    
    return;
    
}


void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}
