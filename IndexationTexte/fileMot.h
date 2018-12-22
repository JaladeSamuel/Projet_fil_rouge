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
void DEFILER(File *file, char *motDefile);
void AFFICHER_FILE(File *file);
void defilerPlusGrand(File *file, char *mot);



#endif
