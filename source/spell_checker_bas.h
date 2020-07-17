#include "spell_checker.h"

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
    if (!(dictionary = (char **) calloc(DICTIONARY_LEN, sizeof *dictionary))) {
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
    if (!(text = (char **) calloc(NWORDS_TEXT, sizeof *text))) {
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
        int j;
        for (j = 0; j < nWordsOfLine; j++) {
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
    if (!(words = (char **) calloc(NWORDS_TEXT, sizeof(char[MAXSTRING])))) {
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
    char word[MAXSTRING];
    int currentChar = 0;

    // Percorre cada char da linha
    for (int j = 0; j < linelen; j++) {
        // Se o char é espaço ou especial, adiciona esse caractere à palavra atual
        if ((line[j] == ' ' || (line[j] > 32 && line[j] < 65)) && strlen(word)) {
            // adiciona a palavra completa ao array
            words[i++] = strdup(word);
            // Aumenta a quantidade de palavras, davi
            (*numberOfWords)++;
            // Reseta a string
            memset(word, 0, MAXSTRING);
            currentChar = 0;

            if (line[j] > 32 && line[j] < 65) {
                char special[2];
                special[0] = line[j];
                special[1] = '\0';

                words[i++] = special;

                // Aumenta a quantidade de palavras
                (*numberOfWords)++;
            }
        }
        else {
            // Adiciona mais um caractere
            if (line[j] != ' ') word[currentChar++] = line[j];
        }
    }

    // Caso sobre uma palavra não adicionada
    if (strlen(word) > 0) {
        words[i++] = strdup(word);
        (*numberOfWords)++;
        memset(word, 0, MAXSTRING);
    }

    return words;
}