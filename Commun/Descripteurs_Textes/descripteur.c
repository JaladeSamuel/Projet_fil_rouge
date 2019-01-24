#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descripteur.h"

void init_DESCR(DESCR* descriptor, int id)
{
    descriptor->id = id;
    descriptor->nbTermes = 0;
    descriptor->termes = NULL;
}

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

TERME* get_DESCR(DESCR descriptor, int index)
{
    TERMES termes = descriptor.termes;

    for (int i = 0; i < index; i++)
    {
        termes = termes->termeSuivant;
    }

    return termes->terme;
}

void close_DESCR(DESCR* descriptor)
{
    for (int i = 0; i < descriptor->nbTermes - 1; i++)
    {
        removeWord_DESCR(descriptor);
    }
}
