#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NWORDS_TEXT 1000
#define DICTIONARY_LEN 320139
#define MAX_INPUT 281

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

    printf("%d\n", numberOfWords);
    printf("%s\n", userText[numberOfWords - 1]);
    // Fazer nossas operações...

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

// Função para Obter as palavras de um arquivo
char **getTextFromFile(char filename[], int *numberOfWords) {
    FILE *file;
    file = fopen(filename, "r");

    // Arquivo não encontrado.
    if (file == NULL) {
        printf("ERRO! O arquivo %s não foi aberto!\n", filename);
        return NULL;
    }

    // Array da linha atual, resultado do get e Array de palavras inicializados
    char line[281];
    char *result;
    char **text = NULL;

    // Aloca o tamanho máximo que o array de palavras terá
    if (!(text = calloc(NWORDS_TEXT, sizeof *text))) {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }

    // Inicializa o array de palavras da linha atual
    // e o indicador da posição de cada palavra
    char **words = NULL;
    int i = 0;

    // Enquanto o arquivo não acabar
    while (!feof(file)) {
        // Obtém a linha atual
        result = fgets(line, 282, file);
        
        // Inicializa a quantidade de palavras naquela linha como zero
        int nWordsOfLine = 0;
        // Obtém o array de palavras naquela linha
        words = getWordsFromLine(result, &nWordsOfLine);
        // Adiciona a quantidade de palavras naquela linha à quantidade total
        (*numberOfWords) += nWordsOfLine;

        // Percorre todas as palavras da linha adicionando ao array de palavras final
        for (int j = 0; j < nWordsOfLine; j++) {
            text[i++] = words[j];
        }
    }

    fclose(file);

    return text;
}

// Função para obter um array de palavras de uma linha
char **getWordsFromLine(char line[], int *numberOfWords) {
    // Inicializa o array de palavras
    char **words = NULL;

    // Aloca o tamanho máximo do array de palavras
    if (!(words = calloc(NWORDS_TEXT, sizeof *words))) {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }
    
    // Obtém o tamanho da linha
    size_t linelen = strlen(line);

    // Retira o \n ao final da linha
    if (line[linelen - 1] == '\n') {
        line[linelen - 1] = 0;
    }

    // Inicializa a string da palavra atual e os indicadores de posição
    int i = 0;
    int wordlen = 47;
    char word[wordlen];
    int currentChar = 0;

    // Percorre cada char da linha
    for (int j = 0; j < linelen; j++) {
        // Se o char é espaço, adiciona esse caractere à palavra atual
        if (line[j] == ' ') {
            // adiciona a palavra completa ao array
            words[i++] = strdup(word);
            // Aumenta a quantidade de palavras
            (*numberOfWords)++;
            // Reseta a string
            memset(word, 0, wordlen);
            currentChar = 0;
        } else {
            // Adiciona mais um caractere
            word[currentChar++] = line[j];
        }
    }

    // Caso sobre uma palavra não adicionada
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
