#include <stdio.h>

void afficherGrille(int grille[50][30]){
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < 50; i++){
        printf("|");
        for (int j = 0; j < 30; j++){
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

void initGrille(int grille[50][30]){
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 30; j++){
            grille[i][j]=0; // on met le vide partout
        }
    }
    for (int i = 0; i < 6; i++){
        if(i%2){ // si impair
            for (int j = 0; j < 30; j++){
                grille[i][j]=1;
            }
        }
    }
    grille[49][14] = 3;
    grille[49][15] = 3;
    grille[49][16] = 3;
    grille[48][15] = 2;
    
}