/** XIONG Amelie
*   menu2.c concerne les choix possibles lorsqu'on désire faire une recherche
*/

# include <stdio.h>
#include"menu2.h"
#include"menu3.h"
#include"menu4.h"



/** Fonction qui permet le choix du type du fichier recherché : 
*   int type = variable contenant la valeur de saisie
*   char saisie[255} = chaine de contrôle sur la saisie
*/
void menu2(){
	int type = 0;
	char saisie[255];
	//contrôle sur la saisie, on attend un entier.
	while(1)
	{
		printf("\nSélectionner le type de fichier recherché :\n1 - Texte\n2 - Image\n3 - Retour\n4 - Quitter\nType de fichier : ");
		fgets(saisie, 255, stdin);

		if (saisie[0] == '\n') // on a des "restes" du stdin, on re demande la saisie 
			fgets(saisie, 255, stdin);

		if (sscanf(saisie, "%d", &type) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}
	
	switch(type){
	case 1 : 
		menu3();
		break;
	case 2 :
		Recherche_image();
		break;
	case 3 :
		menu1();
		break;
	case 4:
		quitter();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\" ou \"4\".\n");
		break;
	}

	menu2();
	saisie[0] = '\0';
}


/**Fonction qui permet le choix du type du fichier recherché 
*  en tant qu'administrateur.
*  Il s'agit de la même fonction que menu2()
*  avec comme unique différence un retour 
*  vers les choix administrateur.
*/
void menu2_adm(){
	
	int type = 0;
	char saisie[255];
	//contrôle de saisie
	while(1)
	{
		printf("\nSélectionner le type de fichier recherché :\n1 - Texte\n2 - Image\n3 - Retour\n4 - Quitter\nType de fichier : ");
		fgets(saisie, 255, stdin);

		if (saisie[0] == '\n') // on a des "restes" du stdin, on re demande la saisie 
			fgets(saisie, 255, stdin);
		
		if (sscanf(saisie, "%d", &type) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}

	switch(type){
	case 1 : 
		menu3();
		break;
	case 2 :
		Recherche_image();
		break;
	case 3 :
		choix_adm();
		break;
	case 4 :
		quitter();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\" ou \"4\".\n");
		break;
	}

	menu2();
}
