#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "IndexationTexte.h"

#define PATH "../Base_de_donnees/TEXTES/Textes/"

int main(void)
{
  //parcours du repertoire
  /* DIR *dir = opendir (PATH);

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

    return 0;*/
    unsigned int taille = 20;
    char str1[taille];
    FILE* fichier = NULL;
    fichier = fopen("03-Des_chercheurs_parviennent_α_rΘgΘnΘrer.xml", "r");

    char *ret;
    char ret2[2] = "<";
    int tailleOctetF;
    if (fichier != NULL)
    {
      fseek (fichier, 0, SEEK_END);   // non-portable
      tailleOctetF=ftell (fichier);
      rewind(fichier);
      printf("Taille octet du fichier : %d\n",tailleOctetF);
      char fichierString[tailleOctetF];
      //printf("NB Ligne : %d \n",nbLigne );
      int b = 1;

      while(b == 1)
      {
        b = fscanf(fichier,"%s",str1);
        /*if(str1[0] == '<') {
          balise = 1;
          printf("Balise ouvrante");
        }
        if(strstr(str1,">"))
        {
          balise = 0;
        }
        if(!balise){

        }*/
        strcat(fichierString, strcat(str1," "));
      }
      fclose(fichier);
      printf("%s\n",fichierString );
      /*int balise = 0;
      char fichierStringF[tailleOctetF];
      for(int i = 0; i<tailleOctetF; i++) {
        if(fichierString[i] == '<')
        {
          balise = 1;
          continue;
        }
        if(balise && fichierString[i] == '>')
        {
          balise = 0;
          continue;
        }
        if(!balise) {
            fichierStringF[i] = fichierString[i];
        }
      }
      printf("\n %s",fichierStringF);
    }*/

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
