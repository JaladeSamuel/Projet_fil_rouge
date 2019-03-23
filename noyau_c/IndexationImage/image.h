#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define NOMBRE_DE_RESULTAT 4 //nombre de résultat renvoyé par la comparaison d'image
typedef struct etImage{//Image RGB
  /*
  Structure pour une image RGB, qui contient les infos sur l'image
  Nous avons le nombre de ligne et de colonne de l'image. 
  3 tableaux à deux dimensions contenant les valeurs quantifiés des composantes RGB
  Un histogramme pour aller de 0 à 63
  L'id est le nom de l'image 
  */
  int nb_lignes;
  int nb_colonnes;
  int** imageR;
  int** imageG;
  int** imageB;
  int** image;
  int histogramme[64];
  char id[150];/*Id est un moyen de la reconnaitre parmi les autres*/
}*image;


typedef struct etImageNB{ //Image NB
  /*
  Structure pour une image RGB, qui contient les infos sur l'image
  Nous avons le nombre de ligne et de colonne de l'image. 
  Un tableaux à deux dimensions contenant les valeurs quantifiés du niveau de gris
  Un histogramme pour aller de 0 à 3
  L'id est le nom de l'image 
  */
  int nb_lignes;
  int nb_colonnes;
  int** image;
  int histogramme[4];/*Tableau de 4 pour aller de 0 à 3*/
  char id[150];/*Id est un moyen de la reconnaitre parmi les autres*/
}*imageNB;

//Pile dynamique
typedef struct Cell{
  /*
  Structure cellule utilisé pour la comparaison. 
  Une cellule contient le suivant qui est un pointeur vers la cellule suivante
  L'id correspond au nom du fichier et la valeur correspond au score enregistré après une comparaison
  */
  struct Cell* suivant;
  int valeur;
  char id[150];
}Cell;

typedef struct{
  /*
  C'est la pile dynamique. La structure Cell est définit au dessus
  La variable premier contient un pointeur vers le premier élément de la pile
  */
  Cell* premier;
}PILE;

typedef struct PAIRE_tag
{
  int size;
  char ids[NOMBRE_DE_RESULTAT][150];
  float valeurs[NOMBRE_DE_RESULTAT];
} PAIRE;

//MODULE POUR LA QUANRIFICATION

int quantificationNoirBlanc(int nombre);
/* 
  Cette fonction va prendre en entrée un entier et retourner un entier qui sert entre 0 et 3.
  Elle sert à faire la quantification des images noir et blanc pour l'indexation.
  */

int quantificationRGB(int nombreR,int nombreG,int nombreB);
/* 
  Cette fonction va prendre en entrée un entier et retourner un entier qui sert entre 0 et 63.
  Elle sert à faire la quantification des images en couleur pour l'indexation.
  */

void histogrammeRGB(image m);
/*
  Cette fonction prend en entrée une image rouge vert bleu et elle va modifier l'image grâce au pointeurs.
  Elle ne renvoie donc rien du tout (void). 
  Son rôle de réaliser l'histogramme de l'image donnée en paramètre.
  */

void histogrammeNB(imageNB m);
/*
  Cette fonction prend en entrée une image noir et blanche et elle va modifier l'image grâce au pointeurs.
  Elle ne renvoie donc rien du tout (void). 
  Son rôle de réaliser l'histogramme de l'image donnée en paramètre.
  */

image creation_imageRGB(int nb_lignes ,int nb_colonnes);
/*
  Cette fonction sert à créer une image coloré. Elle prend en entrée le nombre de ligne et de colonne
  Elle renvoie une image qui sera créer. L'image au ses composantes concernant les couleurs initilisé à 0. 
  */

imageNB creation_imageNB(int nb_lignes ,int nb_colonnes);
/*
  Cette fonction sert à créer une image noire et blanche. Elle prend en entrée le nombre de ligne et de colonne
  Elle renvoie une image qui sera créer. L'image au ses composantes concernant les couleurs initilisé à 0. 
  */

void affiche_imageRGB(image m);
/*
  Le rôle de cette fonction est d'affiché une image rouge vert bleu.
  Elle prend en entrée cette image et ne renvoie rien. 
  Elle est utlisé uniquement pour nos tests et pour éventuellement améliorer le code.
  */

