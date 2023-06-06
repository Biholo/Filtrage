/**
 * @file ABR.h
 * @author  Katia SIFESSALAM & Kilian TROUET
 * @brief ?  
 * @date 2023-03-06
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef __ABR__
#define __ABR__
#define MAX 512

typedef struct noeud {
char * mot;
struct noeud *fg, *fd;
} Noeud, *Arbre;


/**
 * @brief Permet d'allouer la mémoire nécessaire pour un noeud de l'arbre.
 * 
 * @param mot (char*)
 * @return Noeud*
 */
Noeud * alloue_noeud(char *mot);


/**
 * @brief Permet de faire un parcours infixe de l'arbre de recherche donné en paramètre
 * et affiche les mots un par ligne, sur la sortie standard.
 * 
 * @param A (Arbre)
 */
void parcours_infixe(Arbre A);


/**
 * @brief Permet d'ajouter dans l'abre binaire de recherche le mot donné en paramètre.
 * 
 * @param A (Arbre*)
 * @param mot (char*)
 * @return Noeud*
 */
Noeud* ajout(Arbre *A, char *mot);


/**
 * @brief Permet de retourner le mot juste avant le mot le plus grand.
 * 
 * @param a (Arbre*)
 * @return Noeud**
 */
Noeud** max_arbre(Arbre *a);

/**
 * @brief Permet de supprimer de l'arbre donné en paramètre le plus grand mot et
 * le retourne.
 * 
 * @param A (Arbre*)
 * @return Noeud*
 */
Noeud* extrait_max(Arbre *A);

/**
 * @brief Permet d'écrire les 3 premières lignes du fichier .dot qui représente notre 
 * arbre.
 * 
 * @param f (FILE*)
 */
void ecrireDebut(FILE *f);

/**
 * @brief Permet d'écrire la dernière ligne du fichier .dot qui représente notre 
 * arbre.
 * 
 * @param f (FILE*)
 */
void ecritureFin(FILE *f);


/**
 * @brief Permet d'écrire le contenu de l'arbre donné en paramètre dans le 
 * fichier .dot donné en paramètre qui représente notre arbre
 * 
 * @param f (FILE*)
 * @param a (Arbre)
 */
void ecrireArbre(FILE *f, Arbre a);


/**
 * @brief Réuni les fonctions d'écriture afin de former le fichier .dot
 * représentant l'arbre donné en paramètre.
 * 
 * @param f (FILE*)
 * @param A(Arbre)
 */
void ecrireDot(FILE *f, Arbre A);

/**
 * @brief Permet de créer un fichier pdf représentant l'arbre donné en paramètre.
 *
 * @param nom (char*)
 * @param A (Arbre)
 */
void dessine(char * nom, Arbre A);


/**
 * @brief Permet de libérer tous les noeuds contenus dans l'abre en paramètre.
 * 
 * @param A (Arbre*)
 */
void libere(Arbre * A);


Noeud * suppression(Arbre * A, char * mot);

#endif