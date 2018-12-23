#ifndef H_FILE
#define H_FILE

typedef struct Cellule Cellule;
struct Cellule
{
    char mot[50];
    int occurence;
    Cellule *suivant;
};

typedef struct File File;
struct File
{
    Cellule *premier;
    int nbMot;
    int occurencePlusGrande;
};

void INIT_FILE(File *file);
void ENFILER(File *file, char *mot);
int DEFILER(File *file, char *motDefile);
void AFFICHER_FILE(File *file);
int defilerPlusGrand(File *file, char *mot);
void ENFILER_FREQUENT(File *file, char *nvElement, int nbOccurence);
int estVide(File *file);



#endif
