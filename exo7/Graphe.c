#include <stdio.h>
#include <stdlib.h>

#include "Struct_File.h"
#include "Struct_Liste.h"
#include "Reseau.h"
#include "Chaine.h"
#include "Graphe.h"


/* Q 7.1 */
Graphe * creerGraphe(Reseau * r){
    //Nous allouons le Graphe g et initialisons les parametres prets dans Reseau r
    Graphe * g = (Graphe *)malloc(sizeof(Graphe));
    //Test malloc
    if(!g){
        printf("Erreur lors de l'allocation Graphe.\n");
        return NULL;
    }

    g -> nbsom = r -> nbNoeuds;
    g -> gamma = r -> gamma;
    g -> nbcommod = nbCommodites(r);

    //Nous cherchons a creer le tableau de sommets
    Sommet ** g_tabSommets = (Sommet **)malloc(((g -> nbsom) + 1) * sizeof(Sommet*));
    //Test malloc
    if(!g_tabSommets){
        free(g);
        printf("Erreur lors de l'allocation TableauSommets.\n");
        return NULL;
    }

    //Nous initialisons le tableau de sommets
    for(int i = 0 ; i < (g -> nbsom) + 1 ; i++){
        g_tabSommets[i] = NULL;
    }

    CellNoeud * r_cn = r -> noeuds;
    Noeud * r_nd = NULL;
    CellNoeud * r_voisins = NULL;
    int r_numVoisin = 0;

    //Pour cela, nous parcourons la liste de noeuds du reseau
    while(r_cn != NULL){
        r_nd = r_cn -> nd;
        r_voisins = r_nd -> voisins;

        //Nous creons le sommet
        Sommet * g_sommet = (Sommet *)malloc(sizeof(Sommet));
        //Test malloc
        if(!g_sommet){
            for(int i = 0; i < (g -> nbsom) + 1; i++){
                if(g_tabSommets[i]){
                    free(g_tabSommets[i]);
                }
            }
            free(g_tabSommets);
            free(g);
            printf("Erreur lors de l'allocation d'un sommet.\n");
            return NULL;
        }

        //Nous initialisons le numero de sommet par numero du noeud dans le reseau -1 car l'indice du tableau commence par 0
        g_sommet -> num = r_nd -> num;
        g_sommet -> x = r_nd -> x;
        g_sommet -> y = r_nd -> y;
        g_sommet -> L_voisin = NULL;

        while (r_voisins) {
            r_numVoisin = r_voisins -> nd -> num;
            Arete * g_areteNouv = NULL;

            //Nous comparons les numeros des sommets pour determiner si on a deja vu le voisin
            if(r_numVoisin <= r_nd -> num){ //Si c'est la première fois qu'on rencontre cet arete, nous allouons l'arete et nous l'initialisons
                g_areteNouv = (Arete *)malloc(sizeof(Arete));
                g_areteNouv -> u = r_nd -> num;
                g_areteNouv -> v = r_numVoisin;

            } else {    // si ce n'est pas la première fois, nous le trouvons dans la liste des voisins du sommet u
                Cellule_arete * g_cellAreteDejaVu = g_tabSommets[r_numVoisin] -> L_voisin;
                Arete * g_areteDejaVu = NULL;

                while(g_cellAreteDejaVu != NULL){
                    g_areteDejaVu = g_cellAreteDejaVu -> a;
                    //On cherche l'arete qui a pour numero = le numero du sommet v
                    if(g_areteDejaVu -> v == r_nd -> num){
                        g_areteNouv = g_areteDejaVu;
                        break;
                    }
                    g_cellAreteDejaVu = g_cellAreteDejaVu -> suiv;
                }
            }

            //Creer la cellule arete et ajouter l'arete dans cette cellule
            Cellule_arete * g_ca = (Cellule_arete *)malloc(sizeof(Cellule_arete));
            g_ca -> a = g_areteNouv;
            g_ca -> suiv = g_sommet -> L_voisin;
            g_sommet -> L_voisin = g_ca;

            r_voisins = r_voisins -> suiv;
        }
        //Nous ajoutons le sommet dans le tableau de sommets
        g_tabSommets[g_sommet -> num] = g_sommet;

        r_cn = r_cn -> suiv;
    }

    g -> T_som = g_tabSommets;

    //Nous cherchons a creer la liste de comodites en parcourant la liste de commodites du reseau
    Commod * g_tabCommod = (Commod *)malloc((g -> nbcommod) * sizeof(Commod));
    CellCommodite * r_commodites = r -> commodites;
    int i = 0;
    while(r_commodites != NULL){
        Commod g_k;
        g_k.e1 = r_commodites -> extrA -> num;
        g_k.e2 = r_commodites -> extrB -> num;
        g_tabCommod[i] = g_k;
        i++;

        r_commodites = r_commodites -> suiv;
    }

    g -> T_commod = g_tabCommod;

    //Finalement, nous avons initialise tous les parametres du graphe, nous le retournons.
    return g;
}



