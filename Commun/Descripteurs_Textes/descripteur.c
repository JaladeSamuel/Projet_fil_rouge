#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descripteur.h"

void init_DESCR(DESCR *descriptor, int id)
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
                // printf("%s ", word);
                addWord_DESCR(descriptor, word);
            }

            return;
        }
    }
}

void addWord_DESCR(DESCR *descriptor, char *word)
{
    if (descriptor->termes != NULL)
    {
        TERME *terme;

        strcpy(terme->word, word);
        terme->occurence = 1;

        descriptor->termes->terme = terme;
        descriptor->termes->termeSuivant = NULL;
    }
    else
    {
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
    }
}