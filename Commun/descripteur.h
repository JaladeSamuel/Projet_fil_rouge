#define WORDS_MAX 10
#define WORD_LENGTH_MAX 25

typedef struct tag_TERME {
    char word[WORD_LENGTH_MAX];
    int occurence;
} TERME;

typedef struct tag_DESCR {
    int id;
    // Tableau des mots -> a rendre dynamique ?
    TERME words[WORDS_MAX];
    // Indice du dernier mot
    int lastWordIndex;
} DESCR;

void init_DESCR(DESCR* descriptor, int id);
void fill_DESCR(DESCR descriptor, FILE* file);