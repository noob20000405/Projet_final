#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Chaine.h"
#include "SVGwriter.h"

void libererCellChaine(CellChaine * cc){
  if(!cc){
    return;
  }
  
  CellPoint * cpCour = cc -> points;
  CellPoint * cpPrec;

  while(cpCour){
    cpPrec = cpCour;
    cpCour = cpCour -> suiv;
    free(cpPrec);
  }
  
  free(cc);
  return;
}

void libererChaines(Chaines* C){
  if(!C){
    return;
  }
  CellChaine * ccCour = C -> chaines;
  CellChaine * ccPrec;

  while(ccCour){
    ccPrec = ccCour;
    ccCour = ccCour -> suiv;
    libererCellChaine(ccPrec);
  }
  
  free(C);
  return;
}





//Q1.1
Chaines* lectureChaines(FILE * f)
{  
  char buf[256];
  double x, y; //lecture CellPoint
  int nbPoints; // nombre de points dans une Cellchaine
  int num; //lecture CellChaine
  int gamma, nbChaines; //lecture Chaine
  
  //Création ensemble de chaînes 
  Chaines *C = (Chaines *) malloc(sizeof(Chaines));
  if(!C){
    printf("Erreur lors de l'allocation Chaines.\n");
    return NULL;
  }
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
    if(!cc){
      printf("Erreur lors de l'allocation CellChaine.\n");
      libererChaines(C);
      return NULL;
    }
    
    fgets(buf, 256, f);
    buf[strlen(buf) - 1] = '\0';
    sscanf(buf, "%d %d %[^\n]\n", &num, &nbPoints, points);
    printf("%d %d ", num, nbPoints);/* Test */
    
    cc -> numero = num;
    cc -> points = NULL;
    
    //lecture de points
    for(int j = 0; j < nbPoints ; j++){
      sscanf(points, "%lf %lf %[^\n]\n", &x, &y, points);
      printf("%.2f %.2f ", x, y); /* Test */
       
      //Création de points
      CellPoint* cp = (CellPoint*)malloc(sizeof(CellPoint));
      if(!cp){
        printf("Erreur lors de l'allocation CellPoint.\n");
        libererCellChaine(cc);
        libererChaines(C);
        return NULL;
      }
      cp -> x = x;
      cp -> y = y;
      
      //Insertion dans la liste de points
      cp -> suiv = cc -> points;
      cc -> points = cp;
    }
    
    //Insertion dans la liste des chaines
    cc -> suiv = C -> chaines;
    C -> chaines = cc;
    
    printf("\n"); /* Test */
  }

    return C;
}

void ecrireChaines(Chaines * C, FILE * f) {
  if (!C || !f) return ;
  
  fprintf(f, "NbChaine: %d\nGamma: %d\n\n", C -> nbChaines, C -> gamma);
  
  CellChaine * cc = C -> chaines;
  CellPoint * cp = NULL;
  int nbP; // Nombre des points dans une chaine
  
  while (cc) {
    cp = cc -> points;
    nbP = 1;
    /* On compte le nombre de cellPoint */
    while (cp) {
      nbP++;
      cp = cp -> suiv;
    }
    fprintf(f, "%d %d ", cc -> numero, nbP);
    
    /* On parcourt la deuxieme fois pour ecrire les coordonnees */
    cp = cc -> points;
    while (cp) {
      fprintf(f, "%.2f %.2f ", cp -> x, cp -> y);
      cp = cp -> suiv;
    }
    fprintf(f, "\n");
    cc = cc -> suiv;
  }
}

void afficheChainesSVG(Chaines *C, char* nomInstance){
    int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}

double longueurChaine(CellChaine * c) {
  if (!c) return 0;
  CellPoint * cp_cur = c -> points;
  CellPoint * cp_suiv = cp_cur -> suiv;
  /* Longueur qu'on va retourner */
  double lg = 0;
  
  while (cp_suiv) {
    lg += sqrt(pow((cp_suiv -> x) - (cp_cur -> x), 2) + pow((cp_suiv -> y) - (cp_cur -> y), 2));
    cp_cur = cp_suiv;
    cp_suiv = cp_suiv -> suiv;
  }
  
  return lg;
}

double longueurTotale(Chaines *C) {
  if (!C) return 0;
  CellChaine * cc = C -> chaines;
  double lg = 0;
  
  while (cc) {
    lg += longueurChaine(cc);
    cc = cc -> suiv;
  }
  return lg;
}

int comptePointsTotal(Chaines *C) {
  if (!C) return 0;
  /* Nombre total d'occurences de points */
  int nb = 0;
  CellChaine * cc = C -> chaines;
  CellPoint * cp = NULL;
  CellPoint * cp_copie = NULL;
  CellPoint * cp_cmp = NULL;
  CellPoint * cp_cmp_debut = cp_cmp;
  int compte = 0; /* Ce parametre represente si un point est deja compte une fois */
  
  while (cc) {
    cp = cc -> points;
    while (cp) {
      /* Determiner si ce point est deja ajoute dans la liste cp_cmp */
      cp_cmp = cp_cmp_debut;
      while (cp_cmp) {
        /* Si oui */
        if (cp_cmp -> x == cp -> x && cp_cmp -> y == cp -> y) {
          nb++;
          compte = 1;
        }
        cp_cmp = cp_cmp -> suiv;
      }
      /* Sinon, on l'ajoute dans la liste cp_cmp */
      if (!compte) {
        compte = 0;
        cp_copie = (CellPoint *)malloc(sizeof(CellPoint));
        cp_copie -> x = cp -> x;
        cp_copie -> y = cp -> y;
        cp_copie -> suiv = cp_cmp_debut;
        cp_cmp_debut = cp_copie;
      }
      cp = cp -> suiv;
    }
    cc = cc -> suiv;
  }
  /* Liberer la liste */
  cp_cmp = cp_cmp_debut;
  CellPoint * cp_suiv;
  while (cp_cmp) {
    cp_suiv = cp_cmp -> suiv;
    free(cp_cmp);
    cp_cmp = cp_suiv;
  }
  
  return nb;
}
