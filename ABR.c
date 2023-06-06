#include "ABR.h"

Noeud * alloue_noeud(char *mot) {
    Noeud *n = (Noeud*)malloc(sizeof(Noeud));
    if (n == NULL) {
       fprintf(stderr, "Erreur : impossible d'allouer de la mémoire\n");
       return NULL;
    }
    n->mot = malloc((strlen(mot) + 1) * sizeof(char));
    if (n->mot == NULL) {
       free(n);
       fprintf(stderr, "Erreur : impossible d'allouer de la mémoire\n");
       return NULL;
    }
    strcpy(n->mot, mot);
    n->fg = NULL;
    n->fd = NULL;
    return n;
}

void parcours_infixe(Arbre A){
    if(A == NULL)
        return;
    parcours_infixe(A->fg);
    printf("%s\n", A->mot);
    parcours_infixe(A->fd);
}


Noeud* ajout(Arbre *A, char *mot){
    if(*A == NULL){
        Noeud* nouv = alloue_noeud(mot);
        if(nouv == NULL) return NULL;
        *A = nouv;
        return *A;
    }else{
        if(strcmp((*A)->mot, mot) == 0) return NULL;
        else if(strcmp((*A)->mot, mot) < 0){
            ajout(&((*A)->fg), mot);
        }else if(strcmp((*A)->mot, mot) > 0) ajout(&((*A)->fd), mot);
    }
    return NULL;
}



Noeud** max_arbre(Arbre *a){
    if((*a)->fd == NULL){
        return a;
    }else if((*a)->fd->fd == NULL){
        return &((*a)->fd);
    }
    return max_arbre(&((*a)->fd));
}


Noeud* extrait_max(Arbre *A){
    Noeud** avant_max = max_arbre(A);
    if(avant_max == NULL){
        return NULL;
    }
    Noeud *max = *avant_max;
    *avant_max = max->fg ? max->fg : NULL;
    return max;
}

Noeud * suppression(Arbre * A, char * mot){
    Noeud * supp;
    if(*A == NULL){
        return *A;
    }
    if(strcmp((*A)->mot, mot) < 0){
        return suppression(&(*A)->fg, mot);
    }
    if(strcmp((*A)->mot, mot) > 0){
        return suppression(&(*A)->fd, mot);
    }
    supp = *A;
    if((*A)->fg == NULL){
        *A = (*A)->fd;
    }else if((*A)->fd == NULL){
        *A = (*A)->fg;
    }else{
        Noeud * max = extrait_max(&(*A)->fg);
        (*A)->mot = max->mot; 
    }

    return supp;
}



void ecrireDebut(FILE *f){
    char *head = "digraph arbre {\nnode [ shape = record , height = .1 ]\nedge [ tailclip = false , arrowtail = dot , dir = both ];\n";
    fwrite(head,1, strlen(head), f);
}

void ecritureFin(FILE *f){
    fprintf(f,"}\n");
}

void ecrireArbre(FILE *f, Arbre a){
    if(a == NULL) return;
    fprintf(f,"n%p [label=\"<gauche>|<valeur>%s|<droit>\"];\n", a, a->mot);


    if(a->fg != NULL) {
        fprintf(f,"n%p:gauche:c -> n%p:valeur;\n", a, a->fg);
        ecrireArbre(f, a->fg);

    }
    if(a->fd != NULL) {
        fprintf(f,"n%p:droit:c -> n%p:valeur;\n", a, a->fd);
        ecrireArbre(f, a->fd);
    }
}

void ecrireDot(FILE *f, Arbre A){
    ecrireDebut(f);
    ecrireArbre(f, A);
    ecritureFin(f);
    

}

void dessine(char * nom, Arbre A){
    FILE *f;

    size_t size_nom;
    size_nom = strlen(nom) + 1;

    char *dot = (char *) malloc(size_nom + 4);
    char *pdf = (char *) malloc(size_nom + 4);
    strcpy(dot, nom);
    strcpy(pdf, nom);
    
    strcat(dot, ".dot");
    strcat(pdf, ".pdf");


    f = fopen(dot, "w");
     if(f==NULL){
        printf("Erreur lors de l'ouverture d'un fichier");
        exit(1);
    }

    ecrireDot(f, A);
    fclose(f);

    int len = strlen(dot) + strlen(pdf) + 15;
    char cmd[len];
    strcpy(cmd, "dot -Tpdf ");
    strcat(cmd, dot);
    strcat(cmd, " -o ");
    strcat(cmd, pdf);
    system(cmd);
    printf("Le fichiers pdf de %s a bien été créé.\n", nom);

    free(dot);
    free(pdf);
}


void libere(Arbre *A){
    if (*A) {
        libere(&((*A)->fg));
        libere(&((*A)->fd));
        free((*A)->mot);
        free(*A);
        *A = NULL;
    }
}