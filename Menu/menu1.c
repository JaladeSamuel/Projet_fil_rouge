# include <stdio.h>
# include <string.h>
# include "menu5.h"
# include "menu2.h"
#include "../Comparaison/Comparaison_Texte/comparaison.h"

void quitter(){
	printf("\nFin du programme.\n");
	exit(EXIT_SUCCESS);

}

void identification(){
	system("stty -echo; read -p \"\nMot de passe : \" password; stty echo; while [ $password != \"123upssitech\" ] ;do echo \"\nMot de passe refusé ! Réessayez.\n\";stty -echo; read -p \"\nMot de passe : \" password; stty echo; done; echo \"\nMot de passe accepté.\"");

}


void menu1(){
	int mode=0;
	char saisie[255];

	while(1)
	{
		printf("\nSélectionner un mode : \n1 - Utilisateur\n2 - Administrateur\nType de connexion : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &mode) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}

	switch(mode){
	case 1 :
		menu2();
		break;
	case 2 :
		identification();
		choix_adm();
		break;
	default :
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\" ou \"2\".\n");
		menu1();
		break;
	}
}

void test_adresse()
{
	system("read -p \"Lien du fichier : \" adresse; while [ ! -e \"$adresse\" ];do echo \"\nCe fichier n'existe pas, rentrez à nouveau l'adresse.\";read -p \"Lien du fichier : \" adresse;done");
}

void rechercheParAdresse(){
	char path[400];
	RESULTS res;
	init_RES(&res);

	printf("\nRentrer le nom du fichier present dans la base que vous voules comparer ou un chemin absolu : ");
	scanf("%s", path);

	searchFILE_COMPTXT(path, &res);

	print_RES(res);
}
