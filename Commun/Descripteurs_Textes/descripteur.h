#include <stdio.h>

#define WORD_LENGTH_MAX 25

typedef struct tag_TERME
{
    char word[WORD_LENGTH_MAX];
    int occurence;
} TERME;

typedef struct tag_TERMES
{
    TERME* terme;
    struct tag_TERMES* termeSuivant;
} pileTERMES;

typedef pileTERMES* TERMES;

typedef struct tag_DESCR {
    int id;
    int nbTermes;
    int total;
    TERMES termes;
} DESCR;

void init_DESCR(DESCR* descriptor, int id);
void fill_DESCR(DESCR* descriptor, FILE* file);
void addWord_DESCR(DESCR* descriptor, char* word);
void addWordandOcc_DESCR(DESCR* descriptor, char* word, int occurence);
int getOccurence_DESCR(DESCR descriptor, char* word);
void removeWord_DESCR(DESCR* descriptor, TERME* terme);