# include <stdio.h>
#include"menu2.h"
#include"menu3.h"
#include"menu4.h"



void menu2(){
	int type = 0;
	char saisie[255];
	
	while(1)
	{
		printf("\nSélectionner le type de fichier recherché :\n1 - Texte\n2 - Image\n3 - Son\n4 - Retour\nType de fichier : ");
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
		printf("\nEn travaux ...\n");
		break;
	case 4 :
		menu1();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\" ou \"4\".\n");
		menu2();
		break;
	}	
}

void menu2_adm(){
	
	int type = 0;
	char saisie[255];
	
	while(1)
	{
		printf("\nSélectionner le type de fichier recherché :\n1 - Texte\n2 - Image\n3 - Son\n4 - Retour\nType de fichier : ");
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
		printf("\nEn travaux ...\n");
		break;
	case 4 :
		choix_adm();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\" ou \"4\".\n");
		menu2();
		break;
	}	
}
