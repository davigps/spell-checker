#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#ifdef __cplusplus
extern "C"
{
#endif

    size_t
    levenshtein(const char *a, const char *b);

    size_t
    levenshtein_n(const char *a, const size_t length, const char *b, const size_t bLength);

#ifdef __cplusplus
}
#endif

#endif // LEVENSHTEIN_H