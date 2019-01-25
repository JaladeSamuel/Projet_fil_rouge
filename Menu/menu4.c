#include"menu2.h"
#include"menu4.h"
#include"menu1.h"
#include"menu3.h"
#include<stdlib.h>
#include "../IndexationImage/image.h"

/** Choix de la couleur dominante pour une image noir/blanc
*/
void nb_dom(){
	int dom;	
	char saisie[255];
	//contrôle sur la saisie
	while(1)
	{
		printf("\nQuelle est la couleur dominante de l'image ?\n1 - Noir\n2 - Blanc\n3 - Retour\n4 - Quitter\nCouleur : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &dom) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}
	
	switch(dom)
	{

	case 1 :
		rechercherNiveauGris(0);
		break;
	case 2 :
		rechercherNiveauGris(3);
		break;
	case 3 : 
		noir_blanc();
		break;
	case 4 : 
		quitter();
		break;
	default : 
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\" ou \"2\".\n");
		nb_dom();
		break;
	}
}


/** Choix du type de recherche pour une image noir/blanc
*   soit par fichier ou soir par couleur dominante
*/
void noir_blanc(){	
	int nblc;
	char saisie[255];
	//contrôle sur la saisie
	while(1)
	{
		printf("\nQuel type de recherche voulez-vous effectuer ?\n1 - Choix d'une couleur dominante\n2 - Recherche par fichier\n3 - Retour\n4 - Quitter\nType de recherche : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &nblc) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}

	switch(nblc)
	{

	case 1 :
		nb_dom();
		break;
	case 2 :
		comparaisonFichierNB();
		break;
	case 3 :
		Recherche_image();
		break;
	case 4 :
		quitter();
		break;
	default : 
		break;
	}
}


/** Choix du type de recherche pour une image noir/blanc
*   soit par fichier ou soir par couleur dominante
*/
void R_couleur(){
	int cl;
	char saisie[255];
	//contrôle sur la saisie
	while(1)
	{
		printf("\nQuel type de recherche voulez-vous effectuer ?\n1 - Choix d'une couleur dominante\n2 - Recherche par fichier\n3 - Retour\nType de recherche :");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &cl) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}

	switch(cl)
	{

	case 1 : 
		couleur_dom();
		break;
	case 2 :
		comparaisonFichierRGB();
		break;
	case 3 :
		Recherche_image();
		break;
	default :
		printf("Erreur : Saisie impossible, veuillez choisir \"1\",\"2\" ou \"3\".");
		R_couleur();
		break;
	}
}


/** Choix de la couleur dominante pour une image couleur
*/
void couleur_dom(){	
	int couleur;
	char saisie[255];
	//contrôle sur la saisie
	while(1)
	{
		printf("\nChoisir une couleur : \n1 - Rouge\n2 - Rose\n3 - Bleu\n4 - Vert\n5 - Jaune\n6 - Orange\n7 - Noir\n8 - Blanc\n9 - Retour\nCouleur : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &couleur) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}

	switch(couleur)
	{

	case 1 :
		rechercherCouleur(48);
		break;
	case 2 :
		rechercherCouleur(54);
		break;
	case 3 : 
		rechercherCouleur(3);
		break;
	case 4 : 
		rechercherCouleur(12);
		break;
	case 5 : 
		rechercherCouleur(60);
		break;
	case 6 :
		rechercherCouleur(52);
		break;
	case 7 : 
		rechercherCouleur(0);
		break;
	case 8 :
		rechercherCouleur(63);
		break;
	case 9 :
		R_couleur();
		break;
	default :
		printf("Erreur : Saisie impossible, veuillez choisir un entier entre \"1\" et \"8\".");
		couleur_dom();
		break;
	}
	
}



/** Fonction permettant de choisir à comparer une image couleur 
*   ou une image noir/blanc
*/
void Recherche_image(){
	int R_image;
	char saisie[255];
	//contrôle sur la saisie
	while(1)
	{
		printf("\nSélectionner un type d'image :\n1 - Noir et Blanc\n2 - Couleur\n3 - Retour\nType de recherche : ");
		fgets(saisie, 255, stdin);
		if (sscanf(saisie, "%d", &R_image) == 1) break;
		printf("\nErreur de saisie, veuillez saisir un entier.\n");
	}
	switch(R_image){
	case 1 :
		noir_blanc();
		break;
	case 2 :
		R_couleur();
		break;
	case 3 :
		menu2();
		break;
	default : 
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\",\"2\" ou \"3\".\n");
		Recherche_image();
		break;
	}
}

void comparaisonFichierRGB()
{
	comparerImageAvecImageRGB();
}

void comparaisonFichierNB()
{
	comparerImageAvecImageNB();
}
