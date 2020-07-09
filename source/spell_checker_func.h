#include "spell_checker.h"
#include "levenshtein.h"

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
    if (!(dictionary = (char **) calloc(DICTIONARY_LEN, sizeof *dictionary)))
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
    if (!(text = (char **) calloc(NWORDS_TEXT, sizeof *text)))
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
    for (int j = 0; j < linelen; j++)
    {
        // oi eu sou goku!
        // Se o char é espaço ou especial, adiciona esse caractere à palavra atual
        if ((line[j] == ' ' || (line[j] > 32 && line[j] < 65)) && strlen(word))
        {
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
                // specials[iSpecials].word[0] = line[j];
                // specials[iSpecials].position = numberOfWords;
                // iSpecials++;
                (*numberOfWords)++;

                printf("AAAAAAAAAA %s %d\n", words[i - 1], (int) line[j]);
                // Aumenta a quantidade de palavras
            }
        }
        else
        {
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

char **check_words(char **userText, int numberOfWords, char **dictionary)
{
    char userTextCopy[NWORDS_TEXT][MAXSTRING];

    for (int i = 0; i < numberOfWords; i++) {
        // printf("x %s\n", userText[i]);
        strcpy(userTextCopy[i], userText[i]);
    }
    // Inicializa o array de palavras
    char **words = NULL;

    // Aloca o tamanho máximo do array de palavras
    if (!(words = calloc(NWORDS_TEXT, sizeof(char[MAXSTRING]))))
    {
        printf("Memória Virtual exaurida!\n");
        return NULL;
    }

    for (int i = 0; i < numberOfWords; i++) {
        // printf("z %d\n", (int) userText[i][0]);
        if (((int) userText[i][0]) == 0) {
            strcpy(userText[i], userTextCopy[i]);
        }
    }

    int currentWord = 0;
    int i;
    for (i = 0; i < numberOfWords; i++)
    {
        if (!(userText[i][0] > 32 && userText[i][0] < 65)) {
            if (userText[i][0] == '\0') continue;

            int result = find_word(userText[i], dictionary);

            if (result)
            {
                printf("Encontrado: <%s> \n", userText[i]);
            } else {
                printf("chegou %s\n", userText[i]);
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