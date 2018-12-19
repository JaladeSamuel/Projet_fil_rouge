#include <stdio.h>
#include <string.h>
#include"menu2.h"
#include"menu5.h"
#include"menu3.h"

void indexation(){
	int choix;
	printf("\nSélectionner le type du fichier à indexer :\n1 - Fichier texte\n2 - Fichier image\n3 - Fichier son\n4 - Retour\nChoix : ");
	scanf("%d",&choix);
	
	switch(choix){
	case 1 :
		adresse();
		break;
	case 2 :   
		adresse();
		break;
	case 3 : 
		adresse();
		break;
	case 4 : 
		choix_adm();
		break;
	default : 
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\" ou \"4\".");
		indexation();
		break;
	} 
}

void choix_adm(){

	int choix;
	printf("\nSélectionner une action :\n1 - Lancer une recherche\n2 - Accéder aux descripteurs\n3 - Lancer une indexation\n4 - Modifier les configurations\n5 - Retour\nChoix : ");
	scanf("%d",&choix);


	switch(choix){
	case 1 : 
		menu2_adm();
		break;
	case 2 :
	case 3 :
		indexation();
		break;
	case 4 :
		printf("\nEn travaux...\n");
		break;
	case 5 : 
		menu1();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\",\"4\" ou \"5\".\n");
		choix_adm();
		break;
	}	
}
