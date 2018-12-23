#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "fileMot.h"

#include "IndexationTexte.h"

#define PATH "../Base_de_donnees/TEXTES/Textes/"

int main(void)
{


    FILE* fichier = NULL;
    fichier = fopen("03-Mimer_un_signal_nerveux_pour_utf8.xml", "r"); // Ouverture


    if (fichier == NULL){return 1;}

    int tailleOctetF;
    fseek (fichier, 0, SEEK_END);   // non-portable
    tailleOctetF=ftell (fichier);
    rewind(fichier);

    printf("Taille octet du fichier : %d\n",tailleOctetF);


    //On creer la fileMot
    File fileDeMot;
    INIT_FILE(&fileDeMot);



    char fichierString[tailleOctetF];
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
            ENFILER(&fileDeMot,mot); //incrementation de mot deja existant dans enfiler
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
    AFFICHER_FILE(&fileDeMot);

    File fileDescripteur;
    INIT_FILE(&fileDescripteur);

    char motFrequent[50];
    int nb;
    for(int i = 0; i<10; i++)
    {
      nb = defilerPlusGrand(&fileDeMot,motFrequent);
      if(nb>=2)
      {
        ENFILER_FREQUENT(&fileDescripteur,motFrequent,nb);
      }
    }
    //File de mot les plus frequent
    AFFICHER_FILE(&fileDescripteur);


    struct dirent *lecture;
    DIR *rep;
    rep = opendir("../Base_de_donnees/TEXTES/Textes/" );
    while ((lecture = readdir(rep))) {
        printf("%s\n", lecture->d_name);
    }
    closedir(rep);
    //ECRITURE DU DESCRIPTEUR DANS LE fichier
    FILE* fichierDescripteur = NULL;
    fichierDescripteur = fopen("descripteur_base_texte.txt", "w");

    if (fichierDescripteur == NULL){return 2;}
    char motDefile[50];
    while(!estVide(&fileDescripteur))
    {
      fprintf(fichierDescripteur, "%s %d ",motDefile,DEFILER(&fileDescripteur,motDefile));
    }
    fprintf(fichierDescripteur,"\n");
    fclose(fichierDescripteur);
    return 0;
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
