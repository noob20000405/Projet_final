#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "Reseau.h"
#include "ArbreQuat.h"
#include "Hachage.h"
#include "SVGwriter.h"

/* Q 2.3 */
int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("Nombre de parametres incorrect\n");
        printf("./ReconstitueReseau [nom de l'instance] [type de structure]\n");
        printf("1 : liste ; 2 : table hachage ; 3 : arbre\n");
        return 1;
    }

    FILE * fIn = fopen(argv[1], "r");
    FILE * fOut = NULL;
    Chaines * c = lectureChaines(fIn);
    int methode = atoi(argv[2]);
    Reseau * r = NULL;

    /* 1 pour tester la liste chainee, 2 pour la table hachage et 3 pour l'arbre quaternaire*/
    switch (methode) {
        case 1:
            fOut = fopen("reseauListe.txt", "w");
            r = reconstitueReseauListe(c);
            afficheReseauSVG(r, "reseauListe");
            ecrireReseau(r, fOut);
            libereReseauListe(r);
            break;
        case 2:
            fOut = fopen("reseauHachage.txt", "w");
            r = reconstitueReseauHachage(c, comptePointsTotal(c));
            afficheReseauSVG(r, "reseauHachage");
            ecrireReseau(r, fOut);
            libereReseauListe(r);
            break;
        case 3:
            fOut = fopen("reseauArbre.txt", "w");
            r = reconstitueReseauArbre(c);
            afficheReseauSVG(r, "reseauArbre");
            ecrireReseau(r, fOut);
            libereReseauListe(r);
            break;
    }

    libererChaines(c);
    fclose(fIn);
    fclose(fOut);

    return 0;
}
