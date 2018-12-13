# include <stdio.h>

/*#include 

*/
void menu2(){
	printf("\nSélectionner le type de fichier recherché :\n1 - Texte\n2 - Image\n3 - Son\n4 - Retour\nType de fichier : ");
	int type = 0;
	scanf("%d",&type);
	while(type!=1||type!=2||type!=3||type!=4){
		printf("\nErreur : Saisie impossible, veuillez choisir '1','2','3' ou '4'.\n");
		menu2();
	}
}

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

int main(void){
	int mode = menu1();
	printf("valeur du mode : %d\n",mode);
}
