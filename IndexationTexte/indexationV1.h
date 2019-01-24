#include "fileMot.h"
#include "../Commun/Descripteurs_Textes/descripteur.h"
#define PATH_BD "../Base_de_donnees/TEXTES/" //chemin vers la repertoire des fichiers textes
#define PATH_DESCRIPTEUR "../Commun/descripteur_base_texte.txt" //chemin vers le fichier qui stock les descripteurs texte

int nb_termes_max;
int lg_mini_mots;

void fileMotFichier(File *file, char *nomFichier, int dansBase);
void fileMotFrequent(File *fileDeMot, File *fileMotFrequent);
int indexationBaseTexte();
int tableTexteIndexEstVide();
void actualiserTableTexteIndex(FileChemin *file);
int indexationFichierTexte(char *cheminFichier, DESCR *descripteur);
void fileMotFrequentDansDESCR(File *fileDeMot, DESCR *fileMotFrequent);
void load_config_texte();
