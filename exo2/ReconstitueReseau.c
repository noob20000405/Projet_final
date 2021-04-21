#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"
#include "Reseau.h"
#include "ArbreQuat.h"
#include "Hachage.h"
#include "SVGwriter.h"

int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("Nombre de parametres incorrect\n");
        return 1;
    }

    FILE * fIn = fopen(argv[1], "r");
    FILE * fOut = NULL;
    Chaines * c = lectureChaines(fIn);
    int methode = atoi(argv[2]);
    Reseau * r = NULL;
    
    switch (methode) {
        case 1:
            fOut = fopen("reseauListe.txt", "w");
            r = reconstitueReseauListe(c);
            //afficheReseauSVG(r, "reseauListe");这两个里面有1个block lost
            //ecrireReseau(r, fOut);
            libereReseauListe(r);
            break;
        case 2:
            fOut = fopen("reseauHachage.txt", "w");
            r = reconstitueReseauHachage(c, comptePointsTotal(c));
            afficheReseauSVG(r, "reseauHachage");
            ecrireReseau(r, fOut);
            break;
        case 3:
            fOut = fopen("reseauArbre.txt", "w");
            r = reconstitueReseauArbre(c);
            afficheReseauSVG(r, "reseauArbre");
            ecrireReseau(r, fOut);
            break;
    }
    
    libererChaines(c);
    fclose(fIn);
    fclose(fOut);

    return 0;
}
