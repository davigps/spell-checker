#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define comprimentoDaLista 256
#define comprimentoDasPalavras 21

char **pegaPalavras (FILE *fp, int *n);
void liberaArray (char** palavras, int linhas);

int main (int argc, char **argv) {

    int i, nPalavras = 0;
    char **palavras = NULL;  /* arquivo dado em argv[1] (o padrão é dicionario.txt) */
    char *fname = argc > 1 ? argv[1] : "dicionario.txt";
    FILE *dicionario = fopen (fname, "r");

    if (!dicionario) { /* valida a abertura do arquivo */
        fprintf (stderr, "erro: abertura do arquivo falhou.\n");
        return 1;
    }

    if (!(palavras = pegaPalavras (dicionario, &nPalavras))) {
        fprintf (stderr, "erro: pegaPalavras retornou NULL.\n");
        return 1;
    }
    fclose(dicionario);

    printf ("\n '%d' palavras lidas de '%s'\n\n", nPalavras, fname);

    for (i = 0; i < nPalavras; i++) {
        printf ("%s\n", palavras[i]);
    }

    liberaArray (palavras, nPalavras);

    return 0;
}

 /*
 Lê todas as palavras 1 por linha, de 'fp', retorna ponteiro para ponteiro de todas as strings alocadas com sucesso, de outra forma retorna NULL, 'n' é atualizado com número de palavras lidas. 
 */
char **pegaPalavras (FILE *fp, int *n) {

    char **palavras = NULL;
    char buf[comprimentoDasPalavras + 1] = {0};
    int maxlen = comprimentoDaLista > 0 ? comprimentoDaLista : 1;

    if (!(palavras = calloc (maxlen, sizeof *palavras))) {
        fprintf (stderr, "pegaPalavras() erro: memória virtual exaurida.\n");
        return NULL;
    }

    while (fgets (buf, comprimentoDasPalavras + 1, fp)) {

        size_t wordlen = strlen (buf);  

        if (buf[wordlen - 1] == '\n')  
            buf[--wordlen] = 0;

        palavras[(*n)++] = strdup (buf);   

        if (*n == maxlen) { 
            void *tmp = realloc (palavras, maxlen * 2 * sizeof *palavras);
            if (!tmp) {
                fprintf (stderr, "pegaPalavras() realloc: memória exaurida.\n");
                return palavras;
            }
            palavras = tmp;
            memset (palavras + maxlen, 0, maxlen * sizeof *palavras);
            maxlen *= 2;
        }
    }

    return palavras;
}

void liberaArray (char **words, int rows){

    int i;
    for (i = 0; i < rows; i++){
        free (words[i]);
    }
    free(words);
}
