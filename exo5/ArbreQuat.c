#include <stdio.h>
#include <stdlib.h>
#include "ArbreQuat.h"
#include "Chaine.h"
#include "Reseau.h"


void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax) {
    if (!C || !xmin || !ymin || !xmax || !ymax) return ;
    
    CellChaine * cc = C -> chaines;
    CellPoint * cp = NULL;
    
    /* Initialiser les quatre valeurs */
    *xmin = cc -> points -> x;
    *ymin = cc -> points -> y;
    *xmax = cc -> points -> x;
    *ymax = cc -> points -> y;
    
    /* Parcourir la liste pour touver les mins et les maxs */
    while (cc) {
        cp = cc -> points;
        while (cp) {
            if (cp -> x < (*xmin)) (*xmin) = cp -> x;
            if (cp -> y < (*ymin)) (*ymin) = cp -> y;
            if (cp -> x > (*xmax)) (*xmax) = cp -> x;
            if (cp -> y > (*ymax)) (*ymax) = cp -> y;
            cp = cp -> suiv;
        }
        cc = cc -> suiv;
    }
}


ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY) {
    ArbreQuat * aq = (ArbreQuat *)malloc(sizeof(ArbreQuat));
    if (!aq) {
        printf("Erreur d'allocation.\n");
        return NULL;
    }
    
    aq -> xc = xc;
    aq -> yc = yc;
    aq -> coteX = coteX;
    aq -> coteY = coteY;
    
    aq -> noeud = NULL;
    aq -> so = NULL;
    aq -> se = NULL;
    aq -> no = NULL;
    aq -> ne = NULL;
    
    return aq;
}


