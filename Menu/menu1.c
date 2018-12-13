# include <stdio.h>

/*#include 

*/
int menu1(){
	int mode=0;
	printf("\nSélectionner un mode : \n1 - Utilisateur\n2 - Administrateur\nType de connexion : ");
	scanf("%d", &mode);
	while(mode!=1&&mode!=2){
		printf("\nErreur : Saisie impossible, veuillez choisir '1' ou '2'.\n");
		printf("\nSélectionner un mode : \n1 - Utilisateur\n2 - Administrateur\nType de connexion : ");
		scanf("%d", &mode);
	}
	return mode;
}
