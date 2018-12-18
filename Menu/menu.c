#include <stdio.h>
#include <stdlib.h>
#include"menu1.c"
#include"menu2.c"
#include"menu3.c"
//#include"menu5.c"

int main(void){
	int mode = menu1();
	//printf("Valeur du mode : %d\n",mode);
	//printf("Il reste à régler le cas où l'utilisateur ne rentre pas un chiffre mais une chaîne de caractères.\n");
	if(mode==1){
		int type=menu2();
		switch(type){
			case 1:
				menu3();
				break;
			case 2: 
				break;
			case 3:
				break;
			case 4: 
				break;
			default: 
				break;
		}
	}
	else if(mode==2){
		system("stty -echo; read -p \"Mot de passe : \" password; stty echo; echo $password");

	}
	

	

	
		
			
	return 0;

}
