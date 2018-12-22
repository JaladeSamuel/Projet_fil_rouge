#include <stdio.h>
#include "descripteur.h"

int main()
{
    int i;

    printf(" - Initialisation d'une structure descripteur.\n");
    DESCR descripteur;
    init_DESCR(&descripteur, 0);

    printf(" - Lecture du fichier de test et remplissage du descripteur.\n");
    FILE* file;
    file = fopen("../Test_Dev/descripteur_test.txt", "r");
    fseek(file, 34, SEEK_SET); // Avancement pour sauter les deux premieres lignes de commentaire
    fill_DESCR(&descripteur, file);
    fclose(file);

    printf(" - Details du descripteur :\n");
    printf("   - Id du descripteur : %d\n", descripteur.id);
    printf("   - Nombre de termes du descripteur : %d\n", descripteur.nbTermes);
    printf("   - Termes du descripteur : ");
    TERMES terme = descripteur.termes;
    for (i = 0; i < descripteur.nbTermes; i++)
    {
        printf("%s:%d ", terme->terme->word, terme->terme->occurence);
        terme = terme->termeSuivant;
    }

    printf("\n - Fin des tests.\n");
    return 0;
}