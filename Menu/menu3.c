#include"menu3.h"
#include"menu2.h"
#include"menu1.h"
#include "../Comparaison/Comparaison_Texte/comparaison.h"

/** Demande et contrôle sur la saisie du mot-clé
*/
void motcle(){
	char mot[30];
	printf("\nRentrer le mot clé :\nMot clé : ");
	scanf("%s", mot);
	//contrôle sur la taille de la chaine de caractères
	while (strlen(mot) < 3)
	{
		printf("Vous devez entrez un mot clé qui a 3 ou plus caractères : ");
		scanf("%s", mot);
	}	

	RESULTS res;
	init_RES(&res);

	searchWord_COMPTXT(mot, &res);
	print_RES(res);
}

/** Choix du mode de recherche d'un fichier texte
*/
void menu3(){
	int R_par=0;
	char saisie[255];
	//contrôle sur la saisie
	while(1)
	{
		printf("\nRecherche par :\n1 - Mot clé\n2 - Fichier\n3 - Retour\n4 - Quitter\nType de Recherche : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &R_par) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}

	switch(R_par){
	case 1 :
		motcle();
		break;
	case 2 :
		rechercheParAdresse();
		break;
	case 3 :
		menu2();
		break;
	case 4 : 
		quitter();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\",\"3\" ou \"4\"\n");
		menu3();
		break;
	}
}



