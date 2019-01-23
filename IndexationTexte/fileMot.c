#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileMot.h"

void INIT_FILE(File *file)
{
    file->premier = NULL;
    file->nbMot = 0;
    file->occurencePlusGrande = 0;
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
              /*printf("Mot actuel %s : ",celActuel);
              printf("Mot qui veut integrer la file %s\n",nouveau->mot);*/
              celActuel->occurence += 1;
              if(celActuel->occurence > file->occurencePlusGrande)
              {
                file->occurencePlusGrande = celActuel->occurence;
              }
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

void ENFILER_FREQUENT(File *file, char *nvElement, int nbOccurence)
{

    Cellule *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    file->nbMot += 1;
    strcpy(nouveau->mot,nvElement);
    nouveau->occurence = nbOccurence;
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


int DEFILER(File *file, char *motDefile)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    file->nbMot -= 1;
    int nb = -1;
    /* On vérifie s'il y a quelque chose à défiler */
    if (file->premier != NULL)
    {
        Cellule *celDefile = file->premier;

        strcpy(motDefile,celDefile->mot);
        nb = celDefile->occurence;
        file->premier = celDefile->suivant;
        free(celDefile);
    }
    return nb;
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
    printf("Occurence la plus grande : %d \n",file->occurencePlusGrande);
}

int defilerPlusGrand(File *file, char *mot)
{
  if (file == NULL)
  {
      printf("file vide exit\n");
      exit(EXIT_FAILURE);
  }
  int nb = 0;
  if (file->premier != NULL)
  {

    Cellule *cel = file->premier;
    Cellule *tamp;
    if(file->occurencePlusGrande < 2)// OCCURENCE MINIMUM DU MOT
    {
      while(cel->suivant != NULL)
      {
        tamp = cel;
        cel = cel->suivant;
      }
      strcpy(mot,cel->mot);
      nb = cel->occurence;
      tamp->suivant = cel->suivant;

      free(cel);
      //on redefinit le plus
      return nb;
    }
    while(cel->occurence < file->occurencePlusGrande && cel->suivant != NULL)
    {
      tamp = cel;
      cel = cel->suivant;
    }
    strcpy(mot,cel->mot);
    nb = cel->occurence;
    tamp->suivant = cel->suivant;

    free(cel);
    //on redefinit le plus grand
    file->occurencePlusGrande = 0;
    cel = file->premier;
    while (cel != NULL)
    {
        if(cel->occurence > file->occurencePlusGrande)
        {
          file->occurencePlusGrande = cel->occurence;
        }
        cel = cel->suivant;
    }
  }
  return nb;
}

int estVide(File *file)
{
  if(file->premier == NULL)
  {
    return 1;
  }
  return 0;
}

void reinit(File *file)
{
  char c[100];
  while(file->premier != NULL)
  {
    DEFILER(file,c);

  }
}
///////////////
//FILE_CHEMIN//
///////////////
void ENFILER_CHEMIN(FileChemin *file, char *nvChemin, int nvId)
{
  //  printf("CHEMIN PARAMETRE DANS ENFILER CHEMIN : %s\n",nvChemin);
    CheminDescripteur *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->chemin = nvChemin;
    nouveau->id = nvId;
    nouveau->suivant = NULL;
    if (file->premier != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        CheminDescripteur *chActuel = file->premier;
        while(chActuel->suivant != NULL)
        {
            chActuel = chActuel->suivant;
        }
        chActuel->suivant = nouveau;
    }
    else /* La file est vide, notre élément est le premier */
    {
        file->premier = nouveau;
    }
}

int tableTexteIndexEstVide()
{
  int taille = 0;
  FILE* fichierTableIndex = NULL;
  fichierTableIndex = fopen("../Commun/tableTexteIndex.txt","r");
  if(fichierTableIndex == NULL)
  {
    printf("Erreur : fichier NULL \n");
    return -1;
  }
  fseek(fichierTableIndex, 0, SEEK_END);
  taille = ftell(fichierTableIndex);
  fclose(fichierTableIndex);
  if(taille)
  {
    return 0;
  } else {
    return 1;
  }
}

void INIT_FILE_TABLE_INDEX(FileChemin *file)
{
    if(tableTexteIndexEstVide() || 1)
    {
      file->premier = NULL;
    } else {
      FILE* fichierTableIndex = NULL;
      fichierTableIndex = fopen("../Commun/tableTexteIndex.txt","r");
      if(fichierTableIndex == NULL)
      {
        printf("Erreur : fichier NULL \n");
        exit(EXIT_FAILURE);
      }
      rewind(fichierTableIndex);
      int t;
      char path[500];
      while(!feof(fichierTableIndex))
      {
        fscanf(fichierTableIndex,"%d %s",&t,path);
        //printf("%s\n",chemin);
        ENFILER_CHEMIN(file,path,t);
      }
      rewind(fichierTableIndex);
      fclose(fichierTableIndex);
    }

}

int fileContainsChemin(FileChemin *file, char *chemin)
{
  if(file->premier == NULL || tableTexteIndexEstVide())
  {
    printf("0 premier nul \n");
    return 0;
  }

  CheminDescripteur *cel = file->premier;
  while (cel != NULL)
  {

    if(strcmp(chemin,cel->chemin) == 0)
    {
      printf("1\n");
      return 1;
    }
    printf("chemin parametre : %s Chemin file : %s NE SONT PAS =\n",chemin,cel->chemin);
    printf("%s\n",(cel->suivant)->chemin);
    cel = cel->suivant;
  }
  printf("0 aucun chemin == cel->chemin\n");
  return 0;
}

void AFFICHER_FILE_TABLE_INDEX(FileChemin *file)
{
    if (file == NULL)
    {
        printf("ERREUR : File vide");
        exit(EXIT_FAILURE);
    }

    CheminDescripteur *cel = file->premier;

    while (cel != NULL)
    {
        printf("Cellule : %s | id : %d \n",cel->chemin,cel->id);
        cel = cel->suivant;
    }
}
