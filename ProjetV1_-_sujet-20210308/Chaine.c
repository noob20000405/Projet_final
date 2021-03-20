#include "Chaine.h"
#include <stdio.h>

//Q1.1
Chaines* lectureChaines(FILE *f)
{  
  char buf[256];
  int x, y; //lecture CellPoint
  int nbPoints; // nombre de points dans une Cellchaine
  int num; //lecture CellChaine
  int gamma, nbChaines; //lecture Chaine
  
  //Création ensemble de chaînes 
  Chaines *C = (Chaines *) malloc(sizeof(Chaines));
  
  fgets(buf, 256, f);
  buf[strlen(buf) - 1] = '\0';
  sscanf(buf, "NbChain: %d", &nbChaines);
  
  fgets(buf, 256, f);
  buf[strlen(buf) - 1] = '\0';
  sscanf(buf, "Gamma: %d", &gamma);
 
  C -> nbChaines = nbChaines;
  C -> gamma = gamma;
  C -> chaines = NULL;
 
  //lecture de chaînes
  for(int i = 0; i < C -> nbChaines; i++){
    char points[256];
    
    //Création liste de chaînes
    CellChaine* cc = (CellChaine*)malloc(sizeof(CellChaine));
    
    fgets(buf, 256, f);
    buf[strlen(buf) - 1] = '\0';
    sscanf(f, "%d %d %[^\n]\n", &num, &nbPoints, points);
    
    cc -> numero = num;
    cc -> points = NULL;
    
    //lecture de points
    for(int j = 1; j < nbPoints){
      sscanf(points, "%2f %2f %[^\n]\n", &x, &y, points);
       
      //Création de points
      CellPoint* cp = (CellPoint*)malloc(sizeof(CellPoint));
      cp -> x = x;
      cp -> y = y;
      
      //Insertion dans la liste de points
      cp -> suivant = cc -> points;
      cc -> points = cp;
    }
    
    //Insertion dans la liste des chaines
    cp -> suiv = C -> chaines;
    C -> chaines = cp;
  }

    return C;
}

void ecrireChaines(Chaines *C, FILE *f)
void afficheChainesSVG(Chaines *C, char* nomInstance)
double longueurTotale(Chaines *C)
int comptePointsTotal(Chaines *C)
