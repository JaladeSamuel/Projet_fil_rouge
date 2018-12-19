#include <stdio.h>
#include <stdlib.h>
#include "descripteur.h"

void init_DESCR(DESCR* descriptor, int id)
{
    descriptor->lastWordIndex = 0;
    descriptor->id = id;
}

void fill_DESCR(DESCR descriptor, FILE* file)
{
    int id, termes, total;
    size_t len = 0;
    char* line = NULL;

    while (getline(&line, &len, file) != EOF)
    {
        fscanf(file, "%d %d %d\n", &id, &termes, &total);
        printf("%d %d %d\n", id, termes, total);
    }
}