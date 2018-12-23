#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "fileMot.h"
#include "IndexationTexte.h"
#include "indexationV1.h"

#define PATH "../Base_de_donnees/TEXTES/"



int main(void)
{
    //LECTURE des fichier du repertoire bd
    struct dirent *lecture;
    DIR *rep;
    rep = opendir(PATH);


    FILE* fichierDescripteur = NULL;
    fichierDescripteur = fopen("../Commun/descripteur_base_texte.txt", "w");

    File fileDeMot;
    File fileDescripteur;


    char motDefile[50];
    int id = 0, nb = 0;
    while ((lecture = readdir(rep))) {//nom du fichier = lectur ->d_name
        if(strcmp(lecture->d_name,"..") == 0 || strcmp(lecture->d_name,".") == 0 ){

        }else{
          INIT_FILE(&fileDeMot);
          INIT_FILE(&fileDescripteur);


          printf("\n%s\n", lecture->d_name);
          fileMotFichier(&fileDeMot,lecture->d_name);
          fileMotFrequent(&fileDeMot,&fileDescripteur);//free


          if (fichierDescripteur == NULL){return 1;}
          fprintf(fichierDescripteur,"%d %d ",id,fileDeMot.nbMot);
          AFFICHER_FILE(&fileDescripteur);
          while(!estVide(&fileDescripteur))
          {
            printf("On ECRIT\n");
            nb = DEFILER(&fileDescripteur,motDefile); //free
            fprintf(fichierDescripteur, "%s %d ",motDefile,nb);
          }

          fprintf(fichierDescripteur,"\n");
          id++;

          reinit(&fileDeMot);

        }


    }
    fclose(fichierDescripteur);
    closedir(rep);
    return 0;
}

void fileMotFichier(File *fileDeMot, char *nomFichier)
{

  char path[200] = PATH;

  strcat(path,nomFichier);

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

      if(caractereActuel == ' ' || caractereActuel == '\n' || caractereActuel == '.' || caractereActuel == ',' && balise == 0 )
      {
        if(strlen(mot)>5)//On ne prend en compte que les mots plus grand que 5
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

void fileMotFrequent(File *fileDeMot, File *fileMotFrequent)
{
  char motFrequent[50];
  int nb;
  for(int i = 0; i<10; i++)
  {
    nb = defilerPlusGrand(fileDeMot,motFrequent);
    if(nb>=2)
    {
      ENFILER_FREQUENT(fileMotFrequent,motFrequent,nb);
    }
  }
}

/*int compteNbLigne(FILE *fichier)
{
	int c;
	int nLignes = 0;
	int c2 = '\0';

	while((c=fgetc(fichier)) != EOF)
	{
		if(c=='\n')
			nLignes++;
		c2 = c;
	}

	// Ici, c2 est égal au caractère juste avant le EOF.
	if(c2 != '\n')
		nLignes++; // Dernière ligne non finie

	return nLignes;
}*/
