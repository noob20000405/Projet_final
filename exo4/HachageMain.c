#include <stdio.h>

#include "Hachage.h"

int main(void){

    /* Test fonctionClef */

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

    /* Test fonctionHachage avec instance 00014_burma*/

    int n1 = fonctionHachage(fonctionClef(16.530000,97.380000),15);
    int n2 = fonctionHachage(fonctionClef(25.230000,97.240000),15);
    int n3 = fonctionHachage(fonctionClef(20.090000,94.550000),15);
    int n4 = fonctionHachage(fonctionClef(17.200000,96.290000),15);
    int n5 = fonctionHachage(fonctionClef(16.300000,97.380000),15);
    int n6 = fonctionHachage(fonctionClef(21.520000,95.590000),15);
    int n7 = fonctionHachage(fonctionClef(14.050000,98.120000),15);
    int n8 = fonctionHachage(fonctionClef(16.470000,94.440000),15);
    int n9 = fonctionHachage(fonctionClef(22.000000,96.050000),15);
    int n10 = fonctionHachage(fonctionClef(22.390000,93.370000),15);
    int n11 = fonctionHachage(fonctionClef(20.090000,92.540000),15);
    int n12 = fonctionHachage(fonctionClef(16.470000,96.100000),15);

    printf("M=15,\t\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d \n",n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12);

    n1 = fonctionHachage(fonctionClef(16.530000,97.380000),150);
    n2 = fonctionHachage(fonctionClef(25.230000,97.240000),150);
    n3 = fonctionHachage(fonctionClef(20.090000,94.550000),150);
    n4 = fonctionHachage(fonctionClef(17.200000,96.290000),150);
    n5 = fonctionHachage(fonctionClef(16.300000,97.380000),150);
    n6 = fonctionHachage(fonctionClef(21.520000,95.590000),150);
    n7 = fonctionHachage(fonctionClef(14.050000,98.120000),150);
    n8 = fonctionHachage(fonctionClef(16.470000,94.440000),150);
    n9 = fonctionHachage(fonctionClef(22.000000,96.050000),150);
    n10 = fonctionHachage(fonctionClef(22.390000,93.370000),150);
    n11 = fonctionHachage(fonctionClef(20.090000,92.540000),150);
    n12 = fonctionHachage(fonctionClef(16.470000,96.100000),150);

    printf("M=150,\t\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d \n",n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12);

    n1 = fonctionHachage(fonctionClef(16.530000,97.380000),1500);
    n2 = fonctionHachage(fonctionClef(25.230000,97.240000),1500);
    n3 = fonctionHachage(fonctionClef(20.090000,94.550000),1500);
    n4 = fonctionHachage(fonctionClef(17.200000,96.290000),1500);
    n5 = fonctionHachage(fonctionClef(16.300000,97.380000),1500);
    n6 = fonctionHachage(fonctionClef(21.520000,95.590000),1500);
    n7 = fonctionHachage(fonctionClef(14.050000,98.120000),1500);
    n8 = fonctionHachage(fonctionClef(16.470000,94.440000),1500);
    n9 = fonctionHachage(fonctionClef(22.000000,96.050000),1500);
    n10 = fonctionHachage(fonctionClef(22.390000,93.370000),1500);
    n11 = fonctionHachage(fonctionClef(20.090000,92.540000),1500);
    n12 = fonctionHachage(fonctionClef(16.470000,96.100000),1500);

    printf("M=1500,\t\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d \n",n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12);

    n1 = fonctionHachage(fonctionClef(16.530000,97.380000),4500);
    n2 = fonctionHachage(fonctionClef(25.230000,97.240000),4500);
    n3 = fonctionHachage(fonctionClef(20.090000,94.550000),4500);
    n4 = fonctionHachage(fonctionClef(17.200000,96.290000),4500);
    n5 = fonctionHachage(fonctionClef(16.300000,97.380000),4500);
    n6 = fonctionHachage(fonctionClef(21.520000,95.590000),4500);
    n7 = fonctionHachage(fonctionClef(14.050000,98.120000),4500);
    n8 = fonctionHachage(fonctionClef(16.470000,94.440000),4500);
    n9 = fonctionHachage(fonctionClef(22.000000,96.050000),4500);
    n10 = fonctionHachage(fonctionClef(22.390000,93.370000),4500);
    n11 = fonctionHachage(fonctionClef(20.090000,92.540000),4500);
    n12 = fonctionHachage(fonctionClef(16.470000,96.100000),4500);

    printf("M=4500,\t\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d \n",n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12);

    n1 = fonctionHachage(fonctionClef(16.530000,97.380000),15000);
    n2 = fonctionHachage(fonctionClef(25.230000,97.240000),15000);
    n3 = fonctionHachage(fonctionClef(20.090000,94.550000),15000);
    n4 = fonctionHachage(fonctionClef(17.200000,96.290000),15000);
    n5 = fonctionHachage(fonctionClef(16.300000,97.380000),15000);
    n6 = fonctionHachage(fonctionClef(21.520000,95.590000),15000);
    n7 = fonctionHachage(fonctionClef(14.050000,98.120000),15000);
    n8 = fonctionHachage(fonctionClef(16.470000,94.440000),15000);
    n9 = fonctionHachage(fonctionClef(22.000000,96.050000),15000);
    n10 = fonctionHachage(fonctionClef(22.390000,93.370000),15000);
    n11 = fonctionHachage(fonctionClef(20.090000,92.540000),15000);
    n12 = fonctionHachage(fonctionClef(16.470000,96.100000),15000);

    printf("M=15000,\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d \n",n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12);

    return 0;

}
