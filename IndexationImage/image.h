#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct etImage{//Image RGB
  int nb_lignes;
  int nb_colonnes;
  int** imageR;
  int** imageG;
  int** imageB;
  int** image;
  int histogramme[64];
  char id[150];
}*image;


typedef struct etImageNB{ //Image NB
  int nb_lignes;
  int nb_colonnes;
  int** image;
  int histogramme[4];
  char id[150];
}*imageNB;

//MODULE POUR LA QUANRIFICATION
int quantificationNoirBlanc(int nombre);

int quantificationRGB(int nombreR,int nombreG,int nombreB);

void histogrammeRGB(image m);

void histogrammeNB(imageNB m);

//TEST

image creation_imageRGB(int nb_lignes ,int nb_colonnes);

imageNB creation_imageNB(int nb_lignes ,int nb_colonnes);

void affiche_imageNB(imageNB m);

imageNB copieNB(int numeroFichier);

image copieRGB(int numeroFichier);

void constructeurNB(imageNB imageTMP);

void constructeurRGB(image imageTMP);

void descripteurNB();

void descripteurRGB();

#endif


