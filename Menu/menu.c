#include <stdio.h>
#include <stdlib.h>
#include"menu1.c"
#include"menu2.c"
#include"menu3.c"
#include"menu4.c"
#include"menu5.c"
#include "../IndexationTexte/indexationV1.h"

int main(void){
	indexationBaseTexte();
	menu1();

	return 0;
}
