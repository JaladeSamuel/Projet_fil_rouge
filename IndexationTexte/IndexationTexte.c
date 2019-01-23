#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
//CLASSE DE TEST en cours...

#include "IndexationTexte.h"

#define PATH "../Base_de_donnees/TEXTES/Textes/"
#define TAILLE 20
int main(void)
{

    int taille = 20;
    char str1[taille];
    FILE* fichier = NULL;
    fichier = fopen("03-Mimer_un_signal_nerveux_pour_utf8.xml", "r");

    int tailleOctetF;
    if (fichier == NULL){return 0;}

    fseek (fichier, 0, SEEK_END);   // non-portable
    tailleOctetF=ftell (fichier);
    rewind(fichier);
    printf("Taille octet du fichier : %d\n",tailleOctetF);
    char fichierString[tailleOctetF];
    int b = 1;
    while(b == 1)
    {
      b = fscanf(fichier,"%s",str1);
      strcat(fichierString, strcat(str1," "));
    }
    fclose(fichier);
    //printf("%s\n",fichierString );
    int balise = 0 , j= 0;
    char fichierStringF[tailleOctetF];
    char ponctuation[11] = ";,:?/!.\"()";
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
      if(!balise && strchr(ponctuation, fichierString[i]) == NULL) {
          printf("%c",fichierString[i]);
          fichierStringF[j] = fichierString[i];
          j++;

      }
    }
    fichierStringF[j++] = '\0';

    //printf("\n%s",fichierStringF);


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
