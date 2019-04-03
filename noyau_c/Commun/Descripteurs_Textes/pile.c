#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

PILE init_PILE()
{
    return NULL;
}

void affiche_PILE(PILE pile)
{
    Cellule* prochaineCellule = pile;
    
    printf("[ ");

    if (!PILE_estVide(pile))
    {
        while (prochaineCellule != NULL)
        {
            affiche_ELEMENT(prochaineCellule->element);
            printf(" ");
            prochaineCellule = prochaineCellule->prochaineCase;
        }
    }

    printf(" ]");
}

int PILE_estVide(PILE pile)
{
    if (pile == NULL)
    {
        return 1;
    }
    
    return 0;
}

PILE emPILE(PILE pile, ELEMENT element)
{
    PILE pileRet;

    pileRet = malloc(sizeof(Cellule*));
    pileRet->element = element;
    pileRet->prochaineCase = pile;

    return pileRet;
}

PILE dePILE(PILE pile, ELEMENT* element)
{
    PILE pileRet;

    if (PILE_estVide(pile))
    {
        return pile;
    }
    
    *element = pile->element;
    pileRet = pile->prochaineCase;
    free(pile);

    return pileRet;
}

PILE saisir_PILE()
{
    int nombreElements, i;
    ELEMENT element;
    PILE pile = init_PILE();

    printf("Nombre d'element(s) a saisir : ");
    scanf("%d", &nombreElements);

    while (nombreElements < 0)
    {
        printf("Le nombre d'elements doit superieur a 0 : ");
        scanf("%d", &nombreElements);
    }

    for (i = 0; i < nombreElements; i++)
    {
        printf("[%d]: ", i);
        scanf("%f", &element);
        pile = emPILE(pile, element);
    }

    return pile;
}