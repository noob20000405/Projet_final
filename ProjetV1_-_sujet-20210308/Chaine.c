#include "Chaine.h"
#include <stdio.h>

//Q1.1
double x,y;
struct cellPoint *suiv;

CellPoint * creer_cell_point(double x, double y)
{
  Chaine * cp = (CellPoint*)malloc(sizeof(CellPoint));
  if(!cp){ //si l'allocation a echouee
    return NULL;
  }
  cp -> x = x;
  cp -> y = y;
  cp -> suiv = NULL;
  
  return cp;
}

CellPoint * inserer_en_tete_cell_point(CellPoint* cp, CellPoint* aInserer)
{
  if(cp){
    aInserer -> suiv = cp;
  }
  cp = aInserer;
  return cp;
}

CellChaine * creer_cell_chaine(int n, CellPoint cp)
{
  Chaine * cc = (CellChaine*)malloc(sizeof(CellChaine));
  if(!cc){ //si l'allocation a echouee
    return NULL;
  }
  cc -> numero = n;
  cc -> points = cp;
  cc -> suiv = NULL;
  
  return cc;
}

CellChaine * inserer_en_tete_cell_chaine(CellChaine* cc, CellChaine* aInserer)
{
  if(cc)
  {
    aInserer -> suiv = cc;
  }
  cc = aInserer;
  return cc;
}


Chaine * creer_chaine(int g, int nbC)
{
  Chaine * c = (Chaine*)malloc(sizeof(Chaine));
  if(!c) //si l'allocation a echouee
  {
    return NULL;
  }
  c -> gamma = g;
  c -> nbChaines = nbC;
  c -> chaines = NULL;
  return c;
}

Chaine * inserer_en_tete_chaine(Chaine* c, CellChaine* cc)
{
  if(c){
    cc -> suiv = c -> chaine;
  }
  c -> chaine = cc;
  return c;
}


Chaines* lectureChaines(FILE *f)
{
  if (fichier)
  {
    return NULL;
  }
  
  char buf[256];
  int x, y; //lecture CellPoint
  int n; //lecture CellChaine
  int gamma, nbChaines; //lecture Chaine
  

  if (fgets(buf, 256, f) == NULL) 
  {
      //liberer chaine;
      return NULL;
  }
  buf[strlen(buf) - 1] = '\0';
  sscanf(buf, "NbChain: %d", &n);
  
  if (fgets(buf, 256, f) == NULL) 
  {
      //liberer chaine;
      return NULL;
  }
  buf[strlen(buf) - 1] = '\0';
  sscanf(buf, "Gamma: %d", &gamma);
  Chaines* c = creer_chaine(n,gamma);
  
  while (fgets(buf, 256, f) != NULL){
    buf[strlen(buf) - 1] = '\0';
    sscanf(buf,")
  }
  

  
}

void ecrireChaines(Chaines *C, FILE *f)
void afficheChainesSVG(Chaines *C, char* nomInstance)
double longueurTotale(Chaines *C)
int comptePointsTotal(Chaines *C)
