#include "../../Commun/Descripteurs_Textes/descripteur.h"

// TODO : lire la valeur dans le fichier de configs
#define SIZE_RESULTS_MAX 10

#ifndef COMPARAISONTXT_H
#define COMPARAISONTXT_H

typedef struct RESULTS_tag
{
    int size;
    int ids[SIZE_RESULTS_MAX];
    float percentages[SIZE_RESULTS_MAX];

} RESULTS;

char* FILE_DESCRIPTORS_PATH;
char* FILE_TEXT_CONFIG_PATH;
char* FILE_DESCRIPTORS_INDEX;
char* DATA_BASE_PATH;

void tolower_STR(char* word);

void init_RES(RESULTS* res);
void add_RES(RESULTS* res, int id, float pourcentage);
void print_RES(RESULTS res);
void getPathFromId_RES(RESULTS* res, char* path);

void init_COMPTXT();
float compare_COMPTXT(DESCR base, DESCR descriptor);
void searchWord_COMPTXT(char mot[WORD_LENGTH_MAX], RESULTS* res);
void searchFILE_COMPTXT(char file[400], RESULTS* res);
void search_COMPTXT(DESCR base, RESULTS* res);

#endif