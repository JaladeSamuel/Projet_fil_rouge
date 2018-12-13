#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define PATH "../Base_de_donnees/TEXTES/Textes/"

int main(void)
{
   DIR *dir = opendir (PATH);

   struct dirent *dp;
   int filecount = 0;

   if (dir == NULL)
    {
        printf("pas de dossier");
    }

   while ((dp = readdir (dir)) != NULL) //tant qu'il y'a des fichiers non lu dans le dossier
    {
        filecount++;
        printf("%s\n", dp->d_name);
    }

    printf("\nil y a %d trucs dans de dossier\n\n",filecount);

    return 0;
}