/* Q 7.2 */
int plusPetitNbAretes(Graphe * G, int r, int s){
    //Nous initialisons un tableau visit qui nous donne la longueur de la chaîne de r à visit[i]
    int visit[(G -> nbsom) + 1];
    int i;
    for (i = 0; i < G -> nbsom + 1; i++){
        visit[i] = 0;
    }
    //Nous initialisons la bordure du graphe avec une file
    S_file * F = (S_file *)malloc(sizeof(S_file));
    Init_file(F);
    enfile(F,r);

    while(!estFileVide(F)){
        //A chaque fois on prend un sommet u et on regarde ses sommets adjacents
        int u = defile(F);

        //Nous regardons les aretes du sommet u
        Cellule_arete * g_voisins = G -> T_som[u] -> L_voisin;

        while(g_voisins != NULL){
            //Nous choisissont le bon sommet v de l'arete, exemple arete 1-4, si u = 4, nous retournons 1 et sinon , nous retournons 4.
            int v = 0;
            if(g_voisins -> a -> v == u){
                v = g_voisins -> a -> u;
            } else {
                v = g_voisins -> a -> v;
            }

            //Si nous n'avons jamais parcouru le sommet (visit[v] == 0) ou s'il est different du sommet de depart (racine)
            if(visit[v] == 0 && v != r){
                //Nous incrementons de 1 par rapport a son element precedent dans le tableau visit
                visit[v] = visit[u] + 1;
                enfile(F,v);

                //Si on est arrivée au sommet target, nous retournons la distance entre r et s, en prenant le plus cours chemin entre les deux sommets.
                if(v == s){
                    while(!estFileVide(F)){
                        defile(F);
                    }
                    free(F);
                    return visit[s];
                }
            }
            g_voisins = g_voisins -> suiv;
        }

    }
    free(F);
    return visit[s];
}


/* Q 7.3 */
ListeEntier * plusCourteChaineUV(Graphe * G, int r, int s){
    //Nous reprennons la fonction plusPetitNbAretes et nous la modifions pour qu'il retourne la chaîne entre r et s
    //Pour cela, nous utiliserons une liste d'entiers, nous la declarons et initialisons
    ListeEntier * res = (ListeEntier *)malloc(sizeof(ListeEntier));
    Init_Liste(res);

    int visit[(G -> nbsom) + 1];
    //Nous creons un tableau prec pour pouvoir retourner du sommet v au sommet u et remplir notre liste d'entiers
    int prec[(G -> nbsom) + 1];
    int i;
    for (i = 0; i < (G -> nbsom) + 1; i++){
        visit[i] = 0;
        //Nous initialisons prec
        prec[i] = -1;
    }
    S_file * F = (S_file *)malloc(sizeof(S_file));
    Init_file(F);
    enfile(F,r);

    while(!estFileVide(F)){
        int u = defile(F);
        Cellule_arete * g_voisins = G -> T_som[u] -> L_voisin;

        while(g_voisins != NULL){
            int v = 0;
            if(g_voisins -> a -> v == u){
                v = g_voisins -> a -> u;
            } else {
                v = g_voisins -> a -> v;
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

                    /* Liberer la file */
                    while (!estFileVide(F)) {
                        defile(F);
                    }
                    free(F);

                    return res;
                }
            }
            g_voisins = g_voisins -> suiv;
        }

    }

    free(F);
    return res;
}


