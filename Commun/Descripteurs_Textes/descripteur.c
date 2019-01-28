/** Module des descripteurs textes.
 *  Contient une structure de descripteur et les fonctions nécessaire pour les manipuler.
 *  Aurélien Montmejat 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "descripteur.h"

/** Fonction qui transforme la chaine de charactères en minuscule.
 *  char* word : la chaine à transformer en minuscule
 */
void tolower_DESC_STR(char* word)
{
    for (int i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
}

/** Initialise un descripteur.
 *  DESCR* descripteur : la structure de descripteur à initialiser
 *  int id : l'id à utiliser pour l'initialisation
 */
void init_DESCR(DESCR* descriptor, int id)
{
    descriptor->id = id;
    descriptor->nbTermes = 0;
    descriptor->termes = NULL;
}

/** Remplis le descripteur donné en paramètre avec les informations de son 
 *  descripteur en utilisant le fichier donné en paramètre, utile si l'on veut 
 *  en faire plusieurs à la suite sans fermer et ouvrir le fichier.
 *  DESCR* descriptor : la structure du descripteur à remplir
 *  FILE* file : le fichier à utiliser pour le remplissage
 */
void fill_DESCR(DESCR* descriptor, FILE *file)
{
    int id, total;
    char line[500];

    descriptor->nbTermes = 0;

    while (fgets(line, 500, file) != NULL)
    {
        fscanf(file, "%d %d", &id, &total);

        if (id == descriptor->id)
        {
            char word[WORD_LENGTH_MAX];
            int occurence;

            descriptor->total = total;

            fscanf(file, "%s %d",word, &occurence);
            while (atoi(word) == 0 && !feof(file))
            {
                addWordandOcc_DESCR(descriptor, word, occurence);
                fscanf(file, "%s %d",word, &occurence);
                descriptor->nbTermes++;
            }

            return;
        }
    }
}

/** Remplis le descripteur donné en paramètre avec les informations de son 
 *  descripteur en utilisant le chemin du fichier donné en paramètre.
 *  DESCR* descriptor : la structure du descripteur à remplir
 *  FILE* file : le fichier à utiliser pour le remplissage
 */
void fillWithPath_DESCR(DESCR* descriptor, char* path)
{
    int id, total;
    char line[500];

    descriptor->nbTermes = 0;

    FILE* file = fopen(path, "r");

    while (fgets(line, 500, file) != NULL)
    {
        fscanf(file, "%d %d", &id, &total);

        if (id == descriptor->id)
        {
            char word[WORD_LENGTH_MAX];
            int occurence;

            descriptor->total = total;

            fscanf(file, "%s %d", word, &occurence);
            while (atoi(word) == 0 && !feof(file))
            {
                addWordandOcc_DESCR(descriptor, word, occurence);
                fscanf(file, "%s %d", word, &occurence);
                descriptor->nbTermes++;
            }

            return;
        }
    }

    fclose(file);
}

/** Ajoute un mot au descripteur.
 *  DESCR* descriptor : descripteur dans lequel on ajoute le mot
 *  char* word : mot à ajouter au descripteur
 */
void addWord_DESCR(DESCR* descriptor, char *word)
{
    // On recherche le terme
    TERMES prochainTerme = descriptor->termes;
    while (prochainTerme != NULL)
    {
        if (strcmp(prochainTerme->terme->word, word) == 0)
        {
            prochainTerme->terme->occurence++;
            return;
        }

        prochainTerme = prochainTerme->termeSuivant;
    }

    // Si on ne l'a pas trouvé on l'empile
    TERME* terme = malloc(sizeof(TERME*));
    TERMES termesTemp = (TERMES)malloc(sizeof(TERMES));

    strcpy(terme->word, word);
    terme->occurence = 1;

    termesTemp->terme = terme;
    termesTemp->termeSuivant = descriptor->termes;

    descriptor->termes = termesTemp;
}

/** Ajoute un mot et une occurence à un descripteur. 
 *  DESCR* descriptor : descriptor dans lequel on ajout le mot et son occurence
 *  char* word : mot à ajouter
 *  int occurence : occurence du mot à ajouer
 */
void addWordandOcc_DESCR(DESCR* descriptor, char* word, int occurence)
{
    TERME* terme = malloc(sizeof(TERME*));
    TERMES termesTemp = (TERMES)malloc(sizeof(TERMES));

    strcpy(terme->word, word);
    terme->occurence = occurence;

    termesTemp->terme = terme;
    termesTemp->termeSuivant = descriptor->termes;

    descriptor->termes = termesTemp;
}

/** Retourne l'occurence d'un mot cherché dans le descripteur donné.
 *  DESCR descriptor : descripteur dans lequel on recherche le mot
 *  char* word : mot à rechercher
 */
int getOccurence_DESCR(DESCR descriptor, char* word)
{
    char temp[30];
    TERMES prochainTerme = descriptor.termes;
    
    while (prochainTerme != NULL)
    {
        strcpy(temp, prochainTerme->terme->word);
        tolower_DESC_STR(temp);
        tolower_DESC_STR(word);
        if (strcmp(temp, word) == 0)
        {
            return prochainTerme->terme->occurence;
        }

        prochainTerme = prochainTerme->termeSuivant;
    }

    return 0;
}

/** Dépile un mot de la pile du descripteur.
 */
void removeWord_DESCR(DESCR* descriptor)
{
    if (descriptor->termes == NULL)
    {
        return;
    }

    TERME* termeTemp;
    termeTemp = descriptor->termes->terme;
    descriptor->termes = descriptor->termes->termeSuivant;
    free(termeTemp);
    descriptor->nbTermes--;
}

/** Retourne un terme à l'indice donné d'un descripteur donné.
 *  DESCR descriptor : descripteur dans lequel on recherche le terme à l'index donné
 *  int index : l'index du terme recherché
 */
TERME* get_DESCR(DESCR descriptor, int index)
{
    TERMES termes = descriptor.termes;

    for (int i = 0; i < index; i++)
    {
        termes = termes->termeSuivant;
    }

    return termes->terme;
}

/** Ferme un descripteur.
 *  Cette fonction le dépile et libère la place pris par celui-ci.
 */
void close_DESCR(DESCR* descriptor)
{
    for (int i = 0; i < descriptor->nbTermes - 1; i++)
    {
        removeWord_DESCR(descriptor);
    }
}
