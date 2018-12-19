#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descripteur.h"

void init_DESCR(DESCR* descriptor, int id)
{
    descriptor->id = id;
    descriptor->termes = NULL;
}

void fill_DESCR(DESCR* descriptor, FILE *file)
{
    int id, termes, total;
    char line[100];

    while (fgets(line, 100, file) != NULL)
    {
        fscanf(file, "%d %d %d\n", &id, &termes, &total);

        if (id == descriptor->id)
        {
            char word[WORD_LENGTH_MAX];
            int occurence, i;

            descriptor->nbTermes = termes;
            descriptor->total = total;

            for (i = 0; i < termes; i++)
            {
                fscanf(file, "%s %d", &word, &occurence);
                addWordandOcc_DESCR(descriptor, word, occurence);
            }

            return;
        }
    }
}

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

int getOccurence_DESCR(DESCR descriptor, char* word)
{
    TERMES prochainTerme = descriptor.termes;
    while (prochainTerme != NULL)
    {
        if (strcmp(prochainTerme->terme->word, word) == 0)
        {
            return prochainTerme->terme->occurence;
        }

        prochainTerme = prochainTerme->termeSuivant;
    }

    return 0;
}

void removeWord_DESCR(DESCR* descriptor, TERME* terme)
{
    if (descriptor->termes == NULL)
    {
        terme = NULL;
        return;
    }

    TERME* termeTemp;

    terme = descriptor->termes->terme;
    termeTemp = descriptor->termes->terme;
    descriptor->termes = descriptor->termes->termeSuivant;
    free(termeTemp);
}