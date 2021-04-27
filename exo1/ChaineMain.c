#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Chaine.h"

/* Q 1.2 */
int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Nombre de parametres incorrect\n");
        printf("./ChaineMain [nom de l'instance]\n");
        return 1;
    }
    
    FILE * fIn = fopen(argv[1], "r");
    FILE * fOut = fopen("ecrire_chaines.txt", "w");
    Chaines * c = lectureChaines(fIn);
    ecrireChaines(c, fOut);
    afficheChainesSVG(c, "chaineSVG");
    
    printf("longueurTotale : %lf\n", longueurTotale(c));
    printf("comptePointsTotal : %d\n", comptePointsTotal(c));
    
    libererChaines(c);
    fclose(fIn);
    fclose(fOut);
    
    return 0;
}
