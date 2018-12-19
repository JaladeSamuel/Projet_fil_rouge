#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void INIT_FILE(File *file)
{
    file->premier = NULL;
}


void ENFILER(File *file, ELEMENT nvElement)
{

    Cellule *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->element = nvElement;
    nouveau->suivant = NULL;
    if (file->premier != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Cellule *celActuel = file->premier;
        while (celActuel->suivant != NULL)
        {
            celActuel = celActuel->suivant;
        }
        celActuel->suivant = nouveau;
    }
    else /* La file est vide, notre élément est le premier */
    {
        file->premier = nouveau;
    }
}


int DEFILER(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDefile = 0;

    /* On vérifie s'il y a quelque chose à défiler */
    if (file->premier != NULL)
    {
        Cellule *celDefile = file->premier;

        nombreDefile = celDefile->element;
        file->premier = celDefile->suivant;
        free(celDefile);
    }

    return nombreDefile;
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
         affiche_ELEMENT(cel->element);
        cel = cel->suivant;
    }

    printf("\n");
}


int main()
{
    MA_FILE maFile;
    INIT_FILE(&maFile);
    /*for(int i = 0; i<20; i++){
      ENFILER(&maFile, i);
    }*/
    SAISIR_FILE(&maFile);

    printf("\nAffichage file :\n");
    AFFICHER_FILE(&maFile);

    printf("\nJe defile %d\n", DEFILER(&maFile));
    printf("Je defile %d\n", DEFILER(&maFile));

    printf("\nEtat de la file :\n");
    AFFICHER_FILE(&maFile);


    //DEUXIEME PARTIE
    printf("DEUXIEME PARTIE\n");
    printf("------------\n");
    MA_FILE seance1;
    MA_FILE seance2;
    MA_FILE seance3;
    MA_FILE seance4;
    INIT_FILE(&seance1);
    INIT_FILE(&seance2);
    INIT_FILE(&seance3);
    INIT_FILE(&seance4);
    int j = 0;
    int caisse = 0;
    for(int i = 0; i<6; i++){
      ENFILER(&seance1, i);
      caisse += i;
      j++;
    }
    for(int i = 0; i<6; i++){
      ENFILER(&seance1, i);
      caisse += i;
      j++;
    }
    for(int i = 0; i<6; i++){
      ENFILER(&seance1, i);
      caisse += i;
      j++;
    }
    for(int i = 0; i<6; i++){
      ENFILER(&seance1, i);
      caisse += i;
      j++;
    }
    printf("Il y a 4 seances dans la journee\n");
    printf("Nombre de tickets vendu : %d \n",caisse);
    printf("Nombre de client : %d",j);

    return 0;
}
