#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include"menu2.h"
#include"menu5.h"
#include"menu3.h"
#include"menu1.h"

/** choix entre une indexation de fichier texte 
*   ou de fichier image
*/
void indexation(){
	int choix;
	char saisie[255];
	//contrôle sur la saisie
	while(1)
	{
		printf("\nSélectionner le type du fichier à indexer :\n1 - Fichier texte\n2 - Fichier image\n3 - Retour\n4 - Quitter\nChoix : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &choix) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}

	switch(choix)
	{

	case 1 :
		nouveauFichierTexte();
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


/** choix entre configurer le fichier de configuration générale 
*   ou le fichier de configuration texte
*/
void configuration(){
	int choix;
	char saisie[255];
	//contrôle de saisie
	while(1)
	{
		printf("\n\nConfigurer : \n1 - Configuration générale\n2 - Configuration Texte\n3 - Configuration Image\n4 - Retour\n5 - Quitter\nChoix : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &choix) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}
	
	switch(choix)
	{
	case 1:
		if(fork()==0){
			execlp("gedit", "gedit", "../Config/config.txt", NULL);
		}
		configuration();
		break;

	case 2: if(fork()==0){
			execlp("gedit", "gedit", "../Config/config_texte.txt", NULL);
		}
		configuration();
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


/** Fonction proposant les différentes options 
*   auxquelles l'administrateur peut accéder
*/
void choix_adm(){

	int choix;
	char saisie[255];
	//contrôle de saisie
	while(1)
	{
		printf("\n\nSélectionner une action :\n1 - Lancer une recherche\n2 - Accéder aux descripteurs\n3 - Lancer une indexation\n4 - Modifier les configurations\n5 - Retour\n6 - Quitter\nChoix : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &choix) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}

	switch(choix)
	{

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
