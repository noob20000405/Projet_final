#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"

int main(void) {
  FILE * fIn = fopen("00014_burma.cha", "r");
  FILE * fOut = fopen("test", "w");
  Chaines * c = lectureChaines(fIn);
  ecrireChaines(c, fOut);
  
  printf("compte points tot : %d", comptePointsTotal(c));
  
  afficheChainesSVG(c, "test");
  
  fclose(fIn);
  fclose(fOut);
  
  return 0;
}
