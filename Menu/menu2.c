# include <stdio.h>

int menu2(){
	printf("\nSélectionner le type de fichier recherché :\n1 - Texte\n2 - Image\n3 - Son\n4 - Retour\nType de fichier : ");
	int type = 0;
	scanf("%d",&type);
	while(type!=1&&type!=2&&type!=3&&type!=4){
		printf("\nErreur : Saisie impossible, veuillez choisir '1','2','3' ou '4'.\n");
		printf("\nSélectionner le type de fichier recherché :\n1 - Texte\n2 - Image\n3 - Son\n4 - Retour\nType de fichier : ");
		scanf("%d",&type);
	}
	return type;
}

