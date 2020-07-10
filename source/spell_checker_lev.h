#include "spell_checker.h"

int subs[MAXSTRING][MAXSTRING];

int levenshtein(char a[], char b[]) {
  size_t lenA = strlen(a);
  size_t lenB = strlen(b);

  int vi[3] = {0, -1, -1};
  int vj[3] = {-1, -1, 0};

  for (int i = 0; i < lenA + 1; i++) {
    for (int j = 0; j < lenB + 1; j++) {
      if (i == 0) {
        subs[i][j] = j;
      } else {
        if (j == 0) subs[i][j] = i;
        else {
          int smallest = 1000;
          for (int z = 0; z < 3; z++) {
            int currentI = i + vi[z];
            int currentJ = j + vj[z];
            smallest = smallest < subs[currentI][currentJ] ? smallest : subs[currentI][currentJ];
          }
          if (a[i - 1] == b[j - 1]) subs[i][j] = subs[i - 1][j - 1];
          else subs[i][j] = smallest + 1;
        }
      }
    }
  }

  return subs[lenA][lenB];
}

void getSimilar(char word[], char **dictionary, char *similar) {
    char first[MAXSTRING];
    int firstDistance = MAX_DISTANCE;
    char second[MAXSTRING];
    int secondDistance = MAX_DISTANCE;
    char third[MAXSTRING];
    int thirdDistance = MAX_DISTANCE;

    int isAlreadyUpper = isupper(word[0]);

    for (int i = 0; i < DICTIONARY_LEN; i++) {
        int distance = levenshtein(dictionary[i], word); 

        if (distance < firstDistance) {
            strcpy(first, dictionary[i]);
            firstDistance = distance;
        } else if (distance < secondDistance) {
            strcpy(second, dictionary[i]);
            secondDistance = distance;
        } else if (distance < thirdDistance) {
            strcpy(third, dictionary[i]);
            thirdDistance = distance;
        }
    }

    if (isAlreadyUpper) {
        first[0] = toupper(first[0]);
        second[0] = toupper(second[0]);
        third[0] = toupper(third[0]);
    }

    printf("  1 - %s\n", first);
    printf("  2 - %s\n", second);
    printf("  3 - %s\n", third);
    int option;
    printf("\nDigite o número da palavra a ser usada ou 0 para permanecer com a palavra %s.\n", word);
    printf("> ");
    scanf("%d", &option);

    if (option == 1) strcpy(similar, first);
    else if (option == 2) strcpy(similar, second);
    else if (option == 3) strcpy(similar, third);
    else if (option == 0) similar = NULL;
    else {
        printf("Opção desconhecida, nenhuma alteração será feita.\n");
    }

    if (similar != NULL && isAlreadyUpper) similar[0] = toupper(similar[0]);
}

void changeWord(char wrongWord[], char similar[], char **userText, int numberOfWords) {
    for (int i = 0; i < numberOfWords; i++) {
        // printf("CONDICAO: %s %s\n", userText[i], similar);

        if (strcmp(userText[i], wrongWord) == 0) {
            // printf("SIMILAR: %s\n", similar);
            strcpy(userText[i], similar);
            // for (int i = 0; i < numberOfWords; i++) {
            //     printf("%s ", userText[i]);
            // }
            // printf("\n");
            break;
        }
    }
}