#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NWORDS_TEXT 1000
#define DICTIONARY_LEN 320139

char **getDictionary(char[]);

char **getTextFromFile(char[], int*);

char **getWordsFromLine(char[], int*);

void freeArray (char **words, int rows);

int check_word(char []);

int compare_words(char[], char[]);

int main(int argc, char argv[]){
    char **dictionary = getDictionary("palavras.txt");
    char **userText = NULL;
    int numberOfWords = 0;

    printf("Olá, seja bem vindo ao spell-checker!\n");
    printf("Digite o nome do arquivo que deverá ser corrigido\n");
    printf("Ou digite 'T' e ENTER para digitar o texto no terminal.\n");
    printf("> ");

    char input[280];
    fgets(input, 280, stdin);

    if (strlen(input) == 2 && input[0] == 'T') {
        printf("> ");
        fgets(input, 280, stdin);

        userText = getWordsFromLine(input, &numberOfWords);

        printf("%d\n", numberOfWords);
        printf("%s\n", userText[numberOfWords - 1]);
        // Fazer nossas operações...
    } else {
        input[strlen(input) - 1] = '\0';
        userText = getTextFromFile(input, &numberOfWords);

        printf("%d\n", numberOfWords);
        printf("%s\n", userText[numberOfWords - 1]);
        // Fazer nossas operações...
    }

    //printf("O texto foi: \n%s", text);

    // int c = 0;
    // while(text[c] != '\0'){
    //     printf("%s", text[c]);
    //     c++;
    // }*/

    
    

    //verificação por palavra
    // char palavra[141][46];
    // int c, l= 0, j=0;
    // for (c = 0; c < 280; c++, j++){
    //     if(text[c] == '\0'){
    //         break;
    //     }
    //     if(text[c] == ' ' || text[c] == '\n' ){
    //         printf("%s\n", palavra[l]);
    //         //verificação se a palavra formada esta no arquivo .txt
    //         j = -1;
    //         l = l + 1;
    //     }
    //     else{
    //         palavra[l][j] = text[c];
    //     }
    // }

    // char palavra[46];
    // int c, i= 0;
    // for (c = 0; c < 280; c++, i++){
    //     if(text[c] == '\0'){
    //         break;
    //     }
    //     if(text[c] == ' ' || text[c] == '\n' ){
    //         //verificação se a palavra formada esta no arquivo .txt
    //         int j;
    //         // if (check_word(palavra) == 0){
    //             //Quando nao achar a palavra faz ...
    //         // }  
    //         for ( j = 0; j < i; j++ ){
    //             palavra[j] = ' ';
    //         }
    //         i = -1;
    //     }
    //     else{
    //         palavra[i] = text[c];
    //     }
    // }

    freeArray(dictionary, DICTIONARY_LEN);
    freeArray(userText, numberOfWords);

    return 0;
}

// Função para obter o dicionário em array
char **getDictionary(char filename[]) {
    FILE *file;
    file = fopen(filename, "r");

    // Caso o arquivo não exista
    if (!file) {
        printf("ERRO! O arquivo %s não foi aberto!\n", filename);
        return NULL;
    }

    char line[46];
    char *result;
    char **dictionary = NULL;

    // Aloca todas as posições que o array vai precisar ter
    if (!(dictionary = calloc(DICTIONARY_LEN, sizeof *dictionary))) {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }

    int i = 0;
    // Percorre até encontrar o final do arquivo
    while (!feof(file)) {
        // Obtém a linha
        result = fgets(line, 47, file);
        
        // Obtém o tamanho da palavra dessa linha
        size_t wordlen = strlen(result);

        // Retira o caractere \n ao final da palavra
        if (result[wordlen - 1] == '\n') {
            result[wordlen - 1] = 0;
        }

        // Obtém apenas a string exata da palavra (retira os espaços vazios) 
        // e define isso no array final
        dictionary[i++] = strdup(result);
    }

    fclose(file);

    return dictionary;
}


char **getTextFromFile(char filename[], int *numberOfWords) {
    FILE *file;
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("ERRO! O arquivo %s não foi aberto!\n", filename);
        return NULL;
    }

    char line[281];
    char *result;
    char **text = NULL;

    if (!(text = calloc(NWORDS_TEXT, sizeof *text))) {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }

    char **words = NULL;
    int i = 0;
    while (!feof(file)) {
        result = fgets(line, 282, file);
        
        int nWordsOfLine = 0;
        words = getWordsFromLine(result, &nWordsOfLine);
        (*numberOfWords) += nWordsOfLine;

        for (int j = 0; j < nWordsOfLine; j++) {
            text[i++] = words[j];
        }
    }

    fclose(file);

    return text;
}

char **getWordsFromLine(char line[], int *numberOfWords) {
    char **words = NULL;

    if (!(words = calloc(NWORDS_TEXT, sizeof *words))) {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }
    
    size_t linelen = strlen(line);

    if (line[linelen - 1] == '\n') {
        line[linelen - 1] = 0;
    }

    int i = 0;
    int wordlen = 47;
    char word[wordlen];
    int currentChar = 0;

    for (int j = 0; j < linelen; j++) {
        if (line[j] == ' ') {
            words[i++] = strdup(word);
            (*numberOfWords)++;
            memset(word, 0, wordlen);
            currentChar = 0;
        } else {
            word[currentChar++] = line[j];
        }
    }

    if (strlen(word) > 0) {
        words[i++] = strdup(word);
        (*numberOfWords)++;
        memset(word, 0, wordlen);
    }

    return words;
} 

// Função para liberar espaço dos arrays alocados dinâmicamente
void freeArray (char **words, int rows){
    int i;
    // Percorre cada item do array (que também é um array [string])
    for (i = 0; i < rows; i++){
        free (words[i]);
    }
    // Libera o array final
    free(words);
}


int check_word(char palavra[46]){
    FILE *pont_arq;
    pont_arq = fopen("palavras.txt", "r");
    if (pont_arq == NULL){
        printf("ERRO! O arquivo não foi aberto!\n");
    }

    char Linha[46];
    char *result;

    while (!feof(pont_arq)) {
        result = fgets(Linha, 47, pont_arq);
        if (compare_words(palavra, result) == 1){
            printf("%s <<<< Achamos !", result);
            return 1;
        }
    }
    fclose(pont_arq);
    return 0;
}

int compare_words(char palavra[46], char result[46]){
    int i = 0;

    for( i = 0; i < 46; i++){
        if(palavra[i] != result[i]){
            if(isalpha(palavra[i]) == 0 && isalpha(result[i]) == 0){
                break;
            }
            return 0;
        }
    }
    return 1;
}