void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent) {
    if (!n || !parent) return ;  
    
    //////////

    
    /* Premier cas */
    if ((*a) == NULL) {
    printf("insere 1 cas\n");
        /* Calculer la position du noeud dans l'arbre parent et creer une nouvelle cellule */
        double newCoteX = parent -> coteX * 1.0 / 2;
        double newCoteY = parent -> coteY * 1.0 / 2;
        double newXc, newYc;
        
        if (n -> x < parent -> xc) {
            newXc = parent -> xc - parent -> coteX * 1.0 / 4;
        } else {
            newXc = parent -> xc + parent -> coteX * 1.0 / 4;
        }
        if (n -> y < parent -> yc) {
            newYc = parent -> yc - parent -> coteY * 1.0 / 4;
        } else {
            newYc = parent -> yc + parent -> coteY * 1.0 / 4;
        }
      
        (*a) = creerArbreQuat(newXc, newYc, newCoteX, newCoteY);
        /* Ajouter le noeud dans la cellule */
        (*a) -> noeud = n;

        return ;
    }
    
    /* Deuxieme cas */
    if ((*a) -> noeud != NULL) {
    printf("insere 2 cas\n");
        Noeud * nAncien = (*a) -> noeud;
        printf("xc:%f, y:%f\n", (*a) -> xc, (*a) -> yc);/////////////
        /* Calculer la position d'inserer le noeud */
        if (n -> x < (*a) -> xc && n -> y < (*a) -> yc) {
        printf("nouv to 1\n");
            insererNoeudArbre(n, &((*a) -> so), (*a));
        }
        else if (n -> x >= (*a) -> xc && n -> y < (*a) -> yc) {
        printf("nouv to 2\n");
            insererNoeudArbre(n, &((*a) -> se), (*a));
        }
        else if (n -> x < (*a) -> xc && n -> y >= (*a) -> yc) {
        printf("nouv to 3\n");
            insererNoeudArbre(n, &((*a) -> no), (*a));
        }
        else {
        printf("nouv to 4\n");
            insererNoeudArbre(n, &((*a) -> ne), (*a));
        }
        
        /* Calculer la position d'inserer l'ancien noeud */   
        if (nAncien -> x < (*a) -> xc && nAncien -> y < (*a) -> yc) {
        printf("anc to 1\n");
            insererNoeudArbre(nAncien, &((*a) -> so), (*a));
        }
        else if (nAncien -> x >= (*a) -> xc && nAncien -> y < (*a) -> yc) { 
        printf("anc to 2\n");
            insererNoeudArbre(nAncien, &((*a) -> se), (*a));
        }
        else if (nAncien -> x < (*a) -> xc && nAncien -> y >= (*a) -> yc) {
        printf("anc to 3\n");
            insererNoeudArbre(nAncien, &((*a) -> no), (*a));
        }
        else {
        printf("anc to 4\n");
            insererNoeudArbre(nAncien, &((*a) -> ne), (*a));
        }
        
        /* Initialiser l'ancien noeud */
        (*a) -> noeud = NULL;///////////////move to here, but nothing change
        return ;
    }
    
    /* Troisieme cas : (*a) -> noeud == NULL */
    printf("insere 3 cas\n");
    printf("xc:%f, y:%f\n", (*a) -> xc, (*a) -> yc);/////////////
    if (n -> x < (*a) -> xc && n -> y < (*a) -> yc) {
        insererNoeudArbre(n, &((*a) -> so), (*a));
    }
    else if (n -> x >= (*a) -> xc && n -> y < (*a) -> yc) {
        insererNoeudArbre(n, &((*a) -> se), (*a));
    }
    else if (n -> x < (*a) -> xc && n -> y >= (*a) -> yc) {
        insererNoeudArbre(n, &((*a) -> no), (*a));
    }
    else {
        insererNoeudArbre(n, &((*a) -> ne), (*a));
    }
}


Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y) {
    ArbreQuat * arbre = *a;
    
    /* Premier cas */
    if (arbre == NULL) {
    printf("recherche 1 cas\n");
        /* Creer un noeud nouveau */
        Noeud * n = (Noeud *)malloc(sizeof(Noeud));
        n -> num = (R -> nbNoeuds) + 1;
        n -> x = x;
        n -> y = y;
        n -> voisins = NULL;
        
        /* L'inserer dans la liste */
        CellNoeud * cn = (CellNoeud *)malloc(sizeof(CellNoeud));
        cn -> nd = n;
        cn -> suiv = R -> noeuds;
        R -> noeuds = cn;
        R -> nbNoeuds++;
        
        /* L'inserer dans l'arbreQuat */
        insererNoeudArbre(n, &(*a), parent);/////////////

        return n;
    }
    
    /* Deuxieme cas */
    if (arbre -> noeud != NULL) {
        if (arbre -> noeud -> x == x && arbre -> noeud -> y == y) {
        printf("recherche 2 cas, colli\n");
            return arbre -> noeud;
        }
        printf("recherche 2 cas, non colli\n");
        /* Creer un noeud nouveau */
        Noeud * n = (Noeud *)malloc(sizeof(Noeud));
        n -> num = (R -> nbNoeuds) + 1;
        n -> x = x;
        n -> y = y;
        n -> voisins = NULL;
        
        /* L'inserer dans la liste */
        CellNoeud * cn = (CellNoeud *)malloc(sizeof(CellNoeud));
        cn -> nd = n;
        cn -> suiv = R -> noeuds;
        R -> noeuds = cn;
        R -> nbNoeuds++;
        
        /* L'inserer dans l'arbreQuat */
        insererNoeudArbre(n, &(*a), parent);

        return n;
    }
    
    /* Troisieme cas */
    printf("recherche 3 cas\n");
    printf("xc:%f, y:%f\n", (*a) -> xc, (*a) -> yc);/////////////
    if (x < arbre -> xc && y < arbre -> yc) {
    printf("to 1;\n");
        rechercheCreeNoeudArbre(R, &(arbre -> so), arbre, x, y);
        
    }
    else if (x >= arbre -> xc && y < arbre -> yc) {
    printf("to 2;\n");
        rechercheCreeNoeudArbre(R, &(arbre -> se), arbre, x, y);
        
    }
    else if (x < arbre -> xc && y >= arbre -> yc) {
    printf("to 3;\n");
        rechercheCreeNoeudArbre(R, &(arbre -> no), arbre, x, y);
        
    }
    else {
    printf("to 4;\n");
        rechercheCreeNoeudArbre(R, &(arbre -> ne), arbre, x, y);
        
    }
}


