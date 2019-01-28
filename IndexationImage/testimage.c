#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"


int main(void) {
  printf("Hello World\n");

  descripteurNB();
  
  descripteurRGB();
 
  
  //comparerImageAvecImageNB();
  //comparerImageAvecImageRGB();

  //printf("Recherche par niveau de noir et blanc :\n");
  //rechercherNiveauGris(1);

  printf("Recherche par couleur :\n");
  rechercheParCouleur(8);

  printf("\nGoodbye World\n");
  return 0;
}