void affiche_imageNB(imageNB m);
/*
  Le rôle de cette fonction est d'affiché une image noir et blanche.
  Elle prend en entrée cette image et ne renvoie rien. 
  Elle est utlisé uniquement pour nos tests et pour éventuellement améliorer le code.
  */

imageNB copieNB(int numeroFichier);
/*
  La fonction va prendre en entrée un numéro de fichier et elle va créer et renvoyé une image noir et blance qui est la copie de l'image identifié avec le numéro
  Cette fonction sert uniquement à faire des tests, elle n'est pas utilisé. 
  Nous l'avons laissé pour faire des tests et des éventuelle amélioration dans le futur. 
  */

image copieRGB(int numeroFichier);
/*
  La fonction va prendre en entrée un numéro de fichier et elle va créer et renvoyé une image couleur qui est la copie de l'image identifié avec le numéro
  Cette fonction sert uniquement à faire des tests, elle n'est pas utilisé. 
  Nous l'avons laissé pour faire des tests et des éventuelle amélioration dans le futur. 
  */

void constructeurNB(imageNB imageTMP);
/*
  La fonction va prendre en entrée une image noir et blanche et elle ne renvoie rien
  Elle a pour objectif de créer le descripteur d'une image donnée en entrée
  Elle va ouvrir la base des descripteurs et ajouter le nom et l'histogramme de l'image
  */

void constructeurRGB(image imageTMP);
/*
  La fonction va prendre en entrée une image rouge verte et bleu et elle ne renvoie rien
  Elle a pour objectif de créer le descripteur d'une image donnée en entrée
  Elle va ouvrir la base des descripteurs et ajouter le nom et l'histogramme de l'image
  */

void descripteurNB();
/*
  C'est la fonction principale pour créer les descripteurs. Elle ne prend aucune entrée et ne renvoie rien.
  Elle est appelée par le menu pour parcourir les images de la base d'image, elle va ensuite remplir la base de descripteur.
  Cette fonction est utilisée pour les images noires et blanches.    
  */

void descripteurRGB();
/*
  C'est la fonction principale pour créer les descripteurs. Elle ne prend aucune entrée et ne renvoie rien.
  Elle est appelée par le menu pour parcourir les images de la base d'image, elle va ensuite remplir la base de descripteur.
  Cette fonction est utilisée pour les images colorée.    
  */

//Comparaison
int comparaisonNB(imageNB des1,imageNB des2);
/*
  Fonction qui sera appelé par les fonctions de comparaison. Elle va prendre en entrée 2 images.
  Elle va parcourir les deux images et calculer les différences entre les deux histogrammes. 
  Cela lui permettra de renvoyé un entier qui correspond à un score de ressemblance.
  Plus les images se ressemblent et plus le score et petit. Fonction pour les images noires et blanches. 
  */

int comparaisonRGB(image des1,image des2);
/*
  Fonction qui sera appelé par les fonctions de comparaison. Elle va prendre en entrée 2 images.
  Elle va parcourir les deux images et calculer les différences entre les deux histogrammes. 
  Cela lui permettra de renvoyé un entier qui correspond à un score de ressemblance.
  Plus les images se ressemblent et plus le score et petit. Fonction pour les images colorées.
  */

void comparerImageAvecImageNB();
void comparerImageAvecImageRGB();
void rechercherNiveauGris(int niveau);
void rechercherCouleur(int* tableau, int taille);
void rechercherCouleurStr(int* tableau, int taille, char* string);
void rechercheParCouleur(int couleur);
void rechercheParCouleurStr(int couleur, char* string);

void ouvrirFichier(char* fichier, char* localtionPath, char* extension);
int isValeurDansTableau(int valeur, int *tableau, int taille);

void initPaire(PAIRE* paire);
void ajouterParPaireIdValeur(PAIRE* pair, char* id, float valeur);
void getPaire(PAIRE * paire, char * paireStr);
void afficherPaire(PAIRE* paire);

//Module Pile
PILE init_PILE();
int PILE_estVide(PILE pile);
void ParcoursPILE(PILE pile);
int taillePILE(PILE pile);
PILE emPILE(PILE pile,int val,char * id);
#endif
