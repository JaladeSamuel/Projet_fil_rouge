#include "fileMot.h"
#include "IndexationTexte.h"
#define PATH_BD "../Base_de_donnees/TEXTES/" //chemin vers la repertoire des fichiers textes
#define PATH_DESCRIPTEUR "../Commun/descripteur_base_texte.txt" //chemin vers le fichier qui stock les descripteurs texte
void fileMotFichier(File *file, char *nomFichier);
void fileMotFrequent(File *fileDeMot, File *fileMotFrequent);
int indexationBaseTexte();
