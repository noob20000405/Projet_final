#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"

int main(void) {
  FILE * fIn = fopen("00014_burma.cha", "r");
  FILE * fOut = fopen("test", "w");
  Chaines * c = lectureChaines(fIn);
  ecrireChaines(c, fOut);
  
  printf("Compte points total d'occurences : %d\n", comptePointsTotal(c));
  printf("Longeuer total : %f\n", longueurTotale(c));
  
  afficheChainesSVG(c, "test");
  
  fclose(fIn);
  fclose(fOut);
  
  libererChaines(c);
  
  return 0;
}
