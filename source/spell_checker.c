<<<<<<< HEAD
#include "spell_checker_func.h"
=======
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NWORDS_TEXT 141
#define DICTIONARY_LEN 320139
#define MAX_INPUT 281

char **getDictionary(char[]);

char **getTextFromFile(char[], int*);

char **getWordsFromLine(char[], int*);

void freeArray (char **, int);

char **check_words(char **, int, char **);

int find_word(char [], char**);

int binarySearch(char**, int, int, char *);

int compare_words(char[], char[]);
>>>>>>> 762584d1c94fbb823ca7cc0e31e18b9d07701342

int main(int argc, char argv[]){
    char **dictionary = getDictionary("palavras.txt");
    char **userText = NULL;
    int numberOfWords = 0;

    printf("Olá, seja bem vindo ao spell-checker!\n");
    printf("Digite o nome do arquivo que deverá ser corrigido\n");
    printf("Ou digite 'T' e ENTER para digitar o texto no terminal.\n");
    printf("> ");

    char input[MAX_INPUT];
    fgets(input, MAX_INPUT, stdin);

    if (strlen(input) == 2 && input[0] == 'T') {
        printf("> ");
        fgets(input, MAX_INPUT, stdin);

        userText = getWordsFromLine(input, &numberOfWords);
    } else {
        input[strlen(input) - 1] = '\0';
        userText = getTextFromFile(input, &numberOfWords);
    }

    char **wrongWords = check_words(userText, numberOfWords, dictionary);

    int i = -1;
    while (wrongWords[++i]) {
        // printf("A palavra Numca pode estar escrita incorretamente, as opções de substituição são:\n");
        printf("Errada: %s\n", wrongWords[i]);
    }

    freeArray(dictionary, DICTIONARY_LEN);
    freeArray(userText, numberOfWords);

    return 0;
}
