#include <stdio.h>
#include <stdlib.h>
#include "menu1.c"
#include "menu2.c"
#include "menu3.c"
#include "menu4.c"
#include "menu5.c"
#include "../IndexationTexte/indexationV1.h"
#include "../IndexationImage/image.h"

int main(void){
	indexationBaseTexte();

	descripteurNB();
	descripteurRGB();

	FILE_DESCRIPTORS_PATH = "../Commun/descripteur_base_texte.txt\0";
	FILE_TEXT_CONFIG_PATH = "../Config/config_texte.txt\0";
    FILE_DESCRIPTORS_INDEX = "../Commun/tableTexteIndex.txt\0";
    DATA_BASE_PATH = "../Base_de_donnees/TEXTES/\0";
	init_COMPTXT();

	printf("\n\n\n");
	system("echo  \"\033[36;1mFoxIt vous souhaite la bienvenue sur son nouveau moteur de recherche !\033[0m\"");
	menu1();

	return 0;
}
