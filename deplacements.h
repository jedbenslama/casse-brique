#include "conioremade.h"

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
        last_input = to_be_returned; // en gros c'est pour calculer le nombre d'inputs kbhit par tick pour ne pas avoir d'inputs en surplus qui risquent d'etre gardés pour la boucle d'apres
    }
    if(kb_is_hit){
        return to_be_returned;
    }
    return 0;
}

int deplacement_balle(int grille[500][500], int statut_balle[1], int donnees_joueur[10], int vsize, int hsize){
    int jballe = -1;
    int iballe;
    int status = 0;
    for (int i =  0; i<vsize;i++){
        for(int j = 0; j<hsize;j++){
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
        if(grille[iballe-1][jballe-1]==1){ // cassage brique
            donnees_joueur[0]+=10;
            grille[iballe-1][jballe-1]=0;
            statut_balle[0]=2;
        }
        break;
    case 1:
        if(jballe==hsize-1 && iballe!=0){
            statut_balle[0]=0;
            break;
        }
        if(jballe==hsize-1 && iballe==0){
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
        if(grille[iballe-1][jballe+1]==1){ // cassage brique
            donnees_joueur[0]+=10;
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
        }else if(grille[iballe+1][jballe-1]==1){ // cassage brique
            donnees_joueur[0]+=10;
            grille[iballe+1][jballe-1]=0;
            statut_balle[0] = 0;
            if(jballe>=1){
                grille[iballe][jballe]=0;
                grille[iballe][jballe-1]=2;
            }
        }else if(iballe>=vsize-1){
            grille[iballe][jballe]=0;
        }
        break;
    case 3:
        if(jballe==hsize-1){
            statut_balle[0]=2;
            break;
        }
        if(grille[iballe+1][jballe+1]==0){
            grille[iballe][jballe]=0;
            grille[iballe+1][jballe+1]=2;
        }else if(grille[iballe+1][jballe+1]==3){
            statut_balle[0] = 1;
        }else if(grille[iballe+1][jballe+1]==1){ // cassage brique
            donnees_joueur[0]+=10;
            grille[iballe+1][jballe+1]=0;
            statut_balle[0] = 1;
            if(jballe<=28){
                grille[iballe][jballe]=0;
                grille[iballe][jballe+1]=2;
            }
        }else if(iballe>=vsize-1){
            grille[iballe][jballe]=0;
        }
        break;
    default:
        break;
    }
    return status;
}

int deplacement_plateforme(int grille[500][500], int vsize, int hsize){
    int horizontale;
    for (int i =  0; i<vsize;i++){
        for(int j = 0; j<hsize;j++){
            if (grille[i][j] == 3){
                horizontale=j;
                break;
            }
        }
    }
    int nombreinput[2] = {0};
    char input = lireCommandeNonBloquante(nombreinput);
    if (input=='A' || input=='Q' || input=='q' || input=='a'){
        for (int i = 0; i < nombreinput[0]; i++){
            if (horizontale>=1){
                grille[vsize-1][horizontale+2]=0;
                grille[vsize-1][horizontale-1]=3;
                horizontale-=1;
            }
        }
    }else if (input=='d' || input=='D'){
        for (int i = 0; i < nombreinput[0]; i++){
            if (horizontale<=hsize-4){
                grille[vsize-1][horizontale+3]=3;
                grille[vsize-1][horizontale]=0;
                horizontale+=1;
            }
        }
    }else if (input=='s'){
        return 1;
    }
    return 0;
}