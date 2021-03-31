//
//  MainReseau.c
//  
//
//  Created by Lucie Chen on 31/03/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"

int main (void){
    Reseau * r = (Reseau *)malloc(sizeof(Reseau));
    r -> nbNoeuds = 7;
    r -> gamma = 3;
    
    CellNoeud * cn1 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cn2 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cn3 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cn4 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cn5 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cn6 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cn7 = (CellNoeud *)malloc(sizeof(CellNoeud));

    Noeud * n1 = (Noeud *)malloc(sizeof(Noeud));
    Noeud * n2 = (Noeud *)malloc(sizeof(Noeud));
    Noeud * n3 = (Noeud *)malloc(sizeof(Noeud));
    Noeud * n4 = (Noeud *)malloc(sizeof(Noeud));
    Noeud * n5 = (Noeud *)malloc(sizeof(Noeud));
    Noeud * n6 = (Noeud *)malloc(sizeof(Noeud));
    Noeud * n7 = (Noeud *)malloc(sizeof(Noeud));
    
    //Premier point
    CellNoeud * cnv1 = (CellNoeud *)malloc(sizeof(CellNoeud));
    
    CellNoeud * cnv2 = (CellNoeud *)malloc(sizeof(CellNoeud));
    
    cnv1 -> nd = n5;
    cnv1 -> suiv = cnv2;
    
    cnv2 -> nd = n4;
    cnv2 -> suiv = NULL;
    
    cn1 -> nd = n1;
    cn1 -> suiv = cn2;
    n1 -> num = 1;
    n1 -> x = 1.1;
    n1 -> y = 1.2;
    n1 -> voisins = cnv1;

    //Deuxième point
    CellNoeud * cnv3 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cnv4 = (CellNoeud *)malloc(sizeof(CellNoeud));
    
    cnv3 -> nd = n3;
    cnv3 -> suiv = cnv4;
    
    cnv4 -> nd = n4;
    cnv4 -> suiv = NULL;
    
    cn2 -> nd = n2;
    cn2 -> suiv = cn3;
    n2 -> num = 2;
    n2 -> x = 2.1;
    n2 -> y = 2.2;
    n2 -> voisins = cnv3;
    
    //Troixième point
    CellNoeud * cnv5 = (CellNoeud *)malloc(sizeof(CellNoeud));
    
    cnv5 -> nd = n2;
    cnv5 -> suiv = NULL;
     
    cn3 -> nd = n3;
    cn3 -> suiv = cn4;
    n3 -> num = 3;
    n3 -> x = 3.1;
    n3 -> y = 3.2;
    n3 -> voisins = cnv5;

    //Quatrième point
    CellNoeud * cnv6 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cnv7 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cnv8 = (CellNoeud *)malloc(sizeof(CellNoeud));

    cnv6 -> nd = n2;
    cnv6 -> suiv = cnv7;
    
    cnv7 -> nd = n1;
    cnv7 -> suiv = cnv8;
    
    cnv8 -> nd = n6;
    cnv8 -> suiv = NULL;
    
    cn4 -> nd = n4;
    cn4 -> suiv = cn5;
    n4 -> num = 4;
    n4 -> x = 4.1;
    n4 -> y = 4.2;
    n4 -> voisins = cnv6;
    
    //Cinquième point
    CellNoeud * cnv9 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cnv10 = (CellNoeud *)malloc(sizeof(CellNoeud));

    cnv9 -> nd = n1;
    cnv9 -> suiv = cnv10;
    
    cnv10 -> nd = n6;
    cnv10 -> suiv = NULL;
    
    cn5 -> nd = n5;
    cn5 -> suiv = cn6;
    n5 -> num = 5;
    n5 -> x = 5.1;
    n5 -> y = 5.2;
    n5 -> voisins = cnv9;
    
    //Sixième point
    CellNoeud * cnv11 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cnv12 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud * cnv13 = (CellNoeud *)malloc(sizeof(CellNoeud));

    cnv11 -> nd = n5;
    cnv11 -> suiv = cnv12;
    
    cnv12 -> nd = n4;
    cnv12 -> suiv = cnv13;
    
    cnv13 -> nd = n7;
    cnv13 -> suiv = NULL;

    cn6 -> nd = n6;
    cn6 -> suiv = cn7;
    n6 -> num = 6;
    n6 -> x = 6.1;
    n6 -> y = 6.2;
    n6 -> voisins = cnv11;
    
    //Troixième point
    CellNoeud * cnv14 = (CellNoeud *)malloc(sizeof(CellNoeud));
    
    cnv14 -> nd = n6;
    cnv14 -> suiv = NULL;
     
    cn7 -> nd = n7;
    cn7 -> suiv = NULL;
    n7 -> num = 7;
    n7 -> x = 7.1;
    n7 -> y = 7.2;
    n7 -> voisins = cnv14;
    
    r -> noeuds = cn1;
    
    CellCommodite * k1 = (CellCommodite *)malloc(sizeof(CellCommodite));
    CellCommodite * k2 = (CellCommodite *)malloc(sizeof(CellCommodite));
    CellCommodite * k3 = (CellCommodite *)malloc(sizeof(CellCommodite));
    CellCommodite * k4 = (CellCommodite *)malloc(sizeof(CellCommodite));
    
    k1 -> extrA = n1;
    k1 -> extrB = n6;
    k1 -> suiv = k2;
    
    k2 -> extrA = n3;
    k2 -> extrB = n7;
    k2 -> suiv = k3;
    
    k3 -> extrA = n2;
    k3 -> extrB = n5;
    k3 -> suiv = k4;
    
    k4 -> extrA = n1;
    k4 -> extrB = n7;
    k4 -> suiv = NULL;
    
    r -> commodites = k1;
    
    
    int nbL;
    nbL = nbLiaisons(r);
    int nbC;
    nbC = nbCommodites(r);
    printf("nbL = %d , nbC = %d",nbL, nbC);
    
    FILE * fOut = fopen("test", "w");
    ecrireReseau(r,fOut);
    
    afficheReseauSVG(r, "test");
}
