#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"
#include "SVGwriter.h"


/* Q 2.1 */
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y) {
  if (!R) return NULL;

  CellNoeud * cn = R -> noeuds;
  /* On parcourt la liste pour trouver le noeud qui correspond aux coordonnees (x,y)*/
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

/* Fonction qui permet d'inserer un noeud dans une liste des voisins */
void insereVoisin(CellNoeud ** L, Noeud * n) {
    CellNoeud * voisin = (*L);
    
    /* Parcourt la liste des voisins */
    while ((voisin != NULL) && (voisin -> nd != n)) voisin = voisin -> suiv;
    
    /* Si ce noeud n'est pas dans la liste, on l'ajoute */
    if (!voisin) {
        voisin = (CellNoeud *)malloc(sizeof(CellNoeud));
        voisin -> nd = n;
        voisin -> suiv = (*L);
        (*L) = voisin;
    }
}


/* Q 2.2 */
Reseau* reconstitueReseauListe(Chaines *C) {
  if (!C) return NULL;

  /* Creer le reseau */
  Reseau * r = (Reseau *)malloc(sizeof(Reseau));

  r -> nbNoeuds = 0;
  r -> gamma = C -> gamma;
  r -> commodites = NULL;
  r -> noeuds = NULL;

  CellCommodite * ccommo = NULL;
  Noeud * n  = NULL;
  Noeud * nPrec = NULL;
	
  CellChaine * cc = C -> chaines;
  CellPoint * cp = NULL;

  while (cc) {
    cp = cc -> points;
    nPrec = NULL;
    n = NULL;

    /* On cree une commodite chaque fois au debut d'un parcourt d'une chaine */
    ccommo = (CellCommodite *)malloc(sizeof(CellCommodite));

    while (cp) {
      /* On conserve le noeud precedent */
      nPrec = n;
      /* On cree un noeud et l'ajoute dans le reseau */
      n = rechercheCreeNoeudListe(r, cp -> x, cp -> y);

      /* On ajoute les voisins si ce noeud n'est pas le premier dans une chaine */
      if (nPrec) {
        insereVoisin(&(nPrec -> voisins), n);
        insereVoisin(&(n -> voisins), nPrec);
      } else {
        /* Si ce noeud est le premier dans une chaine, alors il est l'extrA */
        ccommo -> extrA = n;
      }

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


/* Q 3.1 */
int nbCommodites(Reseau *R){
    
    if(!R) return 0;
    
    CellCommodite* k = R -> commodites;
    
    int res = 0;
    //Nous incrementons le resultat de 1 à chaque tour sur la liste de commodites
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
	    //Sachant qu'un cable apparait 2 fois et que les noeuds sont classes par ordre decroissant, en faisant la comparaison, nous ne prenons pas en compte le doublon
            if( (v -> nd -> num) < (n -> nd -> num)){
                res++;
            }
            v = v -> suiv;
        }
        n = n -> suiv;
    }
    return res;
}


/* Q 3.2 */
void ecrireReseau(Reseau *R, FILE *f){
    if(R == NULL) return;
    
    fprintf(f, "NbNoeuds : %d\n", R -> nbNoeuds);
    fprintf(f, "NbLiaisons : %d\n", nbLiaisons(R));
    fprintf(f, "NbCommodites : %d\n", nbCommodites(R));
    fprintf(f, "Gamma : %d\n\n", R -> gamma);
    
    /* On ecrit les coordonees des noeuds */
    CellNoeud * cn = R -> noeuds;
    Noeud * n = NULL;
    while (cn != NULL) {
        n = cn -> nd;
        fprintf(f, "v %d %.6f %.6f\n", n -> num, n -> x, n -> y);
        cn = cn -> suiv;
    }
    fprintf(f, "\n");
    
    /* On ecrit les liasons (cables) */
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
    
    /* On ecrit les commodites */
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


/* Q 3.3 */
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

void libereReseauListe(Reseau * R) {
    if (!R) return ;
    
    /* Liberer les commodites */
    CellCommodite * commoCour = NULL;
    CellCommodite * commoSuiv = R -> commodites;
    
    while (commoSuiv) {
        commoCour = commoSuiv;
        commoSuiv = commoSuiv -> suiv;
        free(commoCour);
    }
    
    /* Liberer les cellNoeuds et les noeuds */
    CellNoeud * cnCour = NULL;
    CellNoeud * cnSuiv = R -> noeuds;
    CellNoeud * voisinCour = NULL;
    CellNoeud * voisinSuiv = NULL;
    
    while (cnSuiv) {
        cnCour = cnSuiv;
        cnSuiv = cnSuiv -> suiv;

        /* Liberer tous les voisins du noeud */
        voisinSuiv = cnCour -> nd -> voisins;
        while (voisinSuiv) {
            voisinCour = voisinSuiv;
            voisinSuiv = voisinSuiv -> suiv;
            free(voisinCour);
        }
            
        /* Liberer ce noeud */
        free(cnCour -> nd);
        
        /* Liberer ce CellNoeud */
        free(cnCour);
    }

    free(R);
}
