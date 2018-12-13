#define WORDS_MAX 10
#define WORD_LENGTH_MAX 25

typedef struct tag_DESCR {
    // Tableau des mots -> a rendre dynamique peut etre ?
    int words[WORDS_MAX][WORD_LENGTH_MAX];
    // Indice du dernier mot
    int lastWordIndex;
} DESCR;

void ini_DESCR(DESCR* descriptor);