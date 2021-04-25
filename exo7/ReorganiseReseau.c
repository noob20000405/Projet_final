#include <stdio.h>
#include <stdlib.h>

#include "Struct_Liste.h"
#include "Struct_File.h"
#include "SVGwriter.h"
#include "Graphe.h"
#include "Chaine.h"
#include "Reseau.h"

int main(void){
    Reseau * r1 = NULL;
   
    
    //Reseau * r2 = NULL;
    //Reseau * r3 = NULL;

    /* Charger les trois instances */
    FILE * fIn1 = fopen("00014_burma.cha", "r");
    
 
    //FILE * fIn2 = fopen("05000_USA-road-d-NY.cha", "r");
    //FILE * fIn3 = fopen("07397_pla.cha", "r");

    Chaines * c1 = lectureChaines(fIn1);
    printf("lectureChaines Reussi\n");

    //Chaines * c2 = lectureChaines(fIn2);
    //Chaines * c3 = lectureChaines(fIn3);

    r1 = reconstitueReseauListe(c1);
    printf("reconstitueReseauListe Reussi\n");
    //r2 = reconstitueReseauListe(c2);
    //r3 = reconstitueReseauListe(c3);

    Graphe * g = creerGraphe(r1);
    printf("creerGraphe Reussi\n");

    int i = plusPetitNbAretes(g, 2, 10);
    printf("%d",i);
    
    int a = reorganiseReseau(r1);
    printf("reorganiserReseau Reussi\n");

    //int b = reorganiseReseau(r2);
    //int c = reorganiseReseau(r3);
    //printf("a = %d, b = %d, c = %d\n", a, b, c);
    
    printf("a = %d\n",a);
    libereReseauListe(r1);
    //libereReseauListe(r2);
    //libereReseauListe(r3);
    
    return 0;

}
