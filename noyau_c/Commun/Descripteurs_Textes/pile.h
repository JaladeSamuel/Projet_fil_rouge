#include "descripteur.h"

FILE *FILE_DESCRIPTORS

typedef struct tagCellule
{
    DESCR descriptor;
    struct tagCellule* prochaineCase;
} Cellule;

typedef Cellule* PILE;

PILE init_PILE();
void affiche_PILE(PILE pile);
int PILE_estVide(PILE pile);
PILE emPILE(PILE pile, ELEMENT valeur);
PILE dePILE(PILE pile, ELEMENT* valeur);
PILE saisir_PILE();