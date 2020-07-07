#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NWORDS_TEXT 1000
#define DICTIONARY_LEN 320139

char **getTextFromFile(char[]);

char **getDictionary(char[]);

void freeArray (char **words, int rows);

int check_word(char []);

int compare_words(char[], char[]);

int main(int argc, char argv[]){
    char **dictionary = getDictionary("palavras.txt");

    printf("Olá, seja bem vindo ao spell-checker!\n");
    printf("Digite o nome do arquivo que deverá ser corrigido\n");
    printf("Ou digite 'T' para digitar o texto no terminal.\n");
    printf("> ");

    char text[280];
    fgets(text, 280, stdin);


    printf("%s\n", dictionary[0]);
    printf("%s\n", dictionary[DICTIONARY_LEN - 1]);

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

    return 0;
}

char **getTextFromFile(char filename[]) {
    FILE *file;
    file = fopen(filename, "r");

    if (!file) return NULL;

    char line[281];
    char *result;
    char **text = NULL;

    if (!(text = calloc(NWORDS_TEXT, sizeof *text))) {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }

    int i = 0;
    while (!feof(file))
    {
        result = fgets(line, 282, file);
        
        size_t linelen = strlen(result);

        if (result[linelen - 1] == '\n') {
            result[linelen - 1] = 0;
        }

        int wordlen = 47;
        char word[wordlen];
        for (int j = 0; j < linelen; j++) {
            if (result[j] == ' ') {
                text[i++] = strdup(word);
                memset(word, 0, wordlen);
            } else {
                strcat(word, result[j]);
            }
        }

        if (strlen(word) > 0) {
            text[i++] = strdup(word);
            memset(word, 0, wordlen);
        }
    }

    fclose(file);

    return text;
}

// Função para obter o dicionário em array
char **getDictionary(char filename[]) {
    FILE *file;
    file = fopen(filename, "r");

    // Caso o arquivo não exista
    if (!file) {
        printf("ERRO! O arquivo não foi aberto!\n");
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
