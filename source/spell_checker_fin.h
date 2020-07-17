#include "spell_checker.h"

char **check_words(char **userText, int numberOfWords, char **dictionary) {
    char userTextCopy[NWORDS_TEXT][MAXSTRING];

    for (int i = 0; i < numberOfWords; i++) {
        strcpy(userTextCopy[i], userText[i]);
    }
    // Inicializa o array de palavras
    char **words = NULL;

    // Aloca o tamanho máximo do array de palavras
    if (!(words = calloc(NWORDS_TEXT, sizeof(char[MAXSTRING])))) {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }

    for (int i = 0; i < numberOfWords; i++) {
        if (((int) userText[i][0]) == 0) {
            strcpy(userText[i], userTextCopy[i]);
        }
    }

    int currentWord = 0;
    int i;
    for (i = 0; i < numberOfWords; i++) {
        if (!(userText[i][0] > 32 && userText[i][0] < 65)) {
            if (userText[i][0] == '\0') continue;

            int result = find_word(userText[i], dictionary);

            if (!result) {
                words[currentWord++] = userText[i];
            }
        }
    }

    return words;
}

int find_word(char *word, char **dictionary)
{
    char *result;
    int i;
    int isAlreadyUpper = isupper(word[0]);
    word[0] = tolower(word[0]);

    for (i = 0; i < DICTIONARY_LEN; i++)
    {
        if (strcmp(word, dictionary[i]) == 0)
        {
            if (isAlreadyUpper) word[0] = toupper(word[0]);
            return 1;
        }
        
    }

    if (isAlreadyUpper) word[0] = toupper(word[0]);
    return 0;
}