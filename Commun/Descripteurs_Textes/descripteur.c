#include <stdio.h>
#include <stdlib.h>
#include "descripteur.h"

void init_DESCR(DESCR *descriptor, int id)
{
    descriptor->id = id;
}

void fill_DESCR(DESCR descriptor, FILE *file)
{
    int id, termes, total;
    size_t len = 0;
    char line[100];

    while (fgets(line, 100, file) != NULL)
    {
        fscanf(file, "%d %d %d\n", &id, &termes, &total);

        if (id == descriptor.id)
        {
            descriptor.termes = termes;
            descriptor.total = total;

            fgets(line, 100, file);
            printf("%s", line);
            return;
        }
    }
}

void addWord_DESCR(DESCR descriptor, char* word)
{

}