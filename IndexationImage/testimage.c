#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"


int main(void) {
  printf("Hello World\n");

  BASE_DESCRIPTEUR_IMAGE_NB = "./data/base_descripteur_imageNB.txt";
  BASE_DESCRIPTEUR_IMAGE_RGB = "./data/base_descripteur_imageRGB.txt";
  BASE_EPHEMERE_NB = "./data/baseEphemereNB.txt";
  BASE_EPHEMERE_RGB = "./data/baseEphemereRGB.txt";
  LISTE_EPHEMERE_NB = "./data/listeEphemereNB.txt";
  LISTE_EPHEMERE_RGB = "./data/listeEphemereRGB.txt";
  TEST_NB_DIR_PATH = "./../IMG_et_AUDIO/TEST_NB/";
  TEST_RGB_DIR_PATH = "./../IMG_et_AUDIO/TEST_RGB/";
  LISTE_DESCRIPTEUR_IMAGE_NB = "./data/liste_descripteur_imageNB.txt";
  LISTE_DESCRIPTEUR_IMAGE_RGB = "./data/liste_descripteur_imageRGB.txt";
  DEPOT_IMAGE_A_COMPARER = "./data/depot_image_a_compararer/";
  
  //descripteurNB();
  
  //descripteurRGB();
 
  
  comparerImageAvecImageNB();
  //comparerImageAvecImageRGB();

  
  printf("\nGoodbye World\n");
  return 0;
}
