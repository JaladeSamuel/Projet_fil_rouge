#ifndef H_FILE
#define H_FILE
#include "element.h"
typedef struct Cellule Cellule;
struct Cellule
{
    char[20] mot;
    Cellule *suivant;
};

typedef struct File File;
struct File
{
    Cellule *premier;
};

void INIT_FILE(File *file);
void ENFILER(File *file, char *mot);
int DEFILER(File *file);
void AFFICHER_FILE(File *file);


#endif
