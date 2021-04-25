#include <math.h>
#include <stdlib.h>
#include "Hachage.h"


/* Q 4.2 */
void libereTableHachage(TableHachage * H) {
    if (!H) return ;
    
    CellNoeud * cnCour = NULL;
    CellNoeud * cnPrec = NULL;
    for (int i = 0 ; i < H -> m ; i++) {
        cnPrec = NULL;
        cnCour = (H -> tabN)[i];
        while (cnCour) {
            cnPrec = cnCour;
            cnCour = cnCour -> suiv;
            free(cnPrec);
        }
    }
    
    free(H -> tabN);
    free(H);
}

double fonctionClef(double x, double y){
    return y + (x + y) * (x + y + 1) * 1.0 / 2;
}


/* Q 4.3 */
int fonctionHachage(double k, int m) {
  double A = (sqrt(5) - 1) / 2;
  return ((int)(m * (k * A - ((long int)(k * A)))));/////////////////
}


/* Q 4.4 */
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){

    double clef = fonctionClef(x,y);
    int index = fonctionHachage(clef, H -> m);
    CellNoeud * CNoeudH = (H -> tabN)[index];
    Noeud * NoeudH = NULL;

    //Nous comparons les coordonnes de NoeudH dans la liste CNoeudH avec x et y passés en paramètres
    while(CNoeudH != NULL){
        NoeudH = CNoeudH -> nd;

        if((NoeudH -> x) == x && (NoeudH -> y) == y) return NoeudH;
        CNoeudH = CNoeudH -> suiv;
    }

    //Dans le cas où le noeuds de coordonnees (x,y) n'est pas dans la table, nous la rajoutons dans la table de hachage et dans la liste
    Noeud * NoeudNouv = (Noeud *)malloc(sizeof(Noeud));
    NoeudNouv -> num = ((R -> nbNoeuds) + 1);
    NoeudNouv -> x = x;
    NoeudNouv -> y = y;
    NoeudNouv -> voisins = NULL;

    /* L'ajouter dans la liste */
    CellNoeud * CNouvL = (CellNoeud*)malloc(sizeof(CellNoeud));
    CNouvL -> nd = NoeudNouv;
    CNouvL -> suiv = R -> noeuds;
    R -> noeuds = CNouvL;
    R -> nbNoeuds++;

    /* L'ajouter dans la table de hachage */
    CellNoeud * CNouvH = (CellNoeud*)malloc(sizeof(CellNoeud));
    CNouvH -> nd = NoeudNouv;
    CNouvH -> suiv = (H -> tabN)[index];
    (H -> tabN)[index] = CNouvH;
    H -> nE++;

    return NoeudNouv;
    
}


/* Q 4.5 */
Reseau* reconstitueReseauHachage(Chaines *C, int M){
    if(!C) return NULL;

    /* Declarer et initialiser la table hachage et le reseau */
    TableHachage * H = (TableHachage *)malloc(sizeof(TableHachage));
    H -> nE = 0;
    H -> m = M;
    H -> tabN = (CellNoeud**)malloc(M * sizeof(CellNoeud*));

    for (int i = 0 ; i < M ; i++) (H -> tabN[i]) = NULL;
    
    Reseau * r = (Reseau *)malloc(sizeof(Reseau));
    r -> gamma = C -> gamma;
    r -> nbNoeuds = 0;
    r -> noeuds = NULL;
    r -> commodites = NULL;
    
    CellChaine * cc = C -> chaines;
    CellPoint * cp = NULL;

    while(cc){
        /* Nous traitons d'abord le cas des extrimites de chaines (commodite) */
        CellCommodite * k = (CellCommodite*)malloc(sizeof(CellCommodite));
        cp = cc -> points;
        Noeud * noeudAjouter = rechercheCreeNoeudHachage(r, H, cp -> x, cp -> y);
        Noeud * noeudPrec = NULL;
        //commodite extrA
        k -> extrA = noeudAjouter;
        cp = cp -> suiv;
        
        while(cp){
            /* Nous gardons à chaque fois, le dernier noeudAjouter pour déterminer les voisins. */
            noeudPrec = noeudAjouter;
            noeudAjouter = rechercheCreeNoeudHachage(r, H, cp -> x, cp -> y);
            
            insereVoisin(&(noeudPrec -> voisins), noeudAjouter);
            insereVoisin(&(noeudAjouter -> voisins), noeudPrec);
            
            cp = cp -> suiv;
        }
        //commodite extrB
        k -> extrB = noeudAjouter;
        k -> suiv = r -> commodites;
        r -> commodites = k;
        
        cc = cc -> suiv;
    }
    
    libereTableHachage(H);
    return r;
}
