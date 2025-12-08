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
void deplacement_balle(int grille[50][30], int statut_balle[1]){
    int jballe;
    int iballe;
    for (int i =  0; i<50;i++){
        for(int j = 0; j<30;j++){
            if (grille[i][j] == 2){
                jballe=j;
                iballe=i;
            }
        }
    }
    switch (statut_balle[0]){ // 0 = haut gauche; 1 = haut droite; 2 = bas gauche; 3 = bas droite
    case 0:
        if(jballe==0 && iballe!=0){
            statut_balle[0]=1;
            break;
        }
        if(jballe==0 && iballe==0){
            statut_balle[0]=3;
            break;
        }
        if(iballe==0){
            statut_balle[0]=2;
            break;
        }
        if(grille[iballe-1][jballe-1]==0){
            grille[iballe][jballe]=0;
            grille[iballe-1][jballe-1]=2;
        }
        if(grille[iballe-1][jballe-1]==1){
            grille[iballe-1][jballe-1]=0;
            statut_balle[0]=2;
        }
        break;
    case 1:
        if(jballe==29 && iballe!=0){
            statut_balle[0]=0;
            break;
        }
        if(jballe==29 && iballe==0){
            statut_balle[0]=2;
            break;
        }
        if(iballe==0){
            statut_balle[0]=3;
            break;
        }
        if(grille[iballe-1][jballe+1]==0){
            grille[iballe][jballe]=0;
            grille[iballe-1][jballe+1]=2;
        }
        if(grille[iballe-1][jballe+1]==1){
            grille[iballe-1][jballe+1]=0;
            statut_balle[0]=3;
        }
        break;
    case 2:
        if(jballe==0){
            statut_balle[0]=3;
            break;
        }
        if(grille[iballe+1][jballe-1]==0){
            grille[iballe][jballe]=0;
            grille[iballe+1][jballe-1]=2;
        }else if(grille[iballe+1][jballe-1]==3){
            statut_balle[0] = 0;
        }else if(iballe>=49){
            printf("Perdu !\n");
        }
        break;
    case 3:
        if(jballe==29){
            statut_balle[0]=2;
            break;
        }
        if(grille[iballe+1][jballe+1]==0){
            grille[iballe][jballe]=0;
            grille[iballe+1][jballe+1]=2;
        }else if(grille[iballe+1][jballe+1]==3){
            statut_balle[0] = 1;
        }else if(iballe>=49){
            printf("Perdu !\n");
        }
        break;
    default:
        break;
    }
}

void deplacement_plateforme(int grille[50][30]){
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
    int statut_balle[1] = {1}; // 0 = haut gauche; 1 = haut droite; 2 = bas gauche; 3 = bas droite
    // 0 = vide; 1 = brique; 2 = balle; 3 = plateforme
    while(1){
        clearScreen();
        afficherGrille(grille);
        Sleep(100); // 800 par defaut
        deplacement_plateforme(grille);
        deplacement_balle(grille, statut_balle);
    }
    return 0;
}
