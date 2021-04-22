#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"

int main(void) {
    srand((unsigned)time(NULL));
  
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;
    
    FILE * fOut = fopen("sortie_vitesse.txt", "w");
    Reseau * r = NULL;
    /* Charger les trois instances */
    FILE * fIn1 = fopen("00014_burma.cha", "r");
    FILE * fIn2 = fopen("05000_USA-road-d-NY.cha", "r");
    FILE * fIn3 = fopen("07397_pla.cha", "r");
    Chaines * c1 = lectureChaines(fIn1);
    Chaines * c2 = lectureChaines(fIn2);
    Chaines * c3 = lectureChaines(fIn3);
    
    fprintf(fOut, "type_structure    instance_1      instance_2      instance_3\n");
    
    /* Liste */
    fprintf(fOut, "liste    ");
    
    /* Instance 1 : 00014_burma.cha */
    temps_initial = clock();
    r = reconstitueReseauListe(c1);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 2 : 05000_USA-road-d-NY.cha */
    temps_initial = clock();
    r = reconstitueReseauListe(c2);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 3 : 07397_pla.cha */
    temps_initial = clock();
    r = reconstitueReseauListe(c3);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      \n", temps_cpu);
    libereReseauListe(r);
    
    /* Table hachage */
    
    /* Arbre */
    
    libererChaines(c1);
    libererChaines(c2);
    libererChaines(c3);
    
    fclose(fOut);
    fclose(fIn1);
    fclose(fIn2);
    fclose(fIn3);
    
    return 0;
}
