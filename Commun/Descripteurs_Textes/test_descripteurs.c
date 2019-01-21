#include <stdio.h>
#include "descripteur.h"

int main()
{
    int i;

    printf(" - Initialisation d'une structure descripteur.\n");
    DESCR descripteur;
    init_DESCR(&descripteur, 4);

    printf(" - Lecture du fichier de test et remplissage du descripteur.\n");
    FILE* file;
    file = fopen("../descripteur_base_texte.txt", "r");

    if (file == NULL)
    {
        printf("Impossible de lire le fichier.\n");
        return -1;
    }

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

    close_DESCR(&descripteur);
    printf("\n - Fin des tests.\n");
    return 0;
}