#include <stdio.h>
#include <time.h>
#include "conioremade.c"

char lireCommandeNonBloquante(int nombreinput[3]) {
    int kb_is_hit=0;
    char to_be_returned;
    char last_input;
    while(_kbhit()){
        kb_is_hit=1;
        if(nombreinput[0]==0){
            nombreinput[0]=1;
        }
        to_be_returned = (char)_getch();
        if(to_be_returned == last_input){
            nombreinput[0]+=1;
        }
        last_input = to_be_returned;
    }
    if(kb_is_hit){
        return to_be_returned;
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

    grille[5][0] = 0; // pour test
    
}
int deplacement_balle(int grille[50][30], int statut_balle[1]){
    int jballe = -1;
    int iballe;
    int status = 0;
    for (int i =  0; i<50;i++){
        for(int j = 0; j<30;j++){
            if (grille[i][j] == 2){
                jballe=j;
                iballe=i;
            }
        }
    }
    if(jballe==-1){
        return 1;
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
        }else if(grille[iballe+1][jballe-1]==1){
            grille[iballe+1][jballe-1]=0;
            statut_balle[0] = 0;
            if(jballe>=1){
                grille[iballe][jballe]=0;
                grille[iballe][jballe-1]=2;
            }
        }else if(iballe>=49){
            grille[iballe][jballe]=0;
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
        }else if(grille[iballe+1][jballe+1]==1){
            grille[iballe+1][jballe+1]=0;
            statut_balle[0] = 1;
            if(jballe<=28){
                grille[iballe][jballe]=0;
                grille[iballe][jballe+1]=2;
            }
        }else if(iballe>=49){
            grille[iballe][jballe]=0;
        }
        break;
    default:
        break;
    }
    return status;
}

int deplacement_plateforme(int grille[50][30]){
    int horizontale;
    for (int i =  0; i<50;i++){
        for(int j = 0; j<30;j++){
            if (grille[i][j] == 3){
                horizontale=j;
                break;
            }
        }
    }
    int nombreinput[2] = {0};
    char input = lireCommandeNonBloquante(nombreinput);
    if (input=='q' || input=='a'){
        for (int i = 0; i < nombreinput[0]; i++){
            if (horizontale>=1){
                grille[49][horizontale+2]=0;
                grille[49][horizontale-1]=3;
                horizontale-=1;
            }
        }
    }else if (input=='d'){
        for (int i = 0; i < nombreinput[0]; i++){
            if (horizontale<=26){
                grille[49][horizontale+3]=3;
                grille[49][horizontale]=0;
                horizontale+=1;
            }
        }
    }else if (input=='s'){
        return 1;
    }
    return 0;
}
int main(){
    int grille[50][30];
    initGrille(grille);
    int statut_balle[1] = {1}; // 0 = haut gauche; 1 = haut droite; 2 = bas gauche; 3 = bas droite
    // 0 = vide; 1 = brique; 2 = balle; 3 = plateforme
    while(1){
        clearScreen();
        afficherGrille(grille);
        Sleep(500); // 800 par defaut
        if(deplacement_plateforme(grille) == 1){
            break;
        }
        if(deplacement_balle(grille, statut_balle) == 1){
            printf("Perdu !\n");
            break;
        };
    }
    return 0;
}
