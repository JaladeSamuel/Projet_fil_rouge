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

	BASE_DESCRIPTEUR_IMAGE_NB = "../IndexationImage/data/base_descripteur_imageNB.txt\0";
	BASE_DESCRIPTEUR_IMAGE_RGB = "../IndexationImage/data/base_descripteur_imageRGB.txt\0";
	BASE_EPHEMERE_NB = "../IndexationImage/data/baseEphemereNB.txt\0";
	BASE_EPHEMERE_RGB = "../IndexationImage/data/baseEphemereRGB.txt\0";
	LISTE_EPHEMERE_NB = "../IndexationImage/data/listeEphemereNB.txt\0";
	LISTE_EPHEMERE_RGB = "../IndexationImage/data/listeEphemereRGB.txt\0";
	TEST_NB_DIR_PATH = "../IMG_et_AUDIO/TEST_NB/\0";
	TEST_RGB_DIR_PATH = "../IMG_et_AUDIO/TEST_RGB/\0";
	LISTE_DESCRIPTEUR_IMAGE_NB = "../IndexationImage/data/liste_descripteur_imageNB.txt\0";
	LISTE_DESCRIPTEUR_IMAGE_RGB = "../IndexationImage/data/liste_descripteur_imageRGB.txt\0";
	DEPOT_IMAGE_A_COMPARER = "../IndexationImage/data/depot_image_a_compararer/\0";

	printf("%s\n",BASE_DESCRIPTEUR_IMAGE_NB);

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
