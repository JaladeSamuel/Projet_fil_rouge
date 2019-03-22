#include "../Java_Headers/model_MoteurDeRecherche.h"
#include "../../IndexationTexte/indexationV1.h"
#include "../../Comparaison/Comparaison_Texte/comparaison.h"

void initComparaison()
{
	FILE_DESCRIPTORS_PATH = "../noyau_c/Commun/descripteur_base_texte.txt";
	FILE_TEXT_CONFIG_PATH = "../noyau_c/Config/config_texte.txt";
    FILE_DESCRIPTORS_INDEX = "../noyau_c/Commun/tableTexteIndex.txt";
    DATA_BASE_PATH = "../noyau_c/Base_de_donnees/TEXTES/";
    init_COMPTXT();
}

JNIEXPORT void JNICALL Java_model_MoteurDeRecherche_indexationTexte(JNIEnv * env, jclass class)
{
    indexationBaseTexte();
}

JNIEXPORT jstring JNICALL Java_model_MoteurDeRecherche_rechercheParMotCle(JNIEnv * env, jclass class, jstring motCle)
{
    RESULTS res;
    char resString[200];
    resString[0] = '\0';
    jstring result;
    initComparaison();

    char *mot = (*env)->GetStringUTFChars(env, motCle, NULL);
	init_RES(&res);

	searchWord_COMPTXT(mot, &res);
	toString_RES(res, resString);

    result = (*env)->NewStringUTF(env, resString);
    return result;
}

JNIEXPORT jstring JNICALL Java_model_MoteurDeRecherche_rechercheTexteParFichier(JNIEnv * env, jclass class, jstring chemin)
{
    RESULTS res;
    char resString[200];
    resString[0] = '\0';
    jstring result;
    initComparaison();

    char *path = (*env)->GetStringUTFChars(env, chemin, NULL);
	init_RES(&res);

	searchFILE_COMPTXT(path, &res);

	toString_RES(res, resString);

    result = (*env)->NewStringUTF(env, resString);
    return result;
}