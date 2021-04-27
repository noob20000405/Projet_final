#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"


/* Q 6.1 */
int main(void) {
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
    /* M = 15 */
    fprintf(fOut, "table hachage (taille 15)    ");
    /* Instance 1 : 00014_burma.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 15);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 2 : 05000_USA-road-d-NY.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 15);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 3 : 07397_pla.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 15);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      \n", temps_cpu);
    libereReseauListe(r);

    /* M = 150 */
    fprintf(fOut, "table hachage (taille 150)    ");
    /* Instance 1 : 00014_burma.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 150);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 2 : 05000_USA-road-d-NY.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 150);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 3 : 07397_pla.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 150);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      \n", temps_cpu);
    libereReseauListe(r);

    /* M = 1500 */
    fprintf(fOut, "table hachage (taille 1500)    ");
    /* Instance 1 : 00014_burma.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 1500);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 2 : 05000_USA-road-d-NY.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 1500);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 3 : 07397_pla.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 1500);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      \n", temps_cpu);
    libereReseauListe(r);
    
    /* M = 3000 */
    fprintf(fOut, "table hachage (taille 3000)    ");
    /* Instance 1 : 00014_burma.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 3000);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 2 : 05000_USA-road-d-NY.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 3000);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 3 : 07397_pla.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 3000);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      \n", temps_cpu);
    libereReseauListe(r);

    /* M = 4500 */
    fprintf(fOut, "table hachage (taille 4500)    ");
    /* Instance 1 : 00014_burma.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 4500);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 2 : 05000_USA-road-d-NY.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 4500);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 3 : 07397_pla.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 4500);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      \n", temps_cpu);
    libereReseauListe(r);

    /* M = 6000 */
    fprintf(fOut, "table hachage (taille 6000)    ");
    /* Instance 1 : 00014_burma.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 6000);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 2 : 05000_USA-road-d-NY.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 6000);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 3 : 07397_pla.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 6000);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      \n", temps_cpu);
    libereReseauListe(r);

    /* M = 15000 */
    fprintf(fOut, "table hachage (taille 15000)    ");
    /* Instance 1 : 00014_burma.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c1, 15000);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 2 : 05000_USA-road-d-NY.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c2, 15000);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 3 : 07397_pla.cha */
    temps_initial = clock();
    r = reconstitueReseauHachage(c3, 15000);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      \n", temps_cpu);
    libereReseauListe(r);

    
    /* Arbre */
    fprintf(fOut, "arbre    ");
    
    /* Instance 1 : 00014_burma.cha */
    temps_initial = clock();
    r = reconstitueReseauArbre(c1);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 2 : 05000_USA-road-d-NY.cha */
    temps_initial = clock();
    r = reconstitueReseauArbre(c2);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      ", temps_cpu);
    libereReseauListe(r);
    
    /* Instance 3 : 07397_pla.cha */
    temps_initial = clock();
    r = reconstitueReseauArbre(c3);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
    fprintf(fOut, "%f      \n", temps_cpu);
    libereReseauListe(r);
    
    libererChaines(c1);
    libererChaines(c2);
    libererChaines(c3);
    
    fclose(fOut);
    fclose(fIn1);
    fclose(fIn2);
    fclose(fIn3);
    
    return 0;
}
