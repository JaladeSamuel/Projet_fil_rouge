/** Module des descripteurs textes.
 *  Contient une structure de descripteur et les fonctions nécessaire pour les manipuler.
 *  Aurélien Montmejat 
 */

#include <stdio.h>

#define WORD_LENGTH_MAX 25

#ifndef DESCRIPTEURTXT_H
#define DESCRIPTEURTXT_H

typedef struct tag_TERME
{
    char word[WORD_LENGTH_MAX];
    int occurence;
} TERME;

typedef struct tag_TERMES
{
    TERME* terme;
    struct tag_TERMES* termeSuivant;
} pileTERMES;

typedef pileTERMES* TERMES;

typedef struct tag_DESCR {
    int id;
    int nbTermes;
    int total;
    TERMES termes;
} DESCR;

/** Fonction qui transforme la chaine de charactères en minuscule.
 *  char* word : la chaine à transformer en minuscule
 */
void tolower_DESC_STR(char* word);

/** Initialise un descripteur.
 *  DESCR* descripteur : la structure de descripteur à initialiser
 *  int id : l'id à utiliser pour l'initialisation
 */
void init_DESCR(DESCR* descriptor, int id);

/** Remplis le descripteur donné en paramètre avec les informations de son 
 *  descripteur en utilisant le fichier donné en paramètre, utile si l'on veut 
 *  en faire plusieurs à la suite sans fermer et ouvrir le fichier.
 *  DESCR* descriptor : la structure du descripteur à remplir
 *  FILE* file : le fichier à utiliser pour le remplissage
 */
void fill_DESCR(DESCR* descriptor, FILE* file);

/** Remplis le descripteur donné en paramètre avec les informations de son 
 *  descripteur en utilisant le chemin du fichier donné en paramètre.
 *  DESCR* descriptor : la structure du descripteur à remplir
 *  FILE* file : le fichier à utiliser pour le remplissage
 */
void fillWithPath_DESCR(DESCR* descriptor, char* path);

/** Ajoute un mot au descripteur.
 *  DESCR* descriptor : descripteur dans lequel on ajoute le mot
 *  char* word : mot à ajouter au descripteur
 */
void addWord_DESCR(DESCR* descriptor, char* word);

/** Ajoute un mot et une occurence à un descripteur. 
 *  DESCR* descriptor : descriptor dans lequel on ajout le mot et son occurence
 *  char* word : mot à ajouter
 *  int occurence : occurence du mot à ajouer
 */
void addWordandOcc_DESCR(DESCR* descriptor, char* word, int occurence);

/** Retourne l'occurence d'un mot cherché dans le descripteur donné.
 *  DESCR descriptor : descripteur dans lequel on recherche le mot
 *  char* word : mot à rechercher
 */
int getOccurence_DESCR(DESCR descriptor, char* word);

/** Dépile un mot de la pile du descripteur.
 */
void removeWord_DESCR(DESCR* descriptor);

/** Retourne un terme à l'indice donné d'un descripteur donné.
 *  DESCR descriptor : descripteur dans lequel on recherche le terme à l'index donné
 *  int index : l'index du terme recherché
 */
TERME* get_DESCR(DESCR descriptor, int index);

/** Ferme un descripteur.
 *  Cette fonction le dépile et libère la place pris par celui-ci.
 */
void close_DESCR(DESCR* descriptor);

#endif
