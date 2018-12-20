#define WORDS_MAX 10
#define WORD_LENGTH_MAX 25

typedef struct tag_TERME {
    char word[WORD_LENGTH_MAX];
    int occurence;
} TERME;

typedef struct tag_DESCR {
    int id;
    int termes;
    int total;
    TERME words[WORDS_MAX];
} DESCR;

void init_DESCR(DESCR* descriptor, int id);
void fill_DESCR(DESCR descriptor, FILE* file);
void addWord_DESCR(DESCR descriptor, char* word);