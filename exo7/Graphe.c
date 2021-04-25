#include <stdio.h>
#include "Graphe.h"
#include "Reseau.h"
#include "Chaine.h"


Graphe * creerGraphe(Reseau * r){
    //Nous allouons le Graphe g et initialisons les parametres prets dans Reseau r
    Graphe * g = (Graphe *)malloc(sizeof(Graphe));
    g -> nbsom = r -> nbNoeuds;
    g -> gamma = r -> gamma;
    g -> nbcommod = nbCommodites(r);
    
    //Nous cherchons a creer le tableau de sommets
    Sommet ** t_som = (Sommet **)malloc((g -> nbsom + 1) * sizeof(Sommet*));
    CellNoeud * cn = r -> noeuds;
    Noeud * nd = NULL;
    CellNoeud * voisins = NULL;
    int num = 0;
    
    //Pour cela, nous parcourons la liste de noeuds du reseau
    while(cn != NULL){
        nd = cn -> nd;
        voisins = nd -> voisins;
        //Nous creons le sommet
        Sommet * s = (Sommet *)malloc(sizeof(Sommet));
        s -> num = nd -> num;
        s -> x = nd -> x;
        s -> y = nd -> y;
        
        //Nous cherchons a trouver la liste de voisins de chaque sommet a partir de la liste de voisins du reseau
        Cellule_arete * ca = (Cellule_arete *)malloc(sizeof(Cellule_arete));
        while (voisins) {
            num = voisins -> nd -> num;
            //Nous comparons les numeros des sommets pour determiner si on a deja vu le voisin
            if(num <= nd -> num){ //Si c'est la première fois qu'on rencontre cet arete, nous allouons l'arete et nous l'initialisons
                Arete * a_nouv = (Arete *)malloc(sizeof(Arete));
                a_nouv -> u = nd -> num;
                a_nouv -> v = num;
            } else {    // si ce n'est pas la première fois, nous le trouvons dans la liste des voisins du sommet u
                Sommet * voisin_deja_vu = t_som[num];
                while(voisin_deja_vu -> L_voisin != NULL){
                    Arete * a_vvoisin = voisin_deja_vu -> L_voisin -> a;
                    //On cherche l'arete qui a pour numero = le numero du sommet v
                    Arete * a_nouv = NULL;
                    if(a_vvoisin -> v == num){
                        a_nouv = a_vvoisin;
                    }
                    voisin_deja_vu -> L_voisin = voisin_deja_vu -> L_voisin -> suiv;
                }
            }
            //Nous ajoutons l'arete dans la liste de voisins
            Cellule_arete * ca2 = (Cellule_arete *)malloc(sizeof(Cellule_arete));
            ca2 -> a = a_nouv;
            ca2 -> suiv = ca;
            ca = ca2;
        }
        //Nous ajoutons le sommet dans le tableau de sommets
        t_som[s -> num] = s;
        cn = cn -> suiv;
    }
    
    g -> T_som = t_som;
    
    //Nous cherchons a creer la liste de comodites en parcourant la liste de commodites du reseau
    Commod * t_commod = (Commod *)malloc(g -> nbcommod * sizeof(Commod));
    CellCommodite * commodites = r -> commodites;
    int i = 0;
    while(commodites != NULL){
        Commod k;
        k.e1 = commodites -> extrA -> num;
        k.e2 = commodites -> extrB -> num;
        t_commod[i] = k;
        i++;
        commodites = commodites -> suiv;
    }
    
    g -> T_commod = t_commod;

    //Finalement, nous avons initialise tous les parametres du graphe, nous le retournons.
    return g;
}


//Question 7.2

int plusPetitNbAretes(Graphe * G, int r, int s){
    //Nous initialisons un tableau visit qui nous donne la longueur de la chaîne de r à visit[i]
    int visit[G -> nbsom];
    int i;
    for (i = 0; i < G -> nbsom; i++){
        visit[i] = 0;
    }
    //Nous initialisons la bordure du graphe avec une file
    S_file * F = (S_file *)malloc(sizeof(S_file));
    Init_file(F);
    enfile(F,r);

    while(!estFileVide(F)){
        //A chaque fois on prend un sommet u et on regarde ses sommets adjacents
        int u = defile(F);
        /*printf("%d ", u);*/
        
        //Nous regardons les aretes du sommet u
        Cellule_arete * voisins = G -> T_som[u] -> L_voisin;
        while(voisins != NULL){
            //Nous choisissont le bon sommet v de l'arete, exemple arete 1-4, si u = 4, nous retournons 1 et sinon , nous retournons 4.
            int v = 0;
            if(voisins -> a -> v == u){
                v = voisins -> a -> u;
            } else {
                v = voisins -> a -> v;
            }
            //Si nous n'avons jamais parcouru le sommet (visit[v] == 0) ou s'il est different du sommet de depart (racine)
            if(visit[v] == 0 && v != r){
                //Nous incrementons de 1 par rapport a son element precedent dans le tableau visit
                visit[v] = visit[u] + 1;
                enfile(F,v);
                //Si on est arrivée au sommet target, nous retournons la distance entre r et s, en prenant le plus cours chemin entre les deux sommets.
                if(v == s){
                    while(F -> tete != NULL){
                        defile(F);
                    }
                    free(F);
                    return visit[s];
                }
            }
            voisins = voisins -> suiv;
        }

    }
}