/* Q 7.4 */
int reorganiseReseau(Reseau * r){
    Graphe * g = creerGraphe(r);

    //On déclare et initialise la matrice
    int ** matArete = (int **)malloc(((g -> nbsom) + 1) * sizeof(int*));
    if(matArete == NULL){    //si l'allocation échoue
        libererGraphe(g);
        return -1;
    }

    for (int i = 0; i < (g -> nbsom) + 1; i++){
        matArete[i] = (int *)malloc(((g -> nbsom) + 1) * sizeof(int));
        /* si l'allocation échoue */
        if(matArete[i] == NULL){
            for(int j = 0; j < i; i++){
                free(matArete[j]);
            }
            libererGraphe(g);
            free(matArete);
            return -1;
        }
    }

    for(int i = 0; i < (g -> nbsom) + 1; i++){
        for(int j = 0; j < (g -> nbsom) + 1; j++){
            matArete[i][j] = 0;
        }
    }


    //On parcours la table de commodites
    Commod * tabCommod = g -> T_commod;
    Commod k;
    for(int l = 0; l < g -> nbcommod; l++){
        k = tabCommod[l];
        //On regarde la plus courte chaine qui relie les deux extremites de la commodite
        ListeEntier * LEtemp = plusCourteChaineUV(g, k.e1, k.e2);
        ListeEntier parcours = *LEtemp;
        //Nous ajoutons les aretes dans la matrice matArete
        while(parcours -> suiv != NULL){
            matArete[parcours -> u][parcours -> suiv -> u]++;
            parcours = parcours -> suiv;
        }
        desalloue(LEtemp);
        free(LEtemp);
    }

    //Nous comptons pour chaque couple de sommets, le nombre de chaines qui passent par l'arete qui les relie
    int aretes = 0;
    for (int m = 0; m < (g -> nbsom) + 1; m++){
        for(int n = m; n < (g -> nbsom) + 1; n++){
            aretes = matArete[m][n] + matArete[n][m];
            /* test */
            /* printf("[%d][%d] : nb aretes = %d\n", m, n, aretes); */
            //Si le nombre est superieur a gamma, on retoune Faux
            if(aretes > g -> gamma){
                freeMAT(matArete, (g -> nbsom) + 1);
                libererGraphe(g);
                return 0;
            }
        }
    }

    freeMAT(matArete, (g -> nbsom) + 1);
    libererGraphe(g);
    //On retourne vrai si gamma est bien respectee.
    return 1;
}


void afficherGraphe(Graphe * G) {
    printf("Nombre de sommets : %d\n", G -> nbsom);
    printf("Gamma : %d\n", G -> gamma);
    printf("Nb commodites : %d\n", G -> nbcommod);

    Sommet * s = NULL;
    Cellule_arete * ca = NULL;

    for (int i = 1 ; i < G -> nbsom + 1 ; i++) {
        s = G -> T_som[i];
        printf("sommet : [num : %d] [x : %f] [y : %f] \n", s -> num, s -> x, s -> y);

        ca = s -> L_voisin;
        while (ca) {
            printf("arete : %d, %d\n", ca -> a -> u, ca -> a -> v);
            ca = ca -> suiv;
        }
    }

    printf("\n");

    for (int j = 0 ; j < G -> nbcommod ; j++) {
        printf("Commod : %d, %d\n", (G -> T_commod)[j].e1, (G -> T_commod)[j].e2);
    }
}


void freeMAT(int ** matrice, int taille){
    for(int i = 0; i < taille; i++){
        free(matrice[i]);
    }
    free(matrice);
}


void libererGraphe(Graphe * g) {
    Sommet * s = NULL;
    Cellule_arete * caCour = NULL;
    Cellule_arete * caPrec = NULL;

    /* On libere les sommets et les aretes */
    for (int i = 1 ; i < g -> nbsom + 1 ; i++) {
        s = g -> T_som[i];
        caCour = s -> L_voisin;

        while (caCour) {
            /* Si on rencontre la premiere fois cette arete, on la libere */
            if (s -> num == (caCour -> a -> u)) {
                free(caCour -> a);
            }
            caPrec = caCour;
            caCour = caCour -> suiv;
            free(caPrec);
        }

        free(s);
    }
    free(g -> T_som);

    /* On libere les commodites */
    free(g -> T_commod);

    free(g);
}
