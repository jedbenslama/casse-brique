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

int main(){
    int grille[50][30];
    // 0 = vide; 1 = brique; 2 = balle; 3 = plateforme
    clearScreen();


    return 0;
}
