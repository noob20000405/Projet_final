#include <stdio.h>
#include "Hachage.h"

int main(void){

    double clef = 0;
    for (int i = 1 ; i <= 10 ; i++){
        for (int j = 1; j <= 10; j++){
            clef = fonctionClef(i,j);
            printf(" x = %d, y = %d, clef = %.2f\n", i, j, clef);
        }
    }
    return 0;

}
