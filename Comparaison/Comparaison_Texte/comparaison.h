#include "../../Commun/Descripteurs_Textes/descripteur.h"

// TODO : lire la valeur dans le fichier de configs
#define SIZE_RESULTS_MAX 10
#define FILE_DESCRIPTORS_PATH "../../Commun/descripteur_base_texte.txt"
#define FILE_TEXT_CONFIG_PATH "../../Config/config_texte.txt"

typedef struct RESULTS_tag
{
    int size;
    int ids[SIZE_RESULTS_MAX];
    float percentages[SIZE_RESULTS_MAX];

} RESULTS;

void init_RES(RESULTS* res);
void add_RES(RESULTS* res, int id, float pourcentage);
void print_RES(RESULTS res);

void initComparaison();
float comparer(DESCR base, DESCR descriptor);
void rechercherParMot(char mot[WORD_LENGTH_MAX], RESULTS* res);
void search_COMPTXT(DESCR base, RESULTS res);