#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "indexationV1.h"


/*int main(void)
{
   indexationBaseTexte();
   return 0;
}*/


int indexationFichierTexte(char *cheminFichier, DESCR* descripteur)
{
  load_config_texte();
  printf("Generation du descripteur pour le fichier : %s\n",cheminFichier);
  File fileDeMotDuFichier;
  INIT_FILE(&fileDeMotDuFichier);
  fileMotFichier(&fileDeMotDuFichier,cheminFichier,0);
  fileMotFrequentDansDESCR(&fileDeMotDuFichier,descripteur);
  return 1;
}

int indexationBaseTexte()
{
    load_config_texte();
    //LECTURE des fichier du repertoire bd
    struct dirent *lecture;
    DIR *rep;
    rep = opendir(PATH_BD);


    FILE* fichierDescripteur = NULL;
    fichierDescripteur = fopen("../Commun/descripteur_base_texte.txt", "w"); //LEs descripteurs genere seront ecrit dans ce fichier

    File fileDeMot;
    File fileDescripteur;

    FileChemin fileTableIndex;
    INIT_FILE_TABLE_INDEX(&fileTableIndex);
    //AFFICHER_FILE_TABLE_INDEX(&fileTableIndex);
    int aucunFichierIndexe = 1;

    char motDefile[50];
    int id = 0, nb = 0;
    printf("-------------------------------------------\n");
    printf("|            INDEXATION texte ...         |\n");
    //parcour des fichiers du repertoire

    while ((lecture = readdir(rep))) {//nom du fichier = lectur ->d_name

        if(strcmp(lecture->d_name,"..") == 0 || strcmp(lecture->d_name,".") == 0){
          continue;
        }
      //  printf("%s\n", lecture->d_name);
    /*    if(fileContainsChemin(&fileTableIndex,lecture->d_name))
        {
          printf("Fichier : %s deja indexe\n",lecture->d_name);
          continue;
        } */

        //Convertit les fichier ISO-8859-1 en UTF-8
        /*char conv[500] = {"iconv -f ISO-8859-1 -t UTF-8 "};
        strcat(conv,"../Base_de_donnees/texte2/");
        strcat(conv,lecture->d_name);
        strcat(conv," -o ");
        strcat(conv,"../Base_de_donnees/texte2/");
        strcat(conv,lecture->d_name);
        printf("%s\n",conv);
        system(conv);*/

        aucunFichierIndexe = 0;
        //INITIALISATION DES FILES
        INIT_FILE(&fileDeMot);
        INIT_FILE(&fileDescripteur);



        fileMotFichier(&fileDeMot,lecture->d_name,1);
        fileMotFrequent(&fileDeMot,&fileDescripteur);//free

        if (fichierDescripteur == NULL){return 1;}
        fprintf(fichierDescripteur,"%d %d ",id,fileDeMot.nbMot);
        while(!estVide(&fileDescripteur))
        {
          nb = DEFILER(&fileDescripteur,motDefile); //free
          fprintf(fichierDescripteur, "%s %d ",motDefile,nb);
        }

        fprintf(fichierDescripteur,"\n");

        reinit(&fileDeMot);
        reinit(&fileDescripteur);

        ENFILER_CHEMIN(&fileTableIndex, lecture->d_name, id);
        id++;


    }// end while

    fclose(fichierDescripteur);
    closedir(rep);
    //Si au moin un fichier a ete indexe
    if(!aucunFichierIndexe)
    {
      actualiserTableTexteIndex(&fileTableIndex); //on actualise la table
    }

    printf("| INDEXATION TERMINE | %d fichiers indexe |\n",id);
    printf("-------------------------------------------\n");
    return 0;
}

