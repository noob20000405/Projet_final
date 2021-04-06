#include <math.h>
#include "Hachage.h"
#include <stdlib.h>


double fonctionClef(double x, double y){
    return y + (x + y) * (x + y + 1) / 2;
}


int fonctionHachage(double k, int m) {
  double A = (sqrt(5) - 1) / 2;
  return ((int)(m * (k * A - ((int)(k * A)))));
}


//incrementer r -> nbNoeuds;
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){
    double clef = fonctionClef(x,y);
    int index = fonctionHachage(clef, H -> m);
    int num = 1;
    CellNoeud ** tab_CNouedsH = H -> tabN;
    CellNoeud * CNoeudH = tab_NouedsH[index];
    Noeud * NoeudH = NULL;
    
    //Nous comparons les coordonnes de NoeudH dans la liste CNoeudH avec x et y passés en paramètres
    while(CNoeudH != NULL){

        if((NoeudH -> x = x) && (NoeudH -> y = y)){
            return NoeudH;
        }
        CNoeudH = CNoeudH -> suiv;
    }
    
    //Dans le cas où le noeuds de coordonnees (x,y) n'est pas dans la table, nous la rajoutons
    Noeud * NoeudNouv = (Noeud *)malloc(sizeof(Noeud));
    NoeudNouv -> num = (R -> NoeudNouv + 1);
    NoeudNouv -> x = x;
    NoeudNouv -> y = y;
    NoeudNouv -> voisins = NULL;
    
    CellNoeud * CNnouv = (CellNoeud*)malloc(sizeof(CellNoeud));
    CNouv -> nd = NoeudNouv;
    CNouv -> suiv = R -> noeuds;
    R -> noeuds = CNouv;
    R -> nbNoeuds++;
    
    CNouv -> suiv = CNoeudH;
    CNoeudH = CNouv;
    
    
    return NoeudNouv;
    
}


Reseau* reconstitueReseauHachage(Chaines *C, int M){
    if(!C) return NULL;
    
    TableHachage * H = (TableHachage *)malloc(sizeof(TableHachage));
    H -> nE = 0;
    H -> m = M;
    H -> tabN = (CellNoeud**)malloc(sizeof(M * CellNoeud*));
    
    Reseau * r = reconstitueReseauListe(C);
    r -> gamma = C -> gamma;
    r -> nbNoeuds = 0;
    r -> noeuds = NULL;
    r -> commodites = NULL;
    
    
    CellChaine * cc = C -> chaines;
    CellPoint * cp = NULL;
    int estDejaVoisin = 0;
    while(cc){
        /* Nous traitons d'abord le cas des extrimites de chaines (commodite) */
        CellCommodite * k = (CellCommodite*)malloc(sizeof(CellCommodite));
        cp = cp -> points;
        Noeud * noeudAjouter = rechercheCreeNoeudHachage(r, H, x, y);
        //commodite extrA
        k -> extrA = noeudAjouter;
        cp = cp -> suiv;
        
        Noeud * noeudPrec = NULL;
        while(cp){
            /* Nous gardons à chaque fois, le dernier noeudAjouter pour déterminer les voisins. */
            noeudPrec = noeudAjouter;
            noeudAjouter = rechercheCreeNoeudHachage(r, H, x, y);
            
            /*Mettre à jour la liste de voisins de noeudPrec et noeudAjouter*/
            CellNoeud * voisinParcours = noeudPrec -> voisins;
            while(voisinParcours){
                if(voisinParcours -> nd == noeudAjouter){
                    estDejaVoisin = 1;
                }
                voisinParcours = voisinParcours -> suiv;
            }
            
            if(!estDejaVoisin){
                /* 1. Ajouter noeudAjouter comme voisin de noeudPrec */
                CellNoeud * voisinPrec = (CellNoeud*)malloc(sizeof(CellNoeud));
                voisinPrec -> nd = noeudAjouter;
                voisinPrec -> suiv = noeudPrec -> voisins;
                noeudPrec -> voisins = voisinPrec;
                /* 2. Ajouter noeudPrec comme voisin de noeudAjouter */
                CellNoeud * voisinAjouter = (CellNoeud*)malloc(sizeof(CellNoeud));
                voisinAjouter -> nd = noeudPrec;
                voisinAjouter -> suiv = noeudAjouter -> voisins;
                noeudAjouter -> voisins = voisinAjouter;
            }
            
            cp = cp -> suiv;
        }
        //commodite extrB
        k -> extrB = noeudAjouter;
        k -> suiv = r -> commodites;
        r -> commodites = k;
        
        cc = cc -> suiv;
    }
    return r;
}


