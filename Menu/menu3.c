#include"menu3.h"
#include"menu2.h"
#include"menu1.h"

void motcle(){
	char mot;
	printf("\nRentrer le mot clé :\nMot clé : ");
	scanf("%s",mot);
}

void menu3(){
	int R_par=0;
	char saisie[255];
	
	while(1)
	{
		printf("\nRecherche par :\n1 - Mot clé\n2 - Fichier\n3 - Retour\nType de Recherche : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &R_par) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}

	switch(R_par){
	case 1 :
		motcle();
		break;
	case 2 :
		test_adresse();
		break;
	case 3 :
		menu2();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\" ou \"3\"\n");
		menu3();
		break;
	}
}



