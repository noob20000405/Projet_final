#ifndef __CHAINE_H__
#define __CHAINE_H__	

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

void libererCellChaine(CellChaine* cc);
void libererChaines(Chaines* C);

/* Q 1.1 */
Chaines* lectureChaines(FILE *f);
/* Q 1.2 */
void ecrireChaines(Chaines *C, FILE *f);
/* Q 1.3 */
void afficheChainesSVG(Chaines *C, char* nomInstance);
/* Q 1.4 */
double longueurTotale(Chaines *C);
/* Q 1.5 */
int comptePointsTotal(Chaines *C);

/* Q 6.2 */
Chaines* generationAleatoire(int nbChaines,int nbPointsChaine,int xmax, int ymax);

#endif	
