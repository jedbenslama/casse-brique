#include <stdio.h>

void afficherGrille(int grille[500][500], int vsize, int hsize){
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < vsize; i++){
        printf("|");
        for (int j = 0; j < hsize; j++){
            switch (grille[i][j]){
            case 0:
                printf("⬜️");
                break;
            case 1:
                printf("🟫");
                break;
            case 2:
                printf("🉐");
                break;
            case 3:
                printf("⬛️");
                break;
            default:
                printf("Erreur 1\n");
                break;
            }
        }
        printf("|");
        printf("\n");
    }
    printf("--------------------------------------------------------------\n");
}

void initGrille(int grille[500][500], int vsize, int hsize){
    for (int i = 0; i < vsize; i++){
        for (int j = 0; j < hsize; j++){
            grille[i][j]=0; // on met le vide partout
        }
    }
    for (int i = 0; i < 6; i++){
        if(i%2){ // si impair
            for (int j = 0; j < hsize; j++){
                grille[i][j]=1;
            }
        }
    }
    grille[vsize - 1][hsize/2 - 1] = 3;
    grille[vsize - 1][hsize/2] = 3;
    grille[vsize - 1][hsize/2 + 1] = 3;
    grille[vsize - 2][hsize/2] = 2;
    
}