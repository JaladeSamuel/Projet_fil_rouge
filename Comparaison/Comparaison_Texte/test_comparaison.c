#include <stdio.h>
#include "comparaison.h"

int main()
{
    int i;
    float comparaison;

    initComparaison();

    printf(" - Initialisation de deux descripteurs.\n");
    DESCR descripteur1, descripteur2;
    init_DESCR(&descripteur1, 30);
    init_DESCR(&descripteur2, 32);

    printf(" - Lecture du fichier de test et remplissage du descripteur.\n");
    FILE* file;
    file = fopen("../../Commun/descripteur_base_texte.txt", "r");
    fill_DESCR(&descripteur1, file);
    fill_DESCR(&descripteur2, file);
    fclose(file);
    
    printf(" - Details du descripteur 1 :\n");
    printf("   - Id du descripteur : %d\n", descripteur1.id);
    printf("   - Nombre de termes du descripteur : %d\n", descripteur1.nbTermes);
    printf("   - Termes du descripteur : ");
    TERMES terme = descripteur1.termes;
    for (i = 0; i < descripteur1.nbTermes; i++)
    {
        printf("%s:%d ", terme->terme->word, terme->terme->occurence);
        terme = terme->termeSuivant;
    }

    printf("\n - Details du descripteur 2 :\n");
    printf("   - Id du descripteur : %d\n", descripteur2.id);
    printf("   - Nombre de termes du descripteur : %d\n", descripteur2.nbTermes);
    printf("   - Termes du descripteur : ");
    terme = descripteur2.termes;
    for (i = 0; i < descripteur2.nbTermes; i++)
    {
        printf("%s:%d ", terme->terme->word, terme->terme->occurence);
        terme = terme->termeSuivant;
    }

    comparaison = comparer(descripteur1, descripteur2);
    printf("\n - Comparaison des deux : %f %%", comparaison);

    printf("\n - Recherche du mot 'navigateur' : \n");
    RESULTS res;
    init_RES(&res);
    rechercherParMot("navigateur", &res);
    print_RES(res);

    printf(" - Fin des tests.\n");

    return 0;
}