Reseau* reconstitueReseauArbre(Chaines* C) {
    if (!C) return NULL;
    
    /* Creer le reseau */
    Reseau * r = (Reseau *)malloc(sizeof(Reseau));
    r -> gamma = C -> gamma;
    r -> nbNoeuds = 0;
    r -> noeuds = NULL;
    r -> commodites = NULL;
    Noeud * nAjoute = NULL;
    Noeud * nPrec = NULL;
    
    CellChaine * cc = C -> chaines;
    CellPoint * cp = NULL;
    
    /* Creer la racine de l'arbre */
    double xmin, ymin, xmax, ymax;
    chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
    ArbreQuat * a = creerArbreQuat((xmin + xmax) * 1.0 / 2, (ymin + ymax) * 1.0 / 2, xmax - xmin, ymax - ymin);

    /* Parcourir les chaines */
    while (cc) {
    
        /* Nous traitons d'abord le cas des extrimites de chaines (commodite) */
        CellCommodite * k = (CellCommodite*)malloc(sizeof(CellCommodite));
        cp = cc -> points;

        if ((cp -> x) < (a -> xc) && (cp -> y) < (a -> yc)) {
        printf("1\n");
            nAjoute = rechercheCreeNoeudArbre(r, &(a -> so), a, cp -> x, cp -> y);
        } else if ((cp -> x) >= (a -> xc) && (cp -> y) < (a -> yc)) {
        printf("2\n");
            nAjoute = rechercheCreeNoeudArbre(r, &(a -> se), a, cp -> x, cp -> y);
        } else if ((cp -> x) < (a -> xc) && (cp -> y) >= (a -> yc)) {
        printf("3\n");
            nAjoute = rechercheCreeNoeudArbre(r, &(a -> no), a, cp -> x, cp -> y);
        } else {
        printf("4\n");
            nAjoute = rechercheCreeNoeudArbre(r, &(a -> ne), a, cp -> x, cp -> y);////////////////
        }
    printf("x:%f, y:%f\n\n", cp->x, cp->y);///////////////////
        cp = cc -> points;
        //commodite extrA
        k -> extrA = nAjoute;
        cp = cp -> suiv;
        
        while (cp) {
            /* Ajouter ce noeud dans la liste */
            /* Nous gardons à chaque fois, le dernier noeudAjouter pour déterminer les voisins. */
            nPrec = nAjoute;
            
            if (cp -> x < a -> xc && cp -> y < a -> yc) {
            printf("1\n");
                nAjoute = rechercheCreeNoeudArbre(r, &(a -> so), a, cp -> x, cp -> y);
            } else if (cp -> x >= a -> xc && cp -> y < a -> yc) {
            printf("2\n");
                nAjoute = rechercheCreeNoeudArbre(r, &(a -> se), a, cp -> x, cp -> y);
            } else if (cp -> x < a -> xc && cp -> y >= a -> yc) {
            printf("3\n");
                nAjoute = rechercheCreeNoeudArbre(r, &(a -> no), a, cp -> x, cp -> y);
            } else {
            printf("4\n");
                nAjoute = rechercheCreeNoeudArbre(r, &(a -> ne), a, cp -> x, cp -> y);////////////////
            }
            
            
            /* Ajouter les voisins */
            insereVoisin(&(nPrec -> voisins), nAjoute);
            insereVoisin(&(nAjoute -> voisins), nPrec);
            printf("x:%f, y:%f\n\n", cp->x, cp->y);///////////////////
            cp = cp -> suiv;
            
        }
        
        //commodite extrB
        k -> extrB = nAjoute;
        k -> suiv = r -> commodites;
        r -> commodites = k;
        
        cc = cc -> suiv;
    }
    
    libereArbreQuat(a);
    return r;
}

void libereArbreQuat(ArbreQuat * a) {
    if (a == NULL) return ;
    
    if (a -> noeud != NULL) {
        free(a);
        return ;
    }
    
    libereArbreQuat(a -> so);
    libereArbreQuat(a -> se);
    libereArbreQuat(a -> no);
    libereArbreQuat(a -> ne);
}
