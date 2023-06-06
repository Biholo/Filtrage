#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ABR.h"


Noeud* recherche(Arbre a, char * mot){
    if(a != NULL){
        if(strcmp(a->mot, mot) == 0) return a;
        if(strcmp(a->mot, mot) < 0){
            return recherche(a->fg, mot);
        }else{
            return recherche(a->fd, mot);
        }
   }
    return NULL;
}


int filtrage(Arbre *A, Arbre filtre, Arbre *utilises) {
    if (*A == NULL) {
        return 0;
    }
    if (filtre == NULL) {
        return 0;
    }
    
    Noeud *temp = recherche(*A, filtre->mot);
    
    if (temp != NULL) {
        ajout(utilises, temp->mot);
        suppression(A, temp->mot);   
    }
    
    filtrage(A, filtre->fg, utilises);
    filtrage(A, filtre->fd, utilises);
    return 1;
}

void lecture_file(FILE * fichier, Arbre * texte, char * separateurs, char * l1){
    char * a = fgets(l1, MAX, fichier);
    char * mot = strtok(a, separateurs);    
    while(mot != NULL){
        ajout(texte, mot);
        mot = strtok(NULL, separateurs);
    }
}

int main(int argc, char* argv[]){

    char * separateurs = " \n\r,;:.?!\"()-’";
    char l1[MAX];

    Arbre texte = NULL;
    Arbre only_texte = NULL;
    Arbre utilises = NULL;
    Arbre filtre = NULL;

    if(argc < 2) {
        printf("Error! Veuillez exécuter la compilation avec deux fichiers textes.\n");
    }

    FILE * fichier = fopen(argv[1], "r");
    FILE * fichier2 = fopen(argv[2], "r");

    if (fichier == NULL || fichier2 == NULL){  
        printf("Error! Could not open file\n");
        exit(-1);
    }

    char * a = fgets(l1, MAX, fichier);
    char * mot;

    while (a != NULL) {
        mot = strtok(a, separateurs);
        while(mot != NULL){
            ajout(&texte, mot);
            ajout(&only_texte, mot);
            mot = strtok(NULL, separateurs);
        }
        a = fgets(l1, MAX, fichier);
    }


    char * c = fgets(l1, MAX, fichier2);
    while (c != NULL) {
        mot = strtok(c, separateurs);
        while(mot != NULL){
            ajout(&filtre, mot);
            mot = strtok(NULL, separateurs);
        }
        c = fgets(l1, MAX, fichier2);
    }

    fclose(fichier);
    fclose(fichier2);

    filtrage(&only_texte, filtre, &utilises);

    printf("\nMots présents uniquement dans le texte de référence :\n");
    printf("-----------------------------------------------------\n");
    parcours_infixe(texte);

    printf("\nMots présents dans les deux textes :\n");
    printf("------------------------------------\n");
    parcours_infixe(utilises);

    if(argc == 4){
        if(!strcmp(argv[3], "-v")) {
            dessine("texte", texte);
            dessine("filtre", filtre);
            dessine("filtrage", only_texte);
            dessine("en_commun", utilises);
        }
    }
    
    libere(&texte);
    libere(&filtre);
    libere(&only_texte);
    libere(&utilises);

    return 0;
}