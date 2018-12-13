#include <stdio.h>
#include"menu1.c"
#include"menu2.c"

int main(void){
	int mode = menu1();
	printf("Valeur du mode : %d\n",mode);
	printf("Il reste à régler le cas où l'utilisateur ne rentre pas un chiffre mais une chaîne de caractères.\n");
	if(mode==1){
		menu2();
	}
	return 0;

}
