
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
void reinit(File *file);


typedef struct CheminDescripteur CheminDescripteur;
struct CheminDescripteur
{
    char* chemin;
    int id;
    CheminDescripteur *suivant;
};

typedef struct FileChemin FileChemin;
struct FileChemin
{
    CheminDescripteur *premier;
};

void INIT_FILE_TABLE_INDEX(FileChemin *file);
void ENFILER_CHEMIN(FileChemin *file, char* chemin, int id);
int fileContainsChemin(FileChemin *file, char *chemin);
void AFFICHER_FILE_TABLE_INDEX(FileChemin *file);
