/*
** indexationV1.c
** Samuel Jalade
** Contient tout les fonctions necessaire pour indexer la base de donnees texte ainsi que
** Indexation temporaire de fichier unique et d ajout de fichier a la base de donnees texte
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "indexationV1.h"
#include <dlfcn.h>

/*int main(void)
{
   indexationBaseTexte();
   return 0;
}*/

//Indexe un fichier unique et rempli la structure descripeur pour decrire le fichier
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

//permet d ajouter des fichiers xml a la base de donnee et indexe a nouveau la base pour actualiser
void ajoutDocBase(char *path)
{
  char temp = path[0];
  int lastSlash = 0;
  int dotPosition = strlen(path);
  for (int i = 0; i < strlen(path); i++)
  {
    if (path[i] == '/')
    {
      lastSlash = i + 1;
    }
    else if (path[i] == '.')
    {
      dotPosition = i;
      break;
    }
  }
  char nomFichier[100];
  int i = 0;
  for (int j = lastSlash; j < dotPosition; j++)
  {
    nomFichier[i] = path[j];
    i++;
  }
  char command[500];
  sprintf(command, "cp %s ../noyau_c/Base_de_donnees/TEXTES/%s", path, nomFichier);
  system(command);
  indexationBaseTexte();
}

//Parcours toute la base est indexa chaque fichier a la vole
int indexationBaseTexte()
{
  load_config_texte();
  //LECTURE des fichier du repertoire bd
  struct dirent *lecture;
  DIR *rep;
  rep = opendir(PATH_BD);


  FILE* fichierDescripteur = NULL;
  fichierDescripteur = fopen("../noyau_c/Commun/descripteur_base_texte.txt", "w"); //LEs descripteurs genere seront ecrit dans ce fichier

  File fileDeMot;
  File fileDescripteur;

  FileChemin fileTableIndex;
  INIT_FILE_TABLE_INDEX(&fileTableIndex);
  //AFFICHER_FILE_TABLE_INDEX(&fileTableIndex);
  int aucunFichierIndexe = 1;
  
  char motDefile[50];
  int id = 0, nb = 0;

  //parcour des fichiers du repertoire
  while ((lecture = readdir(rep))) {//nom du fichier = lectur ->d_name
    if(strcmp(lecture->d_name,"..") == 0 || strcmp(lecture->d_name,".") == 0){
      continue;
    }

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

//fonction non qui permet d actualiser la table de chemin et d ID des descripteurs indexes
void actualiserTableTexteIndex(FileChemin *file)
{
  FILE* fichierTableIndex = NULL;
  fichierTableIndex = fopen("../noyau_c/Commun/tableTexteIndex.txt","w");
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
/*
**Charge les variable par le fichier de configuration config_texte.txt
*/
void load_config_texte()
{
  FILE* fichierConfig = NULL;
  fichierConfig = fopen("../noyau_c/Config/config_texte.txt","r");
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
