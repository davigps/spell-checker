#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "levenshtein.h"

// Retorna o tamanho(size_t) representando a diferença entre a e b

size_t
levenshtein_n(const char a, const size_t length, const char *b, const size_t bLength)
{

    if (a == b)
    {
        return 0;
    }

    if (length == 0)
    {
        return bLength;
    }

    if (bLength == 0)
    {
        return length;
    }

    //ponteiro cache com intuito de criar um array usando calloc de tamanho dinamico
    //o sizeof ta sendo usado para saber a quantidade de bytes opcupados por size_t, pra dai fazer a alocação dinamica
    size_t *cache = calloc(length, sizeof(size_t));
    size_t index = 0;
    size_t bIndex = 0;
    size_t distance;
    size_t bDistance;
    size_t result;
    char code;

    //iniciando o vetor
    while (index < length)
    {
        cache[index] = index + 1;
        index++;
    }

    while (bIndex < bLength)
    {
        code = b[bIndex];
        result = distance = bIndex++;
        index = SIZE_MAX;

        while (++index < length)
        {
            bDistance = code == a[index] ? distance : distance + 1;
            distance = cache[index];

            cache[index] = result = distance > result
                                        ? bDistance > result
                                              ? result + 1
                                              : bDistance
                                        : bDistance > distance
                                              ? distance + 1
                                              : bDistance;
        }
    }

    //liberando memória
    free(cache);

    return result;
}

size_t
levenshtein(const char *a, const char *b)
{
    const size_t length = strlen(a);
    const size_t bLength = strlen(b);

    return levenshtein_n(a, length, b, bLength);
}