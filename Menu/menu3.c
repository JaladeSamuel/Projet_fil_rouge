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
	printf("\nRecherche par :\n1 - Mot clé\n2 - Fichier\n3 - Retour\n4 - Quitter\nType de Recherche : ");
	scanf("%d", &R_par);

	switch(R_par){
	case 1 :
		motcle();
		printf("En travaux...\n");
		break;
	case 2 :
		test_adresse();
		break;
	case 3 :
		menu2();
		break;
	case 4 : 
		Exit();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\" ou \"3\"\n");
		menu3();
		break;
	}
}



