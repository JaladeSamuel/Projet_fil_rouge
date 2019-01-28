#include "comparaison.h"
#include "../../IndexationTexte/indexationV1.h"
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h> 

int DESCRIPTORS_MAX_ID = 0;

/** Permet de transformer toute les lettre d'un mot en minuscule donnée en paramètres.
 *  char* word : mot à mettre en minuscule
 */
void tolower_STR(char* word)
{
    for (int i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
}

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
            int i = 0;
            for (i = res->size; (i >= counter && i < SIZE_RESULTS_MAX); i--)
            {
                res->ids[i + 1] = res->ids[i];
                res->percentages[i + 1] = res->percentages[i];
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
    if (res.size == 0)
    {
        printf("Aucun resultat n'a été trouvé.\n");
        return;
    }

    for (int i = 0; i < res.size && i < SIZE_RESULTS_MAX; i++)
    {
        FILE* file;
        file = fopen(FILE_DESCRIPTORS_INDEX, "r");

        if (file == NULL)
        {
            printf("ERREUR : Impossible d'ouvrir le fichier d'index des descripteurs.");
            return;
        }

        printf(" - ");

        int id;
        char fileName[60];
        while (!feof(file))
        {
            fscanf(file, "%d %s", &id, fileName);

            if (id == res.ids[i])
            {
                printf("%s (%.0f%%)\n", fileName, res.percentages[i]);
            }
        }

        rewind(file);
    }
}

void openFirstResult_RES(RESULTS res)
{
    char path[150];

    if (res.size == 0)
    {
        strcpy(path, "NULL");
        return;
    }

    FILE* file;
    file = fopen(FILE_DESCRIPTORS_INDEX, "r");

    if (file == NULL)
    {
        printf("ERREUR : Impossible d'ouvrir le fichier d'index des descripteurs.");
        return;
    }

    int id;
    char fileName[60];
    while (!feof(file))
    {
        fscanf(file, "%d %s", &id, fileName);

        if (id == res.ids[0])
        {
            strcpy(path, "../Base_de_donnees/TEXTES/");
            strcat(path, fileName);
        }
    }

    fclose(file);

    if (!fork())
    {
        execlp("gedit", "gedit", path, NULL);
    }
}

/** Initialise la comparaison.
 */
void init_COMPTXT()
{
    FILE* file;
    file = fopen(FILE_TEXT_CONFIG_PATH, "r");

    if (file == NULL)
    {
        printf("ERREUR : Impossible d'ouvrir le fichier de configurations texte.\n");
    }
    else
    {
        // while (feof(file))
        // {
        //     fscanf("%s %d", );
        // }
        fclose(file);
    }

    file = fopen(FILE_DESCRIPTORS_PATH, "r");

    if (file == NULL)
    {
        printf("ERREUR : Impossible d'ouvrir le fichier des descripteurs.\n");
        return;
    }

    int id = 0, max = 0;
    while (!feof(file))
    {
        fscanf(file, "%d%*[^\n]", &id);

        if (max < id)
        {
            max = id;
        }
    }

    DESCRIPTORS_MAX_ID = max;
    fclose(file);
}

/** Compare deux descripteurs et renvoie la similarité en pourcentage, de 0% (complètement différents) à 100% (descripteurs identiques).
 *  DESCR base : descripteur de référence pour la comparaison
 *  DESCR descriptor : descripteur comparé à celui de référence
 */
float compare_COMPTXT(DESCR base, DESCR descriptor)
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

/** Recherche un mot dans la liste des descripteurs et retourne la liste ordonnée dans la structure RESULTS
 *  char mot[WORD_LENGTH_MAX] : le mot à chercher
 *  RESULTS* res : la structure RESULTS dans laquelle on sauvegarde le résultat de la recherche
 */
void searchWord_COMPTXT(char mot[WORD_LENGTH_MAX], RESULTS* res)
{
    DESCR searchDescr, tempDescr;
    init_DESCR(&searchDescr, -1);
    addWord_DESCR(&searchDescr, mot);
    searchDescr.nbTermes = 1;
    searchDescr.total = 1;

    search_COMPTXT(searchDescr, res);
}

/** Lance une recherche en comparant avec le nom du fichier donné
 *
 */
void searchFILE_COMPTXT(char filePath[400], RESULTS* res)
{
    FILE* file;

    char errorMessage[600];

    char fullFilePath[400];
    strcpy(fullFilePath, DATA_BASE_PATH);
    strcat(fullFilePath, filePath);
    file = fopen(fullFilePath, "r");

    if (file == NULL)
    {
        file = fopen(filePath, "r");
        if (file == NULL)
        {
            printf("Impossible de trouver ni le fichier '%s' ni le fichier '%s'.\n", fullFilePath, filePath);

            file = fopen(FILE_DESCRIPTORS_INDEX, "r");
            tolower_STR(filePath);

            int id;
            char fileName[100];
            char fileNameMinimized[100];
            char closestFileName[500];
            closestFileName[0] = '\0';

            while (!feof(file))
            {
                fscanf(file, "%d %s", &id, fileName);
                strcpy(fileNameMinimized, fileName);
                tolower_STR(fileNameMinimized);
                if (strstr(fileNameMinimized, filePath) != NULL)
                {
                    strcat(closestFileName, "'");
                    strcat(closestFileName, fileName);
                    strcat(closestFileName, "' ");
                }
            }

            if (strlen(closestFileName) > 0)
            {
                printf("Voulez-vous dire le(s) fichier(s) %s?\n", closestFileName);
            }

            fclose(file);
            return;
        }
        else
        {
            DESCR newDescriptor;
            init_DESCR(&newDescriptor, -1);

            indexationFichierTexte(filePath, &newDescriptor);
            
            search_COMPTXT(newDescriptor, res);
            return;
        }
        fclose(file);
    }

    file = fopen(FILE_DESCRIPTORS_INDEX, "r");
    if (file == NULL)
    {
        printf("ERREUR : Impossible d'ouvrir le fichier d'index des descripteurs.\n");
        return;
    }

    int id;
    char fileName[60];
    while (!feof(file))
    {
        fscanf(file, "%d %s", &id, fileName);

        if (strcmp(fileName, filePath) == 0)
        {
            DESCR descriptor;
            init_DESCR(&descriptor, id);
            fillWithPath_DESCR(&descriptor, FILE_DESCRIPTORS_PATH);
            search_COMPTXT(descriptor, res);
        }
    }

    fclose(file);
}

/** Lance une recherche par rapport au descripteur 'base' et renvoie la liste des résultats dans la structure RESULTATS 'res'.
 *  DESCR base : descripteur de référence pour la recherche.
 *  RESULTS* res : structure de resultats que l'on veut afficher
 */
void search_COMPTXT(DESCR base, RESULTS* res)
{
    FILE* file;
    int counter = 0;
    DESCR tempDescr;

    while (counter <= DESCRIPTORS_MAX_ID)
    {
        file = fopen(FILE_DESCRIPTORS_PATH, "r");

        if (file == NULL)
        {
            printf("ERREUR : Impossible d'ouvrir le fichier de descripteurs texte.\n");
            return;
        }

        init_DESCR(&tempDescr, counter);
        fill_DESCR(&tempDescr, file);

        float tempComp = compare_COMPTXT(base, tempDescr);
        if (tempComp > 0.0 && counter != base.id)
        {
            add_RES(res, tempDescr.id, tempComp);
        }

        close_DESCR(&tempDescr);

        counter++;
        fclose(file);
    }
}
