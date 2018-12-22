#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileMot.h"

void INIT_FILE(File *file)
{
    file->premier = NULL;
    file->nbMot = 0;
}


void ENFILER(File *file, char *nvElement)
{

    Cellule *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    file->nbMot += 1;
    strcpy(nouveau->mot,nvElement);
    nouveau->occurence = 1;
    nouveau->suivant = NULL;
    if (file->premier != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Cellule *celActuel = file->premier;
        while (celActuel->suivant != NULL)
        {
            if(strcmp(celActuel->mot,nouveau->mot) == 0)
            {
              celActuel->occurence += 1;
              return;
            }
            celActuel = celActuel->suivant;
        }
        celActuel->suivant = nouveau;
    }
    else /* La file est vide, notre élément est le premier */
    {
        file->premier = nouveau;
    }
}


void DEFILER(File *file, char *motDefile)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    file->nbMot -= 1;
    /* On vérifie s'il y a quelque chose à défiler */
    if (file->premier != NULL)
    {
        Cellule *celDefile = file->premier;

        strcpy(motDefile,celDefile->mot);
        file->premier = celDefile->suivant;
        free(celDefile);
    }
}

void AFFICHER_FILE(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Cellule *cel = file->premier;

    while (cel != NULL)
    {
        printf("%s : %d\n",cel->mot,cel->occurence);
        cel = cel->suivant;
    }

    printf("\n");
    printf("Nombre de mot total : %d \n",file->nbMot);
}

int nbOccurence(File *file, char *mot)
{

}
