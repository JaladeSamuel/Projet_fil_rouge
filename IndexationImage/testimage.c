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

  rechercherNiveauGris(1);
  rechercherCouleur(21);

  
  printf("\nGoodbye World\n");
  return 0;
}
