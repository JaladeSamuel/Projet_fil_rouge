# include <stdio.h>
#include"menu2.h"
#include"menu3.h"
#include"menu4.h"
#include"menu1.h"



void menu2(){
	printf("\nSélectionner le type de fichier recherché :\n1 - Texte\n2 - Image\n3 - Son\n4 - Retour\n5 - Quitter\nType de fichier : ");
	int type = 0;
	scanf("%d",&type);

	switch(type){
	case 1 : 
		menu3();
		break;
	case 2 :
		Recherche_image();
		break;
	case 3 :
		printf("\nEn travaux ...\n");
		menu2();
		break;
	case 4 :
		menu1();
		break;
	case 5 : 
		Exit();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\" ou \"4\".\n");
		menu2();
		break;
	}	
}

void menu2_adm(){
	printf("\nSélectionner le type de fichier recherché :\n1 - Texte\n2 - Image\n3 - Son\n4 - Retour\nType de fichier : ");
	int type = 0;
	scanf("%d",&type);

	switch(type){
	case 1 : 
		menu3();
		break;
	case 2 :
		Recherche_image();
		break;
	case 3 :
		printf("\nEn travaux ...\n");
		menu2_adm();
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
