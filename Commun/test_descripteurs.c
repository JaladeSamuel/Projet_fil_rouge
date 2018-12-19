#include <stdio.h>
#include "descripteur.h"

int main()
{
    printf("Initialisation d'une structure descripteur.\n");
    DESCR descripteur;
    init_DESCR(&descripteur, 0);

    printf("Lecture du fichier de test et remplissage du descripteur.\n");
    FILE* file;
    file = fopen("Test_Dev/descripteur_test.txt", "r");
    /* Avancement pour sauter les deux premieres lignes de commentaire */
    fseek(file, 35, SEEK_SET);
    fill_DESCR(descripteur, file);
    fclose(file);

    printf("Fin des tests.\n");
    return 0;
}