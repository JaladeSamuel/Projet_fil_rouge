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
  int nb_lignes;
  int nb_colonnes;
  int** image;
  int histogramme[4];/*Tableau de 4 pour aller de 0 à 3*/
  char id[150];/*Id est un moyen de la reconnaitre parmi les autres*/
}*imageNB;

//Pile dynamique
typedef struct Cell{
  struct Cell* suivant;
  int valeur;
  char id[150];
}Cell;
 
typedef struct{
  Cell* premier;
}PILE;

//MODULE POUR LA QUANRIFICATION
int quantificationNoirBlanc(int nombre);

int quantificationRGB(int nombreR,int nombreG,int nombreB);

void histogrammeRGB(image m);

void histogrammeNB(imageNB m);

image creation_imageRGB(int nb_lignes ,int nb_colonnes);

imageNB creation_imageNB(int nb_lignes ,int nb_colonnes);

void affiche_imageNB(imageNB m);

imageNB copieNB(int numeroFichier);

image copieRGB(int numeroFichier);

void constructeurNB(imageNB imageTMP);

void constructeurRGB(image imageTMP);

void descripteurNB();

void descripteurRGB();

//Comparaison
int comparaisonNB(imageNB des1,imageNB des2);
int comparaisonRGB(image des1,image des2);

void comparerImageAvecImageNB();
void comparerImageAvecImageRGB();

//Module Pile
PILE init_PILE();
int PILE_estVide(PILE pile);
void ParcoursPILE(PILE pile);
int taillePILE(PILE pile);
PILE emPILE(PILE pile,int val,char * id);
#endif


