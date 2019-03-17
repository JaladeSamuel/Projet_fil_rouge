/*
** indexationV1.h
** Samuel Jalade
** Contient les variable globale ainsi que les chemin vers
** les fichier utilies pour l indexation de fichier texte
*/

#ifndef INDEXATIONTXT_H
#define INDEXATIONTXT_H

#include "fileMot.h"
#include "../Commun/Descripteurs_Textes/descripteur.h"

#define PATH_BD "../noyau_c/Base_de_donnees/TEXTES/" //chemin vers la repertoire des fichiers textes
#define PATH_DESCRIPTEUR "../noyau_c/Commun/descripteur_base_texte.txt" //chemin vers le fichier qui stock les descripteurs texte

int nb_termes_max;
int lg_mini_mots;

/*
**Ajoute les mots du fichier texte dans une file, si le mot est deja existant dans la file
**le compteur du mot est incremente.
*/
void fileMotFichier(File *file, char *nomFichier, int dansBase);
/*
**Prend une file de mot A et enfile dans une seconde File B les mots les plus frequent de A.
*/
void fileMotFrequent(File *fileDeMot, File *fileMotFrequent);
/*
**Parcours toute la base est indexa chaque fichier a la vole
*/
int indexationBaseTexte();
/*
**fonction non qui permet d actualiser la table de chemin et d ID des descripteurs indexes
*/
void actualiserTableTexteIndex(FileChemin *file);
/*
**Indexe un fichier unique et rempli la structure descripeur pour decrire le fichier
*/
int indexationFichierTexte(char *cheminFichier, DESCR *descripteur);
/*
**Prend une file de mot A et enfile dans un DESCR (pour la comparaison) B les mots les plus frequent de A.
*/
void fileMotFrequentDansDESCR(File *fileDeMot, DESCR *fileMotFrequent);
/*
**Charge les variable par le fichier de configuration config_texte.txt
*/
void load_config_texte();
/*
**permet d ajouter des fichiers xml a la base de donnee et indexe a nouveau la base pour actualiser
*/
void ajoutDocBase(char *path);

#endif
