#include "spell_checker.h"

// Função para obter o dicionário em array
char **getDictionary(char filename[])
{
    FILE *file;
    file = fopen(filename, "r");

    // Caso o arquivo não exista
    if (!file)
    {
        printf("ERRO! O arquivo %s não foi aberto!\n", filename);
        return NULL;
    }

    char line[46];
    char *result;
    char **dictionary = NULL;

    // Aloca todas as posições que o array vai precisar ter
    if (!(dictionary = calloc(DICTIONARY_LEN, sizeof *dictionary)))
    {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }

    int i = 0;
    // Percorre até encontrar o final do arquivo
    while (!feof(file))
    {
        // Obtém a linha
        result = fgets(line, 47, file);

        // Obtém o tamanho da palavra dessa linha
        size_t wordlen = strlen(result);

        // Retira o caractere \n ao final da palavra
        if (result[wordlen - 1] == '\n')
        {
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
char **getTextFromFile(char filename[], int *numberOfWords)
{
    FILE *file;
    file = fopen(filename, "r");

    // Arquivo não encontrado.
    if (file == NULL)
    {
        printf("ERRO! O arquivo %s não foi aberto!\n", filename);
        return NULL;
    }

    // Array da linha atual, resultado do get e Array de palavras inicializados
    char line[281];
    char *result;
    char **text = NULL;

    // Aloca o tamanho máximo que o array de palavras terá
    if (!(text = calloc(NWORDS_TEXT, sizeof *text)))
    {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }

    // Inicializa o array de palavras da linha atual
    // e o indicador da posição de cada palavra
    char **words = NULL;
    int i = 0;

    // Enquanto o arquivo não acabar
    while (!feof(file))
    {
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
        for (j = 0; j < nWordsOfLine; j++)
        {
            text[i++] = words[j];
        }
    }

    fclose(file);

    return text;
}

// Função para obter um array de palavras de uma linha
char **getWordsFromLine(char line[], int *numberOfWords)
{
    // Inicializa o array de palavras
    char **words = NULL;

    // Aloca o tamanho máximo do array de palavras
    if (!(words = calloc(NWORDS_TEXT, sizeof *words)))
    {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }

    // Obtém o tamanho da linha
    size_t linelen = strlen(line);

    // Retira o \n ao final da linha
    if (line[linelen - 1] == '\n')
    {
        line[linelen - 1] = 0;
    }

    // Inicializa a string da palavra atual e os indicadores de posição
    int i = 0;
    int wordlen = 47;
    char word[wordlen];
    int currentChar = 0;

    // Percorre cada char da linha
    int j;
    for (j = 0; j < linelen; j++)
    {
        // Se o char é espaço, adiciona esse caractere à palavra atual
        if (line[j] == ' ')
        {
            // adiciona a palavra completa ao array
            words[i++] = strdup(word);
            // Aumenta a quantidade de palavras
            (*numberOfWords)++;
            // Reseta a string
            memset(word, 0, wordlen);
            currentChar = 0;
        }
        else
        {
            // Adiciona mais um caractere
            word[currentChar++] = line[j];
        }
    }

    // Caso sobre uma palavra não adicionada
    if (strlen(word) > 0)
    {
        words[i++] = strdup(word);
        (*numberOfWords)++;
        memset(word, 0, wordlen);
    }

    return words;
}

// Função para liberar espaço dos arrays alocados dinâmicamente
void freeArray(char **words, int rows)
{
    int i;
    // Percorre cada item do array (que também é um array [string])
    for (i = 0; i < rows; i++)
    {
        free(words[i]);
    }
    // Libera o array final
    free(words);
}

char **check_words(char **userText, int numberOfWords, char **dictionary)
{
    // Inicializa o array de palavras
    char **words = NULL;

    // Aloca o tamanho máximo do array de palavras
    if (!(words = calloc(NWORDS_TEXT, sizeof *words)))
    {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }

    int currentWord = 0;
    int i;
    for (i = 0; i < numberOfWords; i++)
    {
        int result = find_word(userText[i], dictionary);

        if (result == 1)
        {
            printf("Encontrado: <%s> \n", userText[i]);
        }

        /*int iResult = binarySearch(dictionary, 0, DICTIONARY_LEN - 1, userText[i]);

        if (iResult == -1) {
            printf("chegou %s\n", userText[i]);
            words[currentWord++] = userText[i];
        }*/
    }

    return words;
}

int binarySearch(char **array, int ini, int end, char *x)
{
    /*if (ini <= end) {
        int mid = ini + (end - ini) / 2;

        if (strcmp(array[mid], x) == 0) {
            printf("achou %s\n", array[mid]);
            return mid;
        } else if (strcmp(array[mid], x) > 0) {
            return binarySearch(array, ini, mid-1, x);
        } else if (strcmp(array[mid], x) < 0) {
            return binarySearch(array, mid+1, end, x);
        }
    }

    return -1;*/

    while (ini < end)
    {
        int mid = (ini + end) / 2;
        if (strcmp(array[mid], x) == 0)
        {
            printf("achou %s\n", array[mid]);
            return mid;
        }
        else if (strcmp(array[mid], x) > 0)
        {
            ini = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }

    return -1;
}

int find_word(char *word, char **dictionary)
{
    char *result;
    int i;
    for (i = 0; i < DICTIONARY_LEN; i++)
    {
        if (strcmp(word, dictionary[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}