#include <stdio.h>
#include "Reseau.h"


int nbCommodites(Reseau *R){
    
    if(!R) return 0;
    
    CellCommodite* k = R -> commodites;
    
    int res = 0;
    while (!k){
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
    while(!n){
        v = n -> nd -> voisins;
        while(!v){
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
    
    fprintf(f, "NbNoeuds : %d\n", R -> NbNoeuds);
    fprintf(f, "NbLiaisons : %d\n", nbLiaisons(R));
    fprintf(f, "NbCommodites : %d\n", NbCommodites(R));
    fprintf(f, "Gamma : %d\n", R -> gamma);
    
    CellNoeud * cn = R -> noeuds;
    Noeud * n = NULL;
    while (cn != NULL) {
        n = cn -> nd;
        fprintf(f, "v %d %.6f %.6f\n", n -> num, n -> x, n -> y);
        cn = cn -> suiv;
    }
    
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
    
    CellCommodite * k = R -> commodites;
    Noeud * ndA = NULL;
    Noeud * ndB = NULL;
    while (k != NULL) {
        ndA = k -> extrA;
        ndB = k -> extrB;
        fprintf(f, "k %d %d \n", ndA -> num, ndB -> num);
        k -> k -> suiv;
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
