#include <stdio.h>
#include <stdlib.h>

#include "Struct_Liste.h"
#include "Struct_File.h"
#include "SVGwriter.h"
#include "Graphe.h"
#include "Chaine.h"
#include "Reseau.h"

int main(int argc, char * argv[]){
    if (argc != 2) {
        printf("Nombre de parametres incorrect\n");
        printf("./ReorganiseReseau [nom de l'instance]\n");
        return 1;
    }

    /* Test l'instance du parametre */
    Reseau * r = NULL;
    FILE * fIn = fopen(argv[1], "r");

    Chaines * c = lectureChaines(fIn);
    printf("lectureChaines Reussi\n");

    r = reconstitueReseauListe(c);
    printf("reconstitueReseauListe Reussi\n");

    /* Test creerGraphe() */
    Graphe * g = creerGraphe(r);
    afficherGraphe(g);
    printf("creerGraphe Reussi\n");

    /* Test plusPetitNbAretes() */
    int i = plusPetitNbAretes(g, 2, 10);
    printf("plusPetitNbAretes (entre 2 et 10) : %d\n",i);

    /* Test reorganiseReseau() */
    int a = reorganiseReseau(r);
    printf("reorganiserReseau Reussi\n");
    if (a) {
        printf("Pour toute arête du graphe, le nombre de chaı̂nes qui passe par cette arête est inférieur à gamma\n\n");
    } else {
        printf("Il existe au moin une arete du graphe, telle que le nombre de chaı̂nes qui passe par cette arête est superieur à gamma\n\n");
    }
    
    libereReseauListe(r);
    libererChaines(c);
    libererGraphe(g);
    
    fclose(fIn);
    
    /* Test les trois instances qui sont crees par nous meme */
    FILE * f1 = fopen("reorganise_instance_1.txt", "r");
    FILE * f2 = fopen("reorganise_instance_2.txt", "r");
    FILE * f3 = fopen("reorganise_instance_3.txt", "r");
    
    printf("instance 1 : \n");
    Chaines * c1 = lectureChaines(f1);
    printf("\n");
    printf("instance 2 : \n");
    Chaines * c2 = lectureChaines(f2);
    printf("\n");
    printf("instance 3 : \n");
    Chaines * c3 = lectureChaines(f3);
    printf("\n");
    
    Reseau * r1 = reconstitueReseauListe(c1);
    Reseau * r2 = reconstitueReseauListe(c2);
    Reseau * r3 = reconstitueReseauListe(c3);
    
    printf("Résultat retourné par la fonction reorganiseReseau() : \n");
    printf("pour l'instance 1 : %d\n", reorganiseReseau(r1));
    printf("pour l'instance 2 : %d\n", reorganiseReseau(r2));
    printf("pour l'instance 3 : %d\n", reorganiseReseau(r3));
    
    libereReseauListe(r1);
    libereReseauListe(r2);
    libereReseauListe(r3);
    libererChaines(c1);
    libererChaines(c2);
    libererChaines(c3);
    
    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}
