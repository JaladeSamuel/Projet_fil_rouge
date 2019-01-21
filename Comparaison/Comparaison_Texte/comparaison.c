#include "comparaison.h"

int DESCRIPTORS_MAX_ID = 0;

/** Initialise la structure 'res' donnée en paramètres.
 *  RESULTS* res : structure de resultats qu'on initialise
 */
void init_RES(RESULTS* res)
{
    res->size = 0;
    for (int i = 0; i < SIZE_RESULTS_MAX; i++)
    {
        res->percentages[i] = -1;
    }
}

/** Ajoute un coupe 'id':'pourcentage' à la liste des resultats.
 *  RESULTS* res : structure de resultats dans laquelle on ajoute
 *  int id : id à ajouter
 *  float pourcentage : pourcentage à associer à l'id
 */
void add_RES(RESULTS* res, int id, float pourcentage)
{
    if (res->size == 0)
    {
        res->ids[0] = id;
        res->percentages[0] = pourcentage;
        res->size++;
    }
    else
    {
        int counter = 0;
        while (counter <= SIZE_RESULTS_MAX && res->percentages[counter] >= pourcentage && res->percentages[counter] != -1)
        {
            counter++;
        }

        if (counter != SIZE_RESULTS_MAX)
        {
            int idTemp = res->ids[counter];
            float pourcentageTemp = res->percentages[counter];

            for (int i = counter; i < res->size - counter; i++)
            {
                int idTemp = res->ids[i];
                float pourcentageTemp = res->percentages[i];

                res->ids[i + 1] = idTemp;
                res->percentages[i + 1] = pourcentageTemp;
            }

            res->ids[counter] = id;
            res->percentages[counter] = pourcentage;

            res->size++;
        }
    }
}

/** Affiche les résultats d'une structure RESULTS.
 *  RESULTS* res : structure de resultats que l'on veut afficher
 */
void print_RES(RESULTS res)
{
    for (int i = 0; i < res.size; i++)
    {
        printf(" - %d (%.0f%%)\n", res.ids[i], res.percentages[i]);
    }
}

void initComparaison()
{
    FILE* file;
    file = fopen(FILE_TEXT_CONFIG_PATH, "r");

    if (file == NULL)
    {
        printf("ERREUR : Impossible d'ouvrir le fichier de configurations texte.\n");
        return;
    }

    // TODO

    fclose(file);

    file = fopen(FILE_DESCRIPTORS_PATH, "r");

    if (file == NULL)
    {
        printf("ERREUR : Impossible d'ouvrir le fichier des descripteurs.\n");
        return;
    }

    int id = 0, total, max = 0;
    char line[500];
    while (fgets(line, 500, file) != NULL)
    {
        fscanf(file, "%d %d", &id, &total);

        if (max < id)
        {
            max = id;
        }
    }

    DESCRIPTORS_MAX_ID = max;
    fclose(file);
}

float comparer(DESCR base, DESCR descriptor)
{
    TERME* termeBase;
    int occTermeDescr;
    float calculBase, calculDescr;
    float sum = 0;
    float interSum = 0;

    for (int i = 0; i < base.nbTermes; i++)
    {
        termeBase = get_DESCR(base, i);
        occTermeDescr = getOccurence_DESCR(descriptor, termeBase->word);

        calculBase = ((float)termeBase->occurence * (float)termeBase->occurence) / (float)base.total;

        if (occTermeDescr == 0)
        {
            calculDescr = 0;
        }
        else
        {
            calculDescr = ((float)occTermeDescr * (float)occTermeDescr) / (float)descriptor.total;

            interSum = calculDescr / calculBase * 100.0;
            if (interSum > 100.0)
            {
                sum += 100.0;
            }
            else
            {
                sum += interSum;
            }
        }
    }

    return sum / (float)base.nbTermes;
}

void rechercherParMot(char mot[WORD_LENGTH_MAX], RESULTS* res)
{
    int counter = 0;

    DESCR searchDescr, tempDescr;
    init_DESCR(&searchDescr, -1);
    addWord_DESCR(&searchDescr, mot);
    searchDescr.nbTermes = 1;
    searchDescr.total = 1;

    FILE* file;
    while (counter <= DESCRIPTORS_MAX_ID)
    {
        file = fopen(FILE_DESCRIPTORS_PATH, "r");

        init_DESCR(&tempDescr, counter);
        fill_DESCR(&tempDescr, file);

        float tempComp = comparer(searchDescr, tempDescr);
        if (tempComp > 0.0)
        {
            add_RES(res, tempDescr.id, tempComp);
        }
        
        close_DESCR(&tempDescr);

        counter++;
        fclose(file);
    }
}

/** Lance une recherche par rapport au descripteur 'base' et renvoie la liste des résultats dans la structure RESULTATS 'res'.
 *  DESCR base : descripteur de référence pour la recherche.
 *  RESULTS* res : structure de resultats que l'on veut afficher
 */
void search_COMPTXT(DESCR base, RESULTS res)
{

}