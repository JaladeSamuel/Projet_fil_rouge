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

	BASE_DESCRIPTEUR_IMAGE_NB = "../IndexationImage/data/base_descripteur_imageNB.txt";
	BASE_DESCRIPTEUR_IMAGE_RGB = "../IndexationImage/data/base_descripteur_imageRGB.txt";
	BASE_EPHEMERE_NB = "../IndexationImage/data/baseEphemereNB.txt";
	BASE_EPHEMERE_RGB = "../IndexationImage/data/baseEphemereRGB.txt";
	LISTE_EPHEMERE_NB = "../IndexationImage/data/listeEphemereNB.txt";
	LISTE_EPHEMERE_RGB = "../IndexationImage/data/listeEphemereRGB.txt";
	TEST_NB_DIR_PATH = "../IMG_et_AUDIO/TEST_NB/";
	TEST_RGB_DIR_PATH = "../IMG_et_AUDIO/TEST_RGB/";
	LISTE_DESCRIPTEUR_IMAGE_NB = "../IndexationImage/data/liste_descripteur_imageNB.txt";
	LISTE_DESCRIPTEUR_IMAGE_RGB = "../IndexationImage/data/liste_descripteur_imageRGB.txt";
	DEPOT_IMAGE_A_COMPARER = "../IndexationImage/data/depot_image_a_compararer/";

	FILE_DESCRIPTORS_PATH = "../Commun/descripteur_base_texte.txt";
	FILE_TEXT_CONFIG_PATH = "../Config/config_texte.txt";
    FILE_DESCRIPTORS_INDEX = "../Commun/tableTexteIndex.txt";
    DATA_BASE_PATH = "../Base_de_donnees/TEXTES/";
	init_COMPTXT();

	printf("\n\n\n");
	system("echo  \"\033[36;1mFoxIt vous souhaite la bienvenue sur son nouveau moteur de recherche !\033[0m\"");
	menu1();

	return 0;
}
