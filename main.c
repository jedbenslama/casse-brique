#include "grille.h"
#include <time.h>
#include <string.h>
#include "deplacements.h"

void saveScore(int donnees_joueur[10]){
    clearScreen();
    char username[100]; 
    printf("Bien joué, ton score final était de %d !\nSaisis ton nom pour enregistrer ton score.\n> ", donnees_joueur[0]);
    fgets(username, 20, stdin);
    username[strcspn(username, "\n")] = 0; // référence sur https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
    printf("Le nom %s a été enregistré avec un score de %d", username, donnees_joueur[0]);
    FILE * fichier = fopen("scores.txt", "a+");
    fprintf(fichier, "%s %d\n", username, donnees_joueur[0]);
    fclose(fichier);
}

int main(){
    
    initConsole();

    int grille[50][30];
    initGrille(grille);
    int statut_balle[1] = {1}; // 0 = haut gauche; 1 = haut droite; 2 = bas gauche; 3 = bas droite
    // 0 = vide; 1 = brique; 2 = balle; 3 = plateforme
    int donnees_joueur[10];
    donnees_joueur[0] = 0;
    donnees_joueur[1] = 1;
    int temps_debut = time(NULL);
    while(1){
        if(time(NULL) > temps_debut + 15*donnees_joueur[1]){ // la difficulté augmente toutes les 15*difficulté secondes
            donnees_joueur[1] += 1;
            temps_debut = time(NULL);
        }
        clearScreen();
        afficherGrille(grille);
        printf("Score: %d\nNiveau actuel: %d\n", donnees_joueur[0], donnees_joueur[1]);
        Sleep(100 / donnees_joueur[1]); // la vitesse augmente selon le niveau de difficulté
        if(deplacement_plateforme(grille) == 1){
            saveScore(donnees_joueur);
            break;
        }
        if(deplacement_balle(grille, statut_balle, donnees_joueur) == 1){
            // on reclear et re affiche la grille pour eviter la pollution visuelle
            clearScreen();
            afficherGrille(grille);
            printf("Score: %d\nNiveau actuel: %d\nPerdu !\n", donnees_joueur[0], donnees_joueur[1]);
            break;
        };
    }
    return 0;
}
