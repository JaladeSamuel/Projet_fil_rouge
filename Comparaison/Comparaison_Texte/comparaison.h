/** Module de la comparaison texte.
 *  Ce module comprend une structure RESULTS qui permet de stocker et traiter les résultats d'un recherche.
 *  Aurélien Montmejat 
 */

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



/** Permet de transformer toute les lettre d'un mot en minuscule donnée en paramètres.
 *  char* word : mot à mettre en minuscule
 */
void tolower_STR(char* word);



/** Initialise la structure 'res' donnée en paramètres.
 *  RESULTS* res : structure de resultats qu'on initialise
 */
void init_RES(RESULTS* res);

/** Ajoute un coupe 'id':'pourcentage' à la liste des resultats.
 *  RESULTS* res : structure de resultats dans laquelle on ajoute
 *  int id : id à ajouter
 *  float pourcentage : pourcentage à associer à l'id
 */
void add_RES(RESULTS* res, int id, float pourcentage);

/** Affiche les résultats d'une structure RESULTS.
 *  RESULTS* res : structure de resultats que l'on veut afficher
 */
void print_RES(RESULTS res);

/** Ouvre le premier fichier des résultats donné en paramètre.
 *  RESULTS res : résultats à traiter
 */
void openFirstResult_RES(RESULTS res);



/** Compare deux descripteurs et renvoie la similarité en pourcentage, de 0% (complètement différents) à 100% (descripteurs identiques).
 *  DESCR base : descripteur de référence pour la comparaison
 *  DESCR descriptor : descripteur comparé à celui de référence
 */
void init_COMPTXT();

/** Recherche un mot dans la liste des descripteurs et retourne la liste ordonnée dans la structure RESULTS
 *  char mot[WORD_LENGTH_MAX] : le mot à chercher
 *  RESULTS* res : la structure RESULTS dans laquelle on sauvegarde le résultat de la recherche
 */
float compare_COMPTXT(DESCR base, DESCR descriptor);

/** Recherche un mot dans la liste des descripteurs et retourne la liste ordonnée dans la structure RESULTS
 *  char mot[WORD_LENGTH_MAX] : le mot à chercher
 *  RESULTS* res : la structure RESULTS dans laquelle on sauvegarde le résultat de la recherche
 */
void searchWord_COMPTXT(char mot[WORD_LENGTH_MAX], RESULTS* res);

/** Lance une recherche en comparant avec le nom du fichier donné.
 *  Vérifie l'exitante du fichier dans la base et en tant que chemin absolue.
 */
void searchFILE_COMPTXT(char file[400], RESULTS* res);

/** Lance une recherche par rapport au descripteur 'base' et renvoie la liste des résultats dans la structure RESULTATS 'res'.
 *  DESCR base : descripteur de référence pour la recherche.
 *  RESULTS* res : structure de resultats que l'on veut afficher
 */
void search_COMPTXT(DESCR base, RESULTS* res);

#endif