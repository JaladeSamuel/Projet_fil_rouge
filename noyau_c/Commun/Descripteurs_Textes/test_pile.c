#include <stdio.h>
#include "pile_dynamique.h"

int main()
{
    PILE pile;
    ELEMENT element;
    affect_ELEMENT(&element, 4.34);
    
    pile = init_PILE();

    printf("Test ajout d'un element.\n");
    pile = emPILE(pile, element);
    affiche_PILE(pile);
    printf("\n");

    printf("Test ajout d'un deuxieme element.\n");
    affect_ELEMENT(&element, -2.342);
    pile = emPILE(pile, element);
    affiche_PILE(pile);
    printf("\n");

    printf("Test ajout d'un troisieme element.\n");
    affect_ELEMENT(&element, 7.3);
    pile = emPILE(pile, element);
    affiche_PILE(pile);
    printf("\n");

    printf("Suppression d'un element.\n");
    pile = dePILE(pile, &element);
    affiche_PILE(pile);
    printf("\nElement depile: ");
    affiche_ELEMENT(element);
    printf("\n\n");

    printf("Suppression de plusieurs elements.\n");
    pile = dePILE(pile, &element);
    pile = dePILE(pile, &element);
    pile = dePILE(pile, &element);
    affiche_PILE(pile);
    printf("\nDernier element depile: ");
    affiche_ELEMENT(element);
    printf("\n\n");

    printf("Test ajout d'un element.\n");
    affect_ELEMENT(&element, 6.667);
    pile = emPILE(pile, element);
    affiche_PILE(pile);
    printf("\n");

    printf("\nTest saisie.\n");
    pile = saisir_PILE();
    affiche_PILE(pile);
    printf("\n");

    return 0;
}