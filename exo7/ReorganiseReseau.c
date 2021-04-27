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
        return 1;
    }

    /* Instance du parametre */
    Reseau * r = NULL;
    FILE * fIn = fopen(argv[1], "r");

    Chaines * c = lectureChaines(fIn);
    printf("lectureChaines Reussi\n");

    r = reconstitueReseauListe(c);
    printf("reconstitueReseauListe Reussi\n");

    Graphe * g = creerGraphe(r);
    afficherGraphe(g);
    printf("creerGraphe Reussi\n");

    int i = plusPetitNbAretes(g, 2, 10);
    printf("plusPetitNbAretes : %d\n",i);

    int a = reorganiseReseau(r);
    printf("reorganiserReseau Reussi\n");
    printf("reorganiseReseau : %d\n",a);
    
    libereReseauListe(r);
    libererChaines(c);
    libererGraphe(g);
    
    fclose(fIn);
    
    /* Les trois instances qui sont crees par nous meme */
    FILE * f1 = fopen("reorganise_instance_1.txt", "r");
    FILE * f2 = fopen("reorganise_instance_2.txt", "r");
    FILE * f3 = fopen("reorganise_instance_3.txt", "r");
    
    Chaines * c1 = lectureChaines(f1);
    Chaines * c2 = lectureChaines(f2);
    Chaines * c3 = lectureChaines(f3);
    
    Reseau * r1 = reconstitueReseauListe(c1);
    Reseau * r2 = reconstitueReseauListe(c2);
    Reseau * r3 = reconstitueReseauListe(c3);
    
    printf("resultat 1 : %d\n", reorganiseReseau(r1));
    printf("resultat 2 : %d\n", reorganiseReseau(r2));
    printf("resultat 3 : %d\n", reorganiseReseau(r3));
    
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
