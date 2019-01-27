# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "menu5.h"
# include "menu2.h"
#include "../Comparaison/Comparaison_Texte/comparaison.h"
#include "../IndexationTexte/indexationV1.h"

/** Fonction qui permet d'arrêter le programme
*/
void quitter(){
	printf("\nFin du programme.\n");
	exit(EXIT_SUCCESS);

}

/** Fonction d'identification, le bon mot de passe doit être saisi.
*   pour cacher la saisie, on utilise les commandes unix
*/
void identification(){
	system("stty -echo; read -p \"\nMot de passe : \" password; stty echo; while [ \"$password\" != \"123upssitech\" ] >& fichier_erreur;do echo \"\nMot de passe refusé ! Réessayez.\n\";stty -echo; read -p \"\nMot de passe : \" password; stty echo; done; echo \"\nMot de passe accepté.\"");
}


/** Demande du mode d'utilisation
*/
void menu1(){
	int mode=0;
	char saisie[255];
	//contrôle sur la saisie
	while(1)
	{
		printf("\nSélectionner un mode : \n1 - Utilisateur\n2 - Administrateur\nType de connexion : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &mode) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}

	switch(mode)
	{
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


/* Fonction demandant une saisie d'adresse et 
*  vérifie si le fichier existe
*/
void test_adresse()
{
	system("read -p \"Lien du fichier : \" adresse; while [ ! -e \"$adresse\" ];do echo \"\nCe fichier n'existe pas, rentrez à nouveau l'adresse.\";read -p \"Lien du fichier : \" adresse;done");
}


void rechercheParAdresse(){
	char path[400];
	RESULTS res;
	init_RES(&res);

	printf("\nRentrer le nom du fichier present dans la base que vous voulez comparer ou un chemin absolu : ");
	scanf("%s", path);

	searchFILE_COMPTXT(path, &res);

	print_RES(res);
    openFirstResult_RES(res);
}

void nouveauFichierTexte()
{
	printf("\nRentrer le chemin absolu du fichier texte à indexer : ");
	char path[500];
	FILE *fichier = fopen("","r");
	while(fichier == NULL)
	{
		scanf("%s", path);
		fichier = fopen(path,"r");
		if(fichier == NULL)
		{
			printf("\nFichier introuvable veuillez réessayer : ");
		}
	}
	ajoutDocBase(path);
	printf("Fichier indexé et ajouté a la base\n");
}
