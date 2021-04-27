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

    double cle1 = fonctionClef(19.43,111.11);
    double cle2 = fonctionClef(115.55,49.89);
    printf("%.2f %.2f\n", cle1, cle2);

    int a = fonctionHachage(fonctionClef(19.43,111.11),7);
    int b = fonctionHachage(fonctionClef(109.02,96.32),7);
    int c = fonctionHachage(fonctionClef(115.55,49.89),7);
    int d = fonctionHachage(fonctionClef(60.00,60.00),7);
    int e = fonctionHachage(fonctionClef(96.97,5.10),7);
    int f = fonctionHachage(fonctionClef(22.52,24.32),7);
    int g = fonctionHachage(fonctionClef(12.12,57.54),7);
    printf("M=7,\t%d\t%d\t%d\t%d\t%d\t%d\t%d \n",a ,b, c, d, e, f, g);

    a = fonctionHachage(fonctionClef(19.43,111.11),3);
    b = fonctionHachage(fonctionClef(109.02,96.32),3);
    c = fonctionHachage(fonctionClef(115.55,49.89),3);
    d = fonctionHachage(fonctionClef(60.00,60.00),3);
    e = fonctionHachage(fonctionClef(96.97,5.10),3);
    f = fonctionHachage(fonctionClef(22.52,24.32),3);
    g = fonctionHachage(fonctionClef(12.12,57.54),3);
    printf("M=3,\t%d\t%d\t%d\t%d\t%d\t%d\t%d \n",a ,b, c, d, e, f, g);

    a = fonctionHachage(fonctionClef(19.43,111.11),9);
    b = fonctionHachage(fonctionClef(109.02,96.32),9);
    c = fonctionHachage(fonctionClef(115.55,49.89),9);
    d = fonctionHachage(fonctionClef(60.00,60.00),9);
    e = fonctionHachage(fonctionClef(96.97,5.10),9);
    f = fonctionHachage(fonctionClef(22.52,24.32),9);
    g = fonctionHachage(fonctionClef(12.12,57.54),9);
    printf("M=9,\t%d\t%d\t%d\t%d\t%d\t%d\t%d \n",a ,b, c, d, e, f, g);

    a = fonctionHachage(fonctionClef(19.43,111.11),14);
    b = fonctionHachage(fonctionClef(109.02,96.32),14);
    c = fonctionHachage(fonctionClef(115.55,49.89),14);
    d = fonctionHachage(fonctionClef(60.00,60.00),14);
    e = fonctionHachage(fonctionClef(96.97,5.10),14);
    f = fonctionHachage(fonctionClef(22.52,24.32),14);
    g = fonctionHachage(fonctionClef(12.12,57.54),14);
    printf("M=14,\t%d\t%d\t%d\t%d\t%d\t%d\t%d \n",a ,b, c, d, e, f, g);

    a = fonctionHachage(fonctionClef(19.43,111.11),100);
    b = fonctionHachage(fonctionClef(109.02,96.32),100);
    c = fonctionHachage(fonctionClef(115.55,49.89),100);
    d = fonctionHachage(fonctionClef(60.00,60.00),100);
    e = fonctionHachage(fonctionClef(96.97,5.10),100);
    f = fonctionHachage(fonctionClef(22.52,24.32),100);
    g = fonctionHachage(fonctionClef(12.12,57.54),100);
    printf("M=100,\t%d\t%d\t%d\t%d\t%d\t%d\t%d \n",a ,b, c, d, e, f, g);

    a = fonctionHachage(fonctionClef(19.43,111.11),500);
    b = fonctionHachage(fonctionClef(109.02,96.32),500);
    c = fonctionHachage(fonctionClef(115.55,49.89),500);
    d = fonctionHachage(fonctionClef(60.00,60.00),500);
    e = fonctionHachage(fonctionClef(96.97,5.10),500);
    f = fonctionHachage(fonctionClef(22.52,24.32),500);
    g = fonctionHachage(fonctionClef(12.12,57.54),500);
    printf("M=500,\t%d\t%d\t%d\t%d\t%d\t%d\t%d \n",a ,b, c, d, e, f, g);

    return 0;

}
