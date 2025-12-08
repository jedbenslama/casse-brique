#include <stdio.h>
#include <time.h>
#include "conioremade.c"


void afficherGrille(int grille[50][30]){
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 30; j++){
            switch (j){
            case 0:
                printf(" ");
                break;
            case 1:
                printf("#");
                break;
            case 2:
                printf("O");
                break;
            case 3:
                printf("=");
                break;
            default:
                printf("Erreur 1\n");
                exit(1);
                break;
            }
        }
        printf("\n");
    }
}

void initGrille(int grille[50][30]){
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 30; j++){
            grille[i][j]=0; // on met le vide partout
        }
    }
    for (int i = 0; i < 5; i++){
        if(i%2){ // si impair
            for (int j = 0; j < 30; j++){
                grille[i][j]=1;
            }
        }
    }
    grille[50][14] = 3;
    grille[50][15] = 3;
    grille[50][16] = 3;
    grille[49][16] = 2;
    
}

int main(){
    int grille[50][30];
    // 0 = vide; 1 = brique; 2 = balle; 3 = plateforme
    clearScreen();


    return 0;
}
