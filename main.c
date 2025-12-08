#include <stdio.h>
#include <time.h>
#include "conioremade.c"

char lireCommandeNonBloquante() {
    if (_kbhit()) {
        return (char)_getch();
    }
    return 0;
}

void afficherGrille(int grille[50][30]){
    printf("--------------------------------\n");
    for (int i = 0; i < 50; i++){
        printf("|");
        for (int j = 0; j < 30; j++){
            switch (grille[i][j]){
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
        printf("|");
        printf("\n");
    }
    printf("--------------------------------\n");
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
    grille[49][14] = 3;
    grille[49][15] = 3;
    grille[49][16] = 3;
    grille[48][15] = 2;
    
}
void déplacement_plateforme(int grille[50][30]){
    int horizontale;
    for (int i =  0; i<50;i++){
        for(int j = 0; j<30;j++){
            if (grille[i][j] == 3){
                horizontale=j;
                break;
            }
        }
    }
    char input = lireCommandeNonBloquante();
    if (input=='q' || input=='a'){
        if (horizontale>=1){
            grille[49][horizontale+2]=0;
            grille[49][horizontale-1]=3;
        }
    }else if (input=='d'){
        if (horizontale<=26){
            grille[49][horizontale+3]=3;
            grille[49][horizontale]=0;
        }
    }
}
int main(){
    int grille[50][30];
    initGrille(grille);
    // 0 = vide; 1 = brique; 2 = balle; 3 = plateforme
    while(1){
        clearScreen();
        afficherGrille(grille);
        Sleep(100);
        déplacement_plateforme(grille);
    }
    return 0;
}