/*
**Ajoute les mots du fichier texte dans une file, si le mot est deja existant dans la file
**le compteur du mot est incremente.
*/
void fileMotFichier(File *fileDeMot, char *nomFichier,int dansBase)
{

  char path[200] = PATH_BD;
  if(dansBase)
  {
    strcat(path,nomFichier);
  } else {
    memset(path,'\0',sizeof(nomFichier));
    strcpy(path,nomFichier);
  }


  FILE* fichier = NULL;
  fichier = fopen(path, "r"); // Ouverture

  if (fichier == NULL){printf("On sors nom fichier %s\n",nomFichier);return;}
  char caractereActuel;
  int balise = 0, i = 0, espace = 0;
  char ponctuation[11] = ";,:?/!.\"()";
  char mot[50];

  // Boucle de lecture des caractères un à un
  while(!feof(fichier))// On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
  {
      caractereActuel = fgetc(fichier); // On lit le caractère
      if(caractereActuel == '<')
      {
        balise = 1;
        continue;
      }
      if(balise && caractereActuel == '>')
      {
        balise = 0;
        continue;
      }

      if((caractereActuel == ' ' || caractereActuel == '\n' || caractereActuel == '.' || caractereActuel == ',') && balise == 0 )
      {
        if(strlen(mot)>lg_mini_mots)//lg_mini_mots est une variable globale cf : load_config_texte On ne prend en compte que les mots plus grand que lg_mini_mots
        {
          ENFILER(fileDeMot,mot); //incrementation de mot deja existant dans enfiler
        }
        for(int i = 0; i<50; i++)
        {
          mot[i] = '\0';
        }
        i = 0;
      }else{
        if(balise == 0 && strchr(ponctuation, caractereActuel) == NULL) {
          mot[i] = caractereActuel;
          i++;
        }
      }
  }
  fclose(fichier);
}
/*
**Prend une file de mot A et enfile dans une seconde File B les mots les plus frequent de A.
*/
void fileMotFrequent(File *fileDeMot, File *fileMotFrequent)
{
  char motFrequent[50];
  int nb;
  for(int i = 0; i<nb_termes_max; i++)//nb_termes_max est une variable globale cf : load_config_texte
  {
    nb = defilerPlusGrand(fileDeMot,motFrequent);
    if(nb > 0){
      ENFILER_FREQUENT(fileMotFrequent,motFrequent,nb);
    }
  }
}

/*
**Prend une file de mot A et enfile dans un DESCR (pour la comparaison) B les mots les plus frequent de A.
*/
void fileMotFrequentDansDESCR(File *fileDeMot, DESCR *fileMotFrequent)
{
  char motFrequent[50];
  int nb;
  int nbTermes = 0;
  int nbMotsTotal = fileDeMot->nbMot;
  for(int i = 0; i<10; i++)
  {
    nb = defilerPlusGrand(fileDeMot,motFrequent);
    if(nb > 0){
      addWordandOcc_DESCR(fileMotFrequent,motFrequent,nb);
      nbTermes++;
    }
  }
  //passage des attributs pour la structure descripteur de comparaison
  fileMotFrequent->nbTermes = nbTermes;
  fileMotFrequent->total = nbMotsTotal;
}

void actualiserTableTexteIndex(FileChemin *file)
{
  FILE* fichierTableIndex = NULL;
  fichierTableIndex = fopen("../Commun/tableTexteIndex.txt","w");
  if (file == NULL)
  {
      exit(EXIT_FAILURE);
  }

  CheminDescripteur *cel = file->premier;
  while (cel != NULL)
  {
      fprintf(fichierTableIndex,"%d %s\n",cel->id,cel->chemin);
      cel = cel->suivant;
  }
  fclose(fichierTableIndex);
}

void load_config_texte()
{
  FILE* fichierConfig = NULL;
  fichierConfig = fopen("../Config/config_texte.txt","r");
  if(fichierConfig == NULL)
  {
    printf("Impossible de charger le fichier config_texte\n");
    exit(EXIT_FAILURE);
  }
  char tamp[100];
  //CHARGEMENT DES PARAMETRES
  rewind(fichierConfig);//positionne le flag au debut du fichier
  fscanf(fichierConfig,"%s %d",tamp,&nb_termes_max);
  fscanf(fichierConfig,"%s %d",tamp,&lg_mini_mots);
}
