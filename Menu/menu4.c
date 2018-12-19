#include"menu2.h"
#include"menu4.h"
#include"menu3.h"
#include<stdlib.h>

void nb_dom(){
	int dom;
	printf("\nChoisir une couleur :\n1 - Noir\n2 - Blanc\n3 - Retour\nCouleur : ");
	scanf("%d",&dom);
	
	switch(dom){
	case 1 :
	case 2 :
		printf("\nEn travaux...\n");
		break;
	case 3 : 
		noir_blanc();
		break;
	default : 
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\" ou \"2\".\n");
		nb_dom();
		break;
	}
}

void noir_blanc(){	
	int nblc;
	printf("\n1 - Noir/Blanc dominant\n2 - Fichier\n3 - Retour\nType de recherche : ");
	scanf("%d",&nblc);


	switch(nblc){
	case 1 :
		nb_dom();
		break;
	case 2 :
		adresse();
		break;
	case 3 :
		Recherche_image();
		break;
	default : 
		break;
	}
}

void R_couleur(){
	int cl;
	printf("\n1 - Couleur dominante\n2 - Fichier\n3 - Retour\nType de recherche :");
	scanf("%d",&cl);
	
	switch(cl){
	case 1 : 
		couleur_dom();
		break;
	case 2 :
		adresse();
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


void couleur_dom(){	
	int couleur;
	printf("\nChoisir une couleur : \n1 - Rouge\n2 - Rose\n3 - Violet\n4 - Bleu\n5 - Vert\n6 - Jaune\n7 - Orange\n8 - Noir\n9 - Blanc\n10 - Retour\nCouleur : ");
	scanf("%d",&couleur);
	
	switch(couleur){
	case 1 :
	case 2 :
	case 3 : 
	case 4 : 
	case 5 : 
	case 6 :
	case 7 : 
	case 8 :
	case 9 :
		printf("\nEn travaux...\n");
		break;
	case 10 :
		R_couleur();
		break;
	default :
		printf("Erreur : Saisie impossible, veuillez choisir un entier entre \"1\" et \"8\".");
		couleur_dom();
		break;
	}
	
}




void Recherche_image(){
	int R_image;
	printf("\nSélectionner un type d'image :\n1 - Noir et Blanc\n2 - Couleur\n3 - Retour\nType de recherche : ");
	scanf("%d",& R_image);

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
	




