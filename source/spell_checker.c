#include "spell_checker_bas.h"
#include "spell_checker_fin.h"
#include "spell_checker_lev.h"


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
        printf("A palavra %s pode estar escrita incorretamente, as opções de substituição são:\n", wrongWords[i]);
        char similar[] = "";
        getSimilar(wrongWords[i], dictionary, similar);

        if (similar != NULL) {
            changeWord(wrongWords[i], similar, userText, numberOfWords);
        }
    }

    char finalMessage[] = "";
    for (int i = 0; i < numberOfWords; i++) {
        if (userText[i][0] >= 65) strcat(finalMessage, " ");
        strcat(finalMessage, userText[i]);
    }

    printf("\nResultado:\n");
    printf("%s\n", finalMessage);

    return 0;
}