//Question 7.3

ListeEntier * plusCourteChaineUV(Graphe * G, int r, int s){
    //Nous reprennons la fonction plusPetitNbAretes et nous la modifions pour qu'il retourne la chaîne entre r et s
    //Pour cela, nous utiliserons une liste d'entiers, nous la declarons et initialisons
    ListeEntier * res = (ListeEntier *)malloc(sizeof(ListeEntier));
    Init_Liste(res);
    
    int visit[G -> nbsom];
    //Nous creons un tableau prec pour pouvoir retourner du sommet v au sommet u et remplir notre liste d'entiers
    int prec[G -> nbsom];
    int i;
    for (i = 0; i < G -> nbsom; i++){
        visit[i] = 0;
        //Nous initialisons prec
        prec[i] = -1;
    }
    S_file * F = (S_file *)malloc(sizeof(S_file));
    Init_file(F);
    enfile(F,r);

    while(!estFileVide(F)){
        int u = defile(F);
        Cellule_arete * voisins = G -> T_som[u] -> L_voisin;
        while(voisins != NULL){
            int v = 0;
            if(voisins -> a -> v == u){
                v = voisins -> a -> u;
            } else {
                v = voisins -> a -> v;
            }
            if(visit[v] == 0 && v != r){
                visit[v] = visit[u] + 1;
                enfile(F,v);
                
                //Nous mettons le sommet antecedent de v dans la case v dans prec
                if(prec[v] == -1){
                    prec[v] = u;
                }
                //Si on a atteint le sommet target, nous n'avons plus besoin du reste.
                if(v == s){
                    int temp = s;
                    //A chaque tour, nous revennons "a l'arriere" grace au tableau prec et on obtiendra la liste d'entiers de la plus courte chaine de u a v.
                    while(prec[temp] != -1){
                        ajoute_en_tete(res, temp);
                        temp = prec[temp];
                    }
                    ajoute_en_tete(res,temp);
                    return res;
                }
            }
            voisins = voisins -> suiv;
        }

    }
}

//Question 7.4.

int reorganiseReseau(Reseau * r){
    Graphe * g = creerGraphe(r);
    //On déclare et initialise la matrice
    int ** matArete = (int **)malloc(g -> nbsom * sizeof(int*));
    if(matArete == NULL){    //si l'allocation échoue
        return -1;
    }
    for (int i = 0; i < g -> nbsom; i++){
        matArete[i] = (int *)malloc(g -> nbsom * sizeof(int));
        if(matArete[i] == NULL){
            for(int j = 0; j < i; i++){
                free(matArete[j]);
                
            }
            free(matArete);
            return -1;
        }
    }
    for(int j = 0; j < g -> nbsom; j++){
        for(int k = 0; k < g -> nbsom; k++){
            matArete[j][k] = 0;
        }
    }
    
    //On parcours la table de commodites
    Commod * tabCommod = g -> T_commod;
    Commod k;
    for(int l = 0; l < g -> nbcommod; l++){
        k = tabCommod[l];
        //On regarde la plus courte chaine qui relie les deux extremites de la commodite
        ListeEntier * LEtemp = plusCourteChaineUV(g, k.e1, k.e2);
        ListeEntier * parcours = LEtemp;
        //Nous ajoutons les aretes dans la matrice matArete
        while(parcours != NULL){
            matArete[parcours -> u][parcours -> suiv -> u];
            parcours = parcours -> suiv;
        }
        desalloue(LEtemp);
    }
    
    //Nous comptons pour chaque couple de sommets, le nombre de chaines qui passent par l'arete qui les relie
    int aretes = 0;
    for (int m = 0; m < g -> nbsom; m++){
        for(int n = m; n < g -> nbsom; n++){
            aretes = matArete[m][n] + matArete[n][m];
            //Si le nombre est superieur a gamma, on retoune Faux
            if(aretes > g -> gamma){
                freeMAT(matArete, g -> nbsom);
                return 0;
            }
        }
    }
    
    freeMAT(matArete, g -> nbsom);
    //On retourne vrai si gamma est bien respectee.
    return 1;
    
}

void freeMAT(int ** matrice, int taille){
    for(int i = 0; i < taille; i++){
        free(matrice[i]);
    }
    free(matrice);
}
