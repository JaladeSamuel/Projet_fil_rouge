# include <stdio.h>
# include "menu2.h"

void identification(){
	system("stty -echo; read -p \"\nMot de passe : \" password; stty echo; if [ $password == \"123upssitech\" ] ;then echo \"\nMot de passe accepté !\";else echo \"\nMot de passe refusé ! Réessayez.\n\";fi;");
	
}

void menu1(){
	int mode=0;
	printf("\nSélectionner un mode : \n1 - Utilisateur\n2 - Administrateur\nType de connexion : ");
	scanf("%d", &mode);

	switch(mode){	
	case 1 :
		menu2();
		break;
	case 2 :
		identification();
		break;
	default : 
		printf("\nErreur : Saisie impossible, veuillez choisir \"1\" ou \"2\".\n");
		menu1();
		break;
	}
}


