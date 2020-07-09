#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NWORDS_TEXT 141
#define DICTIONARY_LEN 320139
#define MAX_INPUT 281
#define MAX_DISTANCE 100
#define MAXSTRING 47

char **getDictionary(char[]);

char **getTextFromFile(char[], int*);

char **getWordsFromLine(char[], int*);

char **check_words(char **, int, char **);

int find_word(char [], char**);

int binarySearch(char**, int, int, char *);

int compare_words(char[], char[]);

void getSimilar(char[], char**, char*);

void changeWord(char[], char[], char**, int);
