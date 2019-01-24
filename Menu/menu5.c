#include <stdio.h>
#include <string.h>
#include"menu2.h"
#include"menu5.h"
#include"menu3.h"
#include"menu1.h"

void indexation(){
	int choix;
	char saisie[255];

	while(1)
	{
		printf("\nSélectionner le type du fichier à indexer :\n1 - Fichier texte\n2 - Fichier image\n3 - Retour\n4 - Quitter\nChoix : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &choix) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}
	switch(choix){
	case 1 :
		test_adresse();
		break;
	case 2 :   
		test_adresse();
		break;
	case 3 : 
		choix_adm();
		break;
	case 4 : 
		quitter();
		break;
	default : 
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\" ou \"4\".");
		indexation();
		break;
	} 
}

void configuration(){
	int choix;
	char saisie[255];
	while(1)
	{
		printf("\n\nConfigurer : \n1 - Configuration générale\n2 - Configuration Texte\n3 - Configuration Image\n4 - Retour\n5 - Quitter\nChoix : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &choix) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}
	switch(choix){
	case 1: system("nano ../Config/config.txt");
		break;
	case 2: system("nano ../Config/config_texte.txt");
		break;
	case 3: system("echo \"En Travaux...\"");
		break;
	case 4: 
		choix_adm();
		break;
	case 5 : 
		quitter();
		break;
	default : 
		choix_adm();
		break;
	}
}

void choix_adm(){

	int choix;
	char saisie[255];

	while(1)
	{
		
		printf("\n\nSélectionner une action :\n1 - Lancer une recherche\n2 - Accéder aux descripteurs\n3 - Lancer une indexation\n4 - Modifier les configurations\n5 - Retour\n6 - Quitter\nChoix : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &choix) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}
	
	switch(choix){
	case 1 : 
		menu2_adm();
		break;
	case 2 :
		printf("\nAffichage des descripteurs : \n\n");
		system("cat ../Commun/descripteur_base_texte.txt");
		choix_adm();
		break;
	case 3 :
		indexation();
		break;
	case 4 :
		configuration();
		break;
	case 5 : 
		menu1();
		break;
	case 6 :
		quitter();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\",\"4\",\"5\" ou \"6\".\n");
		choix_adm();
		break;
	}	
}